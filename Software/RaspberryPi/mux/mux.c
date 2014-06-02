#include "mux/mux.h"


#if !defined(DESKTOP) && !defined(TEENSY)

#define REGISTER_SHIFT_LINE(VAR, DS) 			 			\
	{									\
		(VAR) = shift_create(MUX_SHIFT_LINE_LEN, (DS));			\
		shift_mgr_register(mux_int_mgr, (VAR));				\
	}

#define SET_COLOR_BIT(POS, COLOR, REG)					        \
	{									\
		if(mux_int_buffer[row][col].COLOR < depth)			\
		{								\
			/* log_debug("Clear %d.%d Val %d " # COLOR, row, col,	\
				mux_int_buffer[row][col].COLOR );*/		\
			(REG)->Data[(((POS) + MUX_COL_OFFSET) >> 3)] &= 	\
				~(1 << (((POS) + MUX_COL_OFFSET) % 8));		\
		}								\
		else								\
		{								\
			/* log_debug("Set %d.%d Val %d " # COLOR, row, col,	\
				mux_int_buffer[row][col].COLOR );*/		\
			(REG)->Data[(((POS) + MUX_COL_OFFSET) >> 3)] |= 	\
				(1 << (((pos) + MUX_COL_OFFSET) % 8));		\
		}								\
	}

#endif

////////////////////////////////////////////////////////////////////////////////
// public variables
p_mux_buffer_t mux_buffer;

////////////////////////////////////////////////////////////////////////////////
// private variables
static bool mux_initialized = false;

static mux_buffer_t mux_int_buffer_1, mux_int_buffer_2;
static p_mux_buffer_t mux_int_buffer;

#ifndef TEENSY
static bool mux_int_dirty_swap = false;

static pthread_t mux_int_thread;
#endif

#ifdef TEENSY
static int mux_file;
#endif

#if !defined(TEENSY) && !defined(DESKTOP)
static p_shift_mgr_t mux_int_mgr = NULL;
static p_shift_register_t reg1 = NULL;
#endif

////////////////////////////////////////////////////////////////////////////////
// private function declaration

inline void mux_int_swap_buffer();

#ifndef TEENSY
void *mux_plex(void *);
#endif

#if !defined(TEENSY) && !defined(DESKTOP)
inline bool mux_get_time_diff(struct timespec *left, struct timespec *right);
#endif

#ifdef DESKTOP
	bool mux_gl_init();
	bool mux_gl_init_gl();
	void mux_gl_render();
	void mux_gl_main_loop(int val);
#endif

////////////////////////////////////////////////////////////////////////////////
// public function implementation

bool mux_init()
{
 	mux_int_buffer  = mux_int_buffer_1;
	mux_buffer 	= mux_int_buffer_2;

	draw_picture( photo_pi );
	mux_int_swap_buffer(); 

#if defined(DESKTOP)
	mux_initialized = true;

	return mux_gl_init();

#elif defined(TEENSY)
	mux_file = open(MUX_PORT, O_WRONLY);
	if(mux_file < 0)
		log_error("Unable to connect to comport");
	else
	{
		log_debug("Connected to comport " MUX_PORT);

		struct termios settings;

		tcgetattr(mux_file, &settings);
		cfmakeraw(&settings);
		tcsetattr(mux_file, TCSANOW, &settings);

		mux_initialized = true;

		mux_swap_buffer(); // needed 2times so the previously drawn buffer gets transmitted.
		mux_swap_buffer();
	}

	return mux_file >= 0;
#else
	gpio_init();

	mux_int_mgr = shift_mgr_create(MUX_SHCP, MUX_STCP);
	if(mux_int_mgr == NULL)
	{
		MUX_DEBUG("Unable to initialize the shift line manager.");
		return false;
	}

	REGISTER_SHIFT_LINE(reg1, MUX_MODUL_1_DS);

	mux_initialized = true;

	return true;
#endif
}

void mux_deinit()
{
	if(!mux_initialized) return;
#if defined(DESKTOP)
	glutLeaveMainLoop();
	log_debug("Stop Glut (Open GL)");

	pthread_cancel(mux_int_thread);

#elif defined(TEENSY)
	draw_picture( photo_pi );
	mux_swap_buffer();

	if(mux_file >= 0)
		close(mux_file);
#else
	DRAW_CLEAR();
	mux_swap_buffer();

	shift_mgr_delete(mux_int_mgr);
	pthread_cancel(mux_int_thread);
#endif

	log_debug("shutdown mux module");
}

void mux_run()
{
	if(!mux_initialized) return;

#ifndef TEENSY
	if(pthread_create(&mux_int_thread, NULL, mux_plex, NULL))
	{
		MUX_DEBUG("Unable to start thread");
	}
#endif
}

void mux_request_swap_buffer()
{
#ifndef TEENSY
	mux_int_dirty_swap = true;
#else
	if(!mux_initialized) return;
	
	static const uint8_t frame[1] = { 0xFF };
	if(write(mux_file, frame, 1) && write(mux_file, mux_buffer, sizeof(mux_buffer_t)) != sizeof(mux_buffer_t))
		log_error("Write to comport (teensy) failed or was not complete");

	mux_int_swap_buffer();
#endif
}

void mux_wait_swap_buffer()
{
#ifndef TEENSY
	while(mux_int_dirty_swap);
#endif
}

void mux_swap_buffer()
{
 	mux_request_swap_buffer();
#ifndef TEENSY
	mux_wait_swap_buffer();
#endif
}

////////////////////////////////////////////////////////////////////////////////
// private function implementation

void mux_int_swap_buffer()
{
	p_mux_buffer_t tmp = mux_buffer;
	mux_buffer = mux_int_buffer;
	mux_int_buffer = tmp;

#ifndef TEENSY
	mux_int_dirty_swap = false;
#endif

	// MUX_DEBUG("Swap Buffer");
}

#ifndef TEENSY
void *mux_plex(void *)
{
#ifndef DESKTOP
	// get reference time
	struct timespec last_delta, delta;
	clock_gettime(CLOCK_MONOTONIC, &last_delta);
	last_delta.tv_nsec -= (MUX_DELAY); // So that the first image will be
					   // displayed immediatly

	MUX_DEBUG("MUX: Start multiplexing");

	while(true)
	{
		for(int row=0; row < MUX_HEIGHT; row++)
		{
			// Delete previous values
			memset(reg1->Data, 0, MUX_SHIFT_LINE_LEN);

			// Set new row value

			reg1->Data[((row + MUX_ROW_OFFSET) >> 3)] |=
				(1 << (row + MUX_ROW_OFFSET) % 8);

			for(int depth = 1; depth <= MUX_COLOR_DEPTH; depth++)
			{
				for(int col=0; col < MUX_WIDTH; col++)
				{
					uint8_t pos = col * 3;
					SET_COLOR_BIT(pos, r, reg1)
					++pos;
					SET_COLOR_BIT(pos, g, reg1)
					++pos;
					SET_COLOR_BIT(pos, b, reg1)
				}

				// write the serialized image
				shift_mgr_write(mux_int_mgr);

				// Add Delta and wait for the next step
				last_delta.tv_nsec = last_delta.tv_nsec  +
						     MUX_DELAY;
				do
				{
					clock_gettime(CLOCK_MONOTONIC, &delta);
				} while(mux_get_time_diff(&last_delta, &delta));

				last_delta.tv_sec  = delta.tv_sec;
				last_delta.tv_nsec = delta.tv_nsec;

				// Display image
				shift_mgr_activate(mux_int_mgr);
			}
		}

		if(mux_int_dirty_swap)
			mux_int_swap_buffer();
	}
#else
	glutDisplayFunc(mux_gl_render);
	glutTimerFunc(MUX_GL_DELAY, mux_gl_main_loop, 0);

	glutMainLoop();
#endif
	return NULL;
}
#endif
#if !defined(TEENSY) && !defined(DESKTOP)
inline bool mux_get_time_diff(struct timespec *last, struct timespec *cur)
{
	return 	 last->tv_sec > cur->tv_sec ||
		(last->tv_sec == cur->tv_sec && last->tv_nsec >= cur->tv_nsec);
}
#endif

#ifdef DESKTOP
bool mux_gl_init()
{
	char *argv[] = { "LedPI", NULL };
	int argc = 1;

	glutInit(&argc, argv);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(MUX_GL_SCREEN_WIDTH, MUX_GL_SCREEN_HEIGHT);
	glutCreateWindow("LedPI Emulated LED Matrix");

	log_debug("Open Gl Window created");

	return mux_gl_init_gl();
}

bool mux_gl_init_gl()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, MUX_GL_SCREEN_WIDTH, MUX_GL_SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(MUX_GL_BACKGROUND_COLOR);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		log_error("Error initializing OpenGL: %s", gluErrorString(error));
		return false;
	}
	else
	{
		log_debug("Open Gl Initialized");
	}

	return true;
}

void mux_gl_main_loop(int val)
{
	mux_gl_render();

	if(mux_int_dirty_swap)
		mux_int_swap_buffer();

	glutTimerFunc(MUX_GL_DELAY, mux_gl_main_loop, val);
}

void mux_gl_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin( GL_QUADS );

	for(int row = 0 ; row < MUX_HEIGHT ; ++row)
	{
		for(int col = 0 ; col < MUX_WIDTH ; ++col)
		{
			/// log_debug( "%d %d %d", mux_int_buffer[row][col].r, mux_int_buffer[row][col].g, mux_int_buffer[row][col].b );

			glColor3f( MUX_GL_COLOR_PIXEL( mux_int_buffer[row][col] ) );

			// left upper corner
			glVertex2f( MUX_GL_TO_SCREEN_COORD( (col * MUX_GL_TILE_SIZE_VERTICAL   + MUX_GL_MARGIN_VERTICAL),
		        				    (row * MUX_GL_TILE_SIZE_HORIZONTAL + MUX_GL_MARGIN_HORIZONTAL) ) );

			// right upper corner
	      		glVertex2f( MUX_GL_TO_SCREEN_COORD( (col * MUX_GL_TILE_SIZE_VERTICAL   - MUX_GL_MARGIN_VERTICAL	+ MUX_GL_TILE_SIZE_VERTICAL ),
						            (row * MUX_GL_TILE_SIZE_HORIZONTAL + MUX_GL_MARGIN_HORIZONTAL) ) );

			// right bottom corner
			glVertex2f( MUX_GL_TO_SCREEN_COORD( (col * MUX_GL_TILE_SIZE_VERTICAL   - MUX_GL_MARGIN_VERTICAL   + MUX_GL_TILE_SIZE_VERTICAL ),
						            (row * MUX_GL_TILE_SIZE_HORIZONTAL - MUX_GL_MARGIN_HORIZONTAL + MUX_GL_TILE_SIZE_HORIZONTAL ) ) );

			// left bottom corner
			glVertex2f( MUX_GL_TO_SCREEN_COORD( (col * MUX_GL_TILE_SIZE_VERTICAL   + MUX_GL_MARGIN_VERTICAL),
	  					            (row * MUX_GL_TILE_SIZE_HORIZONTAL - MUX_GL_MARGIN_HORIZONTAL + MUX_GL_TILE_SIZE_HORIZONTAL ) ) );

		}
	}

	glEnd();

	glutSwapBuffers();
}

#endif

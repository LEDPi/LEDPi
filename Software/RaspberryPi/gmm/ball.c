#include "ball.h"

#define CROP_LIMIT(val, min, max)	( (val) <= (min) ? (min) : (val) >= (max) ? (max) : (val) )
#define CROP(val)			CROP_LIMIT(val, 0, 1)

#define WRITE(TARGET,SOURCE)					\
	{							\
		tmp = (float)(SOURCE);				\
		*((TARGET)+0) = *(((uint8_t*)(&(tmp))) + 0);	\
		*((TARGET)+1) = *(((uint8_t*)(&(tmp))) + 1);	\
		*((TARGET)+2) = *(((uint8_t*)(&(tmp))) + 2);	\
		*((TARGET)+3) = *(((uint8_t*)(&(tmp))) + 3);	\
	}							

///////////////////////////////////////////////////////////////////////////////
// module private variables

static bool ball_initialized = false;

static pthread_mutex_t ball_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_t ball_thread;

static uint8_t ball_count     = 0;
static uint8_t ball_new_count = 4;
static ball_var_t ball_size   = 8;
static ball_var_t ball_red    = 1;
static ball_var_t ball_green  = 0.2;
static ball_var_t ball_blue   = 0.7;
static ball_var_t ball_speed  = 1.2;
static ball_var_t ball_glow   = 0.4;
static bool ball_invert       = false;
static bool ball_random	      = false;
static ball_var_t ball_random_speed = 8;

static p_ball_t ball_balls    = NULL;

///////////////////////////////////////////////////////////////////////////////
//private function declaration

void ball_generate();
void ball_draw();
void ball_color();
void ball_move();

///////////////////////////////////////////////////////////////////////////////
// Thread function of the module. Controls the gradient module und changes forms
// and colors.
//
// PARA: 
//	void * unnamed: needed to match the thread entry point method signature
//			but is not used. Passed data will be ignored.
//	return value:	is also not used, function will not return anything
///////////////////////////////////////////////////////////////////////////////
void *ball_run_thread(void *);

///////////////////////////////////////////////////////////////////////////////
// public function implementation
///////////////////////////////////////////////////////////////////////////////

bool ball_init()
{
	srand( (unsigned) time( NULL ) );

	if(pthread_create(&ball_thread, NULL, ball_run_thread, NULL) != 0)
	{
		log_error("Unable to create the mono thread");
		return false;
	}
	
	ball_initialized = true; 
	return true;
}

void ball_deinit()
{
	if(!ball_initialized) return;
	ball_initialized = false;
	pthread_cancel(ball_thread);
}

void MsgBalls_Change(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	if(!ball_initialized) return;

	if(len == 0)
	{
		uint8_t data_to_send[29];

		//flag byte
		uint8_t flags = 0;

		if(ball_random) flags += 128;
		if(ball_invert) flags += 64;
		flags += ball_new_count;

		data_to_send[0] = flags;

		float tmp;

		WRITE(&data_to_send[1],ball_speed);
		WRITE(&data_to_send[5],ball_red);
		WRITE(&data_to_send[9],ball_green);
		WRITE(&data_to_send[13],ball_blue);
		WRITE(&data_to_send[17],ball_size);
		WRITE(&data_to_send[21],ball_glow);
		WRITE(&data_to_send[25],ball_random_speed);

		net_send(sender,fc|0x8000,29,data_to_send);

	}
	else if (len == 29)
	{
		//flag byte
		if(data[0]<128) ball_random = false;
		else ball_random = true;

		if((data[0]&64)==64) ball_invert = true;
		else ball_invert = false;

		ball_new_count = data[0]&15;
		
		float tmp;
	
		//speed
		memcpy((void*) &tmp, &data[1], 4);	
		ball_speed = (ball_var_t) tmp;

		//colors
		memcpy((void*) &tmp, &data[5],4);
		ball_red = (ball_var_t) tmp;
		memcpy((void*) &tmp, &data[9],4);
		ball_green = (ball_var_t) tmp;
		memcpy((void*) & tmp, &data[13],4);
		ball_blue = (ball_var_t) tmp;

		//size
		memcpy((void*) &tmp, &data[17],4);
		ball_size = (ball_var_t) tmp;

		//glow
		memcpy((void*) &tmp, &data[21],4);
		ball_glow = (ball_var_t) tmp;	

		//random speed
		memcpy((void*) &tmp, &data[25],4);
		ball_random_speed = (ball_var_t) tmp;
	}
	else
	{
		log_error("Wrong message lenght for MsgBalls_Change");
	}
}

///////////////////////////////////////////////////////////////////////////////
// private function implementation
///////////////////////////////////////////////////////////////////////////////
void *ball_run_thread(void *)
{
	for(;;)
	{
		if( ball_count != ball_new_count )
			ball_generate();

		if( ball_random ) 
			ball_color();
	
		ball_move();	
		ball_draw();
		mux_swap_buffer();
	
		usleep( BALL_SLEEP );		
	}
}

void ball_generate()
{
	ball_count = ball_new_count;
	ball_balls = (p_ball_t) malloc( sizeof( ball_t ) * ball_count );

	for( int i=0 ; i<ball_count ; ++i )
	{
		ball_balls[i].x = BALL_RND * 30.0;
		ball_balls[i].y = BALL_RND * 30.0;
		ball_balls[i].dx = BALL_RND + .5;
		ball_balls[i].dy = BALL_RND + .5;
		
		if( BALL_RND < .5 )
			ball_balls[i].dx = -ball_balls[i].dx;

		if( BALL_RND < .5 )
			ball_balls[i].dy = -ball_balls[i].dy;
	}
}

void ball_draw()
{
	for( uint8_t x=0 ; x<MUX_WIDTH ; ++x )
		for( uint8_t y=0 ; y<MUX_HEIGHT ; ++y )
		{
			ball_var_t r = 0, g = 0, b = 0;

			for( int i=0 ; i<ball_count ; ++i )
			{
				ball_var_t dist = ball_balls[i].valx[x] + ball_balls[i].valy[y];

				r += ball_size / dist * ball_red;
				g += ball_size / dist * ball_green;
				b += ball_size / dist * ball_blue;	
			}
			
			if(ball_invert)
			{
				DRAW_POINT(x, y, (uint8_t)((1 - CROP(r)) * MUX_COLOR_DEPTH),
					 	 (uint8_t)((1 - CROP(g)) * MUX_COLOR_DEPTH),
						 (uint8_t)((1 - CROP(b)) * MUX_COLOR_DEPTH) )
			}
			else
			{
				DRAW_POINT(x, y, (uint8_t)(CROP(r) * MUX_COLOR_DEPTH),
						 (uint8_t)(CROP(g) * MUX_COLOR_DEPTH),
						 (uint8_t)(CROP(b) * MUX_COLOR_DEPTH) );
			}
		} 
}

void ball_color()
{
	if( BALL_RND < .25 )
	{
		if( BALL_RND < .5 )
			ball_red += BALL_RND / ball_random_speed;
		else
			ball_red -= BALL_RND / ball_random_speed;
		
		if( ball_red < 0 ) ball_red = .0;
		if( ball_red > 1 ) ball_red = 1.0;
	}

	if( BALL_RND < .25 )
	{
		if( BALL_RND < .5 )
			ball_green += BALL_RND / ball_random_speed;
		else
			ball_green -= BALL_RND / ball_random_speed;
		
		if( ball_green < 0 ) ball_green = .0;
		if( ball_green > 1 ) ball_green = 1.0;
	}

	if( BALL_RND < .25 )
	{
		if( BALL_RND < .5 )
			ball_blue += BALL_RND / ball_random_speed;
		else
			ball_blue -= BALL_RND / ball_random_speed;
		
		if( ball_blue < 0 ) ball_blue = .0;
		if( ball_blue > 1 ) ball_blue = 1.0;
	}
}

void ball_move()
{
	for( int i=0 ; i<ball_count ; ++i )
	{
		ball_balls[i].x += ball_balls[i].dx * ball_speed;		
		ball_balls[i].y += ball_balls[i].dy * ball_speed;

		if( ball_balls[i].x < 0 || ball_balls[i].x > MUX_WIDTH )
			ball_balls[i].dx = -ball_balls[i].dx;
		
		if( ball_balls[i].y < 0 || ball_balls[i].y > MUX_HEIGHT )
			ball_balls[i].dy = -ball_balls[i].dy;

		for( int j=0 ; j<MUX_WIDTH ; ++j )
			ball_balls[i].valx[j] = ball_glow * (ball_balls[i].x - j) * (ball_balls[i].x - j);
		
		for( int j=0 ; j<MUX_HEIGHT ; ++j )
			ball_balls[i].valy[j] = ball_glow * (ball_balls[i].y - j) * (ball_balls[i].y - j);
	}
}




#include "gui/gui_con.h"

////////////////////////////////////////////////////////////////////////////////
// local variables
#define CON_INPUT_X 	8
#define CON_INPUT_Y 	20
#define CON_INPUT()	move(CON_INPUT_Y, CON_INPUT_X)

#define CON_COM_WIDTH	40

#define CON_PAIR_OFFSET	2

static int con_x;
static int con_y;
static int pos_log = 0, pos_com = 0;

static bool gui_initialized = false;

static WINDOW 	*con_input = NULL, 
		*con_main  = NULL, 
		*con_debug = NULL, 
		*con_com   = NULL;

////////////////////////////////////////////////////////////////////////////////
// local function decalration

#define MUX_TEST(COLOR)								\
	{									\
		mux_test_ ## COLOR();						\
		log_debug("Changed color to " #COLOR);				\
		con_set_status("Changed color to " #COLOR);			\
	}

void con_create_input_wnd();
void con_create_debug_wnd();
void con_create_com_wnd();
void con_create_main_wnd();
void con_draw(int sig);
void con_log_msg(int lvl, 
		 int *pos, 
		 WINDOW *wnd, 
		 int height,
		 int len, 
		 const char *msg, 
		 va_list va);
void con_handle_input(char c);

////////////////////////////////////////////////////////////////////////////////
// public function implementation

bool con_init()
{
	initscr();
	
	if(has_colors() == FALSE)
	{
		endwin();
		log_error("Terminal doesn't support colors\n");
		return false;
	}

	start_color();

	init_pair(1, COLOR_RED, COLOR_WHITE);

	init_pair(CON_ERROR   + CON_PAIR_OFFSET, COLOR_RED, COLOR_BLACK);
	init_pair(CON_WARNING + CON_PAIR_OFFSET, COLOR_WHITE, COLOR_BLACK);
	init_pair(CON_DEBUG   + CON_PAIR_OFFSET, COLOR_GREEN, COLOR_BLACK);
	init_pair(CON_COM     + CON_PAIR_OFFSET, COLOR_WHITE, COLOR_BLACK);

	con_draw(0);

	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = con_draw;
	sigaction(SIGWINCH, &sa, NULL);

	// set functions to interface
	gui_deinit = con_deinit;
	gui_run = con_run;
	gui_log = con_log;
	gui_log_v = con_log_v;
	gui_set_status = con_set_status;

	gui_initialized = true;
	return true;
}

void con_deinit()
{
	gui_initialized = false;
	endwin();
}
 
void con_run()
{
	char c;
	while((c = getch()) != 'q')	
	{
		con_handle_input(c);
		CON_INPUT();
	}
	
	log_debug("shutdown initiated");	
}

void con_handle_input(char c)
{
	switch(c)
	{
		case 'r':
		MUX_TEST(red);
		break;

		case 'g':
		MUX_TEST(green);
		break;

		case 'b':
		MUX_TEST(blue);
		break;

		case 'o':
		MUX_TEST(off);
		break;

		case 'w':
		MUX_TEST(white);
		break;

		default:
			con_set_status("Unknown input: %c", c);
	}
}

void con_set_status(const char *msg, ...)
{
	va_list ap;
	
	attron(COLOR_PAIR(1));
	
	move(con_x-1, 9);

	va_start(ap, msg);
	vwprintw(stdscr, msg, ap);	
	va_end(ap);

	attroff(COLOR_PAIR(1));
	refresh();

	CON_INPUT();
}

void con_log(int lvl, const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);
	con_log_v(lvl, msg, ap);
	va_end(ap);
}

void con_log_v(int lvl, const char *msg, va_list ap)
{
	if(!gui_initialized) return;

	if(lvl == CON_COM)
	{
		con_log_msg(lvl, 
			    &pos_com, 
		 	    con_com, 
			    con_x - 7, 
			    CON_COM_WIDTH - 1,
			    msg, ap);
	}
	else
	{
		con_log_msg(lvl, 
			    &pos_log, 
			    con_debug, 
			    con_x - CON_INPUT_Y - 6, 
			    con_y - CON_COM_WIDTH - 17,
			    msg, ap);
	}
}

////////////////////////////////////////////////////////////////////////////////
// private function implementation

void con_log_msg(int lvl, 
		 int *pos, 
		 WINDOW *wnd, 
  		 int height, 
		 int len, 
		 const char *msg, 
		 va_list ap)
{
	// Get write position
	int local_pos = ((*pos)++ % height) + 1;

	// Get current time
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);

	// write
	wattron(wnd, COLOR_PAIR(lvl + CON_PAIR_OFFSET));

	mvwprintw(wnd, local_pos + 1, 1, 
		lvl == CON_COM ? "%4d: " : "%4d %4d.%3d: ", 
		(*pos), ts.tv_sec % 1000, ts.tv_nsec / 1000000);
	
	// cut off the strings length
	char *tmpmsg = (char *)malloc(sizeof(char) * len);
	memset(tmpmsg, ' ', len);
	for(int i=0 ; msg[i] != '\0' && i<len ; i++)
	{
		tmpmsg[i] = msg[i];
	}

	tmpmsg[len - 1] = '\0';

	vwprintw(wnd, tmpmsg, ap);
	
	free(tmpmsg);

	wattroff(wnd, COLOR_PAIR(lvl + CON_PAIR_OFFSET)); 

	wrefresh(wnd);
}

void con_create_input_wnd()
{
	if(con_input != NULL) delwin(con_input);

	con_input = newwin(3, con_y-CON_COM_WIDTH, CON_INPUT_Y - 1, 0);
	wborder(con_input, 	ACS_VLINE, 	ACS_VLINE,
				ACS_HLINE, 	ACS_HLINE,
				ACS_ULCORNER,	ACS_URCORNER,
				ACS_LLCORNER,	ACS_LRCORNER ); 

	mvwprintw(con_input, 1, 1, "INPUT: ");
	wrefresh(con_input);
}

void con_create_debug_wnd()
{
	if(con_debug != NULL) delwin(con_debug);

	con_debug = newwin(con_x - CON_INPUT_Y - 3, // lines
			   con_y - CON_COM_WIDTH,   // cols	
			   CON_INPUT_Y + 2,	    // y 
			   0);			    // x

	wborder(con_debug, 	ACS_VLINE, 	ACS_VLINE,
				ACS_HLINE, 	ACS_HLINE,
				ACS_ULCORNER,	ACS_URCORNER,
				ACS_LLCORNER,	ACS_LRCORNER ); 

	mvwprintw(con_debug, 1, 1, "DEBUG OUTPUT: ");

	wrefresh(con_debug);
}

void con_create_com_wnd()
{
	if(con_com != NULL) delwin(con_com);

	con_com = newwin(  con_x-4, // lines
			   CON_COM_WIDTH,   // cols	
			   3,	    		      // y 
			   con_y - CON_COM_WIDTH);    // x

	wborder(con_com, 	ACS_VLINE, 	ACS_VLINE,
				ACS_HLINE, 	ACS_HLINE,
				ACS_ULCORNER,	ACS_URCORNER,
				ACS_LLCORNER,	ACS_LRCORNER ); 
	mvwprintw(con_com, 1, 1, "COMMUNICATION: ");
	wrefresh(con_com);
}

void con_create_main_wnd()
{
	if(con_main != NULL) delwin(con_main);

	con_main = newwin( CON_INPUT_Y - 4,
			   con_y - CON_COM_WIDTH,   // cols	
			   3,     // y 
			   0);    // x

	wborder(con_main, 	ACS_VLINE, 	ACS_VLINE,
				ACS_HLINE, 	ACS_HLINE,
				ACS_ULCORNER,	ACS_URCORNER,
				ACS_LLCORNER,	ACS_LRCORNER ); 

	mvwprintw(con_main, 1, 1, "LED PI Main");

	time_t absolute_time = time(NULL);
	struct tm cur_time = *localtime(&absolute_time);

	mvwprintw(con_main, 1, 1, 
		"LED PI Main\t\tTimestamp: %02d:%02d:%2d %02d.%02d.%04d",
		cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec,
		cur_time.tm_mday, cur_time.tm_mon + 1, cur_time.tm_year + 1900);

	mvwprintw(con_main, 3, 1, "VERSIN PI: %02d.%02d", VERSION >> 8, VERSION & 0xFF);
	mvwprintw(con_main, 4, 1, "Version NET: %02d.%02d\tVersion MUX: %02d.%02d\tVersion GUI: %02d.%02d",
		NET_VERSION >> 8, NET_VERSION & 0xFF,
		MUX_VERSION >> 8, MUX_VERSION & 0xFF,
		GUI_VERSION >> 8, GUI_VERSION & 0xFF);

	mvwprintw(con_main, CON_INPUT_Y - 6, 1, "Press R, G, B, W or O to fill the Matrix");
	wrefresh(con_main);
}

void con_draw(int sig)
{
	endwin();
	refresh();

	getmaxyx(stdscr, con_x, con_y);

	attron(COLOR_PAIR(1));

	mvhline(0, 0, ' ', con_y);
	mvhline(1, 0, ' ', con_y);
	mvhline(2, 0, ' ', con_y);
	mvprintw(1, con_y / 2 - 10, "LED PI %02x.%02x", 
		VERSION >> 8, VERSION & 0xFF);
	
	mvhline(con_x-1, 0, ' ', con_y);
	mvprintw(con_x-1, 0, "STATUS:");
	mvprintw(con_x-1, con_y - 7, "[Q]uit");

	attroff(COLOR_PAIR(1));
	
	refresh();

	con_set_status("Loading ...");

	con_create_input_wnd();
	con_create_debug_wnd();
	con_create_com_wnd();
	con_create_main_wnd();

	CON_INPUT();
}

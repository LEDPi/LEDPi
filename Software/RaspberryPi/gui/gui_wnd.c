#include "gui/gui_wnd.h"

bool wnd_init()
{
	gui_deinit = wnd_deinit;	
	gui_run = wnd_run;
	gui_set_status = wnd_set_status;
	gui_log = wnd_log;
	gui_log_v = wnd_log_v;

	log_error("Module not implemented");
	return false;
}

void wnd_deinit()
{
}

void wnd_run()
{
}

void wnd_set_status(const char *msg, ...)
{
}

void wnd_log(int lvl, const char *msg, ...)
{
}

void wnd_log_v(int lvl, const char *msg, va_list ap)
{
}
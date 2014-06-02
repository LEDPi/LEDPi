#include "gui/gui_int.h"

void (*gui_deinit)();
void (*gui_run)();
void (*gui_set_status)(const char *msg, ...);
void (*gui_log)(int lvl, const char *msg, ...);	
void (*gui_log_v)(int lvl, const char *msg, va_list ap);

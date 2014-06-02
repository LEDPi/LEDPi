#include <gui/logger.h>

////////////////////////////////////////////////////////////////////////////////
// private variables

#define LOG_AP(LVL, MSG)			\
	{					\
		va_list ap;			\
						\
		va_start(ap, (MSG));		\
		log_v(ap, (LVL), (MSG));	\
		va_end(ap);			\
	}					
		
static timespec log_time;

////////////////////////////////////////////////////////////////////////////////
// public function implementation

bool log_init()
{
	FILE * file = fopen(LOG_FILE, "w");

	if(file == NULL && gui_log != NULL)
	{
		gui_log(LOG_ERROR, "Unable to open log file");
		return false;
	}
	
	time_t absolute_time = time(NULL);
	struct tm cur_time = *localtime(&absolute_time);

	fprintf(file, 
		"LED PI Logfile\n\n\tKai Gemmrich\n\tSebastian Weiss\n\tAiko I"
		"sselhard\n\nTimestamp: %02d:%02d:%2d %02d.%02d.%04d\n\nVERSIN PI: "
		"%02d.%02d\n\tVersion NET: %02d.%02d\n\tVersion MUX: %02d.%02d\n\tVe"
		"rsion GUI: %02d.%02d\n\nLog entries:\n",
		cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec,
		cur_time.tm_mday, cur_time.tm_mon + 1, cur_time.tm_year + 1900,
		VERSION >> 8, VERSION & 0xFF,
		NET_VERSION >> 8, NET_VERSION & 0xFF,
		MUX_VERSION >> 8, MUX_VERSION & 0xFF,
		GUI_VERSION >> 8, GUI_VERSION & 0xFF);
		
	fclose(file);

	clock_gettime(CLOCK_REALTIME, &log_time);
	log_time.tv_nsec = 0;

	return true;
}

void log_v(va_list va, log_lvl_t level, const char *msg)
{
	if(gui_log != NULL)
	{
		gui_log_v(level, msg, va);
	}
	else
	{
		printf("%2d:", level);
		vprintf(msg, va);
		printf("\n");
	}	

	FILE * file = fopen(LOG_FILE, "a");
	if(file == NULL && gui_log != NULL)
	{
		gui_log(LOG_ERROR, "Unable to open log file");
	} 
	else
	{	
		timespec time;
		clock_gettime(CLOCK_REALTIME, &time);
		
		fprintf(file, "%4d.%04d ",
			(int)(time.tv_sec - log_time.tv_sec), 
			(int)((time.tv_nsec - log_time.tv_nsec)/ 1000000));

		switch(level)
		{
			case LOG_ERROR:
				fprintf(file, "Error  : ");
			break;

			case LOG_WARNING:
				fprintf(file, "Wanring: ");
			break;

			case LOG_DEBUG:
				fprintf(file, "Debug  : ");
			break;
	
			case LOG_COM:
				fprintf(file, "Com    : ");
			break;

			default:
				fprintf(file, "No Lvl : ");	
		}

		vfprintf(file, msg, va);

		fprintf(file, "\n");
		fclose(file);
	}
}

void log(log_lvl_t level, const char *msg, ...)
{
	LOG_AP(level, msg);
}

void log_error(const char *msg, ...)
{
	LOG_AP(LOG_ERROR, msg);
}

void log_warning(const char *msg, ...)
{
	LOG_AP(LOG_WARNING, msg);
}

void log_debug(const char *msg, ...)
{
	LOG_AP(LOG_DEBUG, msg);
}

void log_com(const char *msg, ...)
{
	//LOG_AP(LOG_COM, msg);
}

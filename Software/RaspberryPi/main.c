#include "main.h"

///////////////////////////////////////////////////////////////////////////////
// private function declarations

////////////////////////////////////////////////////////////////////////////////
// Returns true if any string in the given array is equal to the given compare
// string.
// PARAMS:
//	src	the source array
//	count	the number of elements in the source array
//	str	the compare string
////////////////////////////////////////////////////////////////////////////////
bool any_equal(char *src[], int count, char *str);

////////////////////////////////////////////////////////////////////////////////
// Initializes all software modules.
// PARAMS:
//	argc	the number of array elements
//	argv	the command line parameters
////////////////////////////////////////////////////////////////////////////////
bool init(int argc, char* argv[]);

////////////////////////////////////////////////////////////////////////////////
// Avivates all software modules and their threads.
////////////////////////////////////////////////////////////////////////////////
void run();

////////////////////////////////////////////////////////////////////////////////
// Initializes the destruction of all software modules.
////////////////////////////////////////////////////////////////////////////////
void deinit();

///////////////////////////////////////////////////////////////////////////////
// private function implementations

int main(int argc, char* argv[])
{
	if(init(argc, argv))
		run();

	if(any_equal(argv, argc, "-nogui"))
	{
		while( 1==1 );
	}
	else
	{
		gui_run();
	}
	
	deinit();

	log_debug("exit program");
	return 0;
}

bool init(int argc, char *argv[])
{
	if(any_equal(argv, argc, "-gui"))
	{
		printf("Initialize graphical interface ... ");
		if(!wnd_init())
		{
			printf("failed\n");
			return false;
		}
	}
	else if(any_equal(argv, argc, "-nogui"))
	{
		printf("Initialize without interface ... ");
	}
	else
	{
		printf("Initialize console interface ... ");
		if(!con_init())
		{
			printf("failed\n");
			return false;
		}
	}
	
	log_init(); // If something goes wrong here, it is normally no reason 
		    // interrupt the startup process. So the check is omitted

#ifdef DESKTOP
	log_debug("Emulating hardware. Start in desktop mode");
#endif

	if(any_equal(argv, argc, "-nonet"))
		log_debug("Start without net module");
	else
	{
		if(!net_init())
		{
			log_error("Failed to load net module");
			return false;
		}

		log_debug("Loaded Net Module");
	}

	if(any_equal(argv, argc, "-nomux"))
		log_debug("Start without mux module");
	else
	{
		if(!mux_init())
		{
			log_error("Failed to load mux module");
			return false;
		}

		log_debug("Loaded Mux Module");
	}

	gui_set_status("Loading complete");
	return true;
}

void run()
{
	log_debug("Starting threads ...");

	mux_run();
	net_run();
}

void deinit()
{
	net_close();
	mux_deinit();
	gui_deinit();
}

bool any_equal(char *src[], int count, char *str)
{
	for(int i = 0 ; i < count ; i++)
		if(strcmp(str, src[i]) == 0)
			return true;

	return false;
}

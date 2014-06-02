#include "mono.h"

///////////////////////////////////////////////////////////////////////////////
// module private variables

static bool mono_initialized=false;
static pthread_mutex_t thread_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_t mono_thread;
static mux_pixel_t mono_color;
uint16_t mono_ontime, mono_offtime;

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//private function declaration

///////////////////////////////////////////////////////////////////////////////
// Thread function of the module. Controls the mux modul and changes color and
// and on/off time.
//
// PARA: 
//	void * unnamed: needed to match the thread entry point method signature
//			but is not used. Passed data will be ignored.
//	return value:	is also not used, function will not return anything
///////////////////////////////////////////////////////////////////////////////
void *mono_run_thread(void *);

///////////////////////////////////////////////////////////////////////////////
// public function implementation
///////////////////////////////////////////////////////////////////////////////

bool mono_init()
{
	if(pthread_create(&mono_thread, NULL, mono_run_thread, NULL) != 0)
	{
		log_error("Unable to create the mono thread");
		return false;
	}
	
	DRAW_CLEAR();
	mux_swap_buffer();

	mono_initialized = true;
	return true;
}

void mono_mono(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	if(!mono_initialized) return;

	if(len == 0)
	{
		//Client wants curren color and blink values
		const int16_t data_len = 7;
		uint8_t data_to_send [data_len] = {
						    mono_color.r, 
						    mono_color.g, 
						    mono_color.b,
						    mono_ontime>>8, mono_ontime & 0xFF,
						    mono_offtime>>8, mono_offtime & 0xFF
				     		  };		

		net_send(sender,fc|0x8000,data_len,data_to_send);
	}
	else if(len == 7)
	{
		//Client want to set new value to led wall 

		if((data[0] >  MUX_COLOR_DEPTH)||(data[1] >  MUX_COLOR_DEPTH)||(data[2] >  MUX_COLOR_DEPTH))
		{
			net_senderror(sender, MODULE_ID_GMM, ERR_CODES_UNEXPECTED_PAYLOAD, len, data);	
			return;
		}	

		pthread_mutex_lock(&thread_lock);

		mono_color.r = data[0];
		mono_color.g = data[1];
		mono_color.b = data[2];

		mono_ontime = data[3] << 8 | data[4];
		mono_offtime = data[5] << 8 | data[6];

		if(mono_ontime < MONO_THRESHOLD || mono_offtime < MONO_THRESHOLD)
		{
			DRAW_FILL(mono_color.r, mono_color.g, mono_color.b);
			mux_swap_buffer();
		}

		pthread_mutex_unlock(&thread_lock);
	}
	else
	{
		log_error("Incorrect data length for mono_mono");
	}
}

void mono_deinit()
{
	if(!mono_initialized) return;
	mono_initialized = false;
	pthread_cancel(mono_thread);

	log_debug("mono thread stopped");
}

///////////////////////////////////////////////////////////////////////////////
// privatee function implemenatation
///////////////////////////////////////////////////////////////////////////////
void *mono_run_thread(void *)
{
	log_debug("Mono modul thread started");
	
	while(true)
	{
		if(mono_ontime >= MONO_THRESHOLD)
		{
			pthread_mutex_lock(&thread_lock);	
	
				DRAW_FILL(mono_color.r, mono_color.g, mono_color.b);
				mux_swap_buffer();

			pthread_mutex_unlock(&thread_lock);

			usleep(mono_ontime*1000);

			if(mono_offtime >= MONO_THRESHOLD)
			{
				DRAW_CLEAR();
				mux_swap_buffer();
				usleep(mono_offtime*1000);
			}
		}
		usleep(10*1000);
	}
}

#include "plasma.h"

#define CROP_LIMIT(val, min, max)	( (val) <= (min) ? (min) : (val) >= (max) ? (max) : (val) )
#define CROP(val)			CROP_LIMIT(val, 0, 1)
#define NOT_NULL(val, action)		(val) == 0 ? 0 : (action)

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

static plasma_var_t plasma_step              = .0;
static plasma_var_t plasma_step_size         = .1;
static plasma_var_t plasma_period            = M_PI / 7.5;

static plasma_var_t plasma_concentric_scale  		= 2500.0;
static plasma_var_t plasma_concentric_speed  		= 4.0;
static plasma_var_t plasma_concentric_horizontal 	= 5.0;
static plasma_var_t plasma_concentric_vertical 		= 3.0;
static plasma_var_t plasma_concentric_lissajour_a 	= 2.0;
static plasma_var_t plasma_concentric_lissajour_b 	= 3.0;
static plasma_var_t plasma_concentric_lissajour_sigma 	= M_PI_2;

static plasma_color_t plasma_color   = PLASMA_RED_GREEN;
static plasma_method_t plasma_method = PLASMA_ADD;

static bool plasma_invert = false;

static bool plasma_initialized = false;

static pthread_mutex_t plasma_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_t plasma_thread;

///////////////////////////////////////////////////////////////////////////////
//private function declaration

plasma_var_t plasma_sin(plasma_var_t pos);
plasma_var_t plasma_cos(plasma_var_t pos);
plasma_var_t plasma_sqrt(plasma_var_t val);

void plasma_calc_color(plasma_var_t sat, p_plasma_var_t r, p_plasma_var_t g, p_plasma_var_t b);

plasma_var_t plasma_sat(uint8_t x, uint8_t y);

plasma_var_t plasma_sinusoid1(uint8_t x);
plasma_var_t plasma_sinusoid2(uint8_t x, uint8_t y);
plasma_var_t plasma_concentric(uint8_t x, uint8_t y);

///////////////////////////////////////////////////////////////////////////////
// Thread function of the module. Calculates the plasmalike movement and 
// updates the color matrix.
//
// PARA: 
//	void * unnamed: needed to match the thread entry point method signature
//			but is not used. Passed data will be ignored.
//	return value:	is also not used, function will not return anything
///////////////////////////////////////////////////////////////////////////////
void *plasma_run_thread(void *);

///////////////////////////////////////////////////////////////////////////////
// public function implementation
///////////////////////////////////////////////////////////////////////////////

bool plasma_init()
{
	if(pthread_create(&plasma_thread, NULL, plasma_run_thread, NULL) != 0)
	{
		log_error("Unable to create the plasma thread");

		plasma_initialized = false;
		return false;
	}
		
	plasma_initialized = true;
	return true;
}

void plasma_deinit()
{
	if(!plasma_initialized) return;
	plasma_initialized = false;
	pthread_cancel(plasma_thread);
}

void MsgPlasma_Change(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	if(!plasma_initialized) return;

	if(len==0)
	{
		//Send current plasma settings to client

		uint8_t data_to_send[16];

		//flag byte

		uint8_t flags = 0; 

		if(plasma_invert) flags += 128;
		flags += (plasma_method<<2);
		flags += plasma_color;
		
		data_to_send[0] = flags;

		float tmp;
		
		WRITE(&data_to_send[1],plasma_concentric_scale);
		WRITE(&data_to_send[5],plasma_concentric_speed);
		WRITE(&data_to_send[9],plasma_period);
		WRITE(&data_to_send[13],plasma_step_size);

		net_send(sender,fc|0x8000,16,data_to_send);
	}
	else if(len==16)
	{
		//Set new plasma settings
		
		//flag byte
		if(data[0]>=0x80) plasma_invert = true;
		else plasma_invert = false;

		plasma_method = (plasma_method_t)((data[0]&0x1C)>>2);
		plasma_color = (plasma_color_t)(data[0]&0x03);

		float tmp;

		//concentric scale
		memcpy((void*) &tmp, &data[1],4);
		plasma_concentric_scale = (plasma_var_t) tmp;
		
		// concentric speed
		memcpy((void*) &tmp, &data[5],4);
		plasma_concentric_speed = (plasma_var_t) tmp;

		//period
		memcpy((void*) &tmp, &data[9],4);
		plasma_period = (plasma_var_t) tmp;
		
		//speed
		memcpy((void*) &tmp, &data[13],4);
		plasma_step_size = (plasma_var_t) tmp;
	}
	else
	{
		log_error("Wrong message length. Discard Message");
	}
}

///////////////////////////////////////////////////////////////////////////////
// privatee function implemenatation
///////////////////////////////////////////////////////////////////////////////
void *plasma_run_thread(void *)
{
	for(;;)
	{
		plasma_step += plasma_step_size;
	
		for( int x=0 ; x<MUX_WIDTH ; ++x )
			for( int y=0 ; y<MUX_HEIGHT ; ++y )		
			{
				plasma_var_t r = .0;
				plasma_var_t g = .0; 
				plasma_var_t b = .0;

				plasma_calc_color( plasma_sat( x, y ), &r, &g, &b );

				if(plasma_invert)
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
		
		mux_swap_buffer();
		usleep( PLASMA_SLEEP );
	}	
}

plasma_var_t plasma_sin(plasma_var_t pos)
{
	return (plasma_var_t) sin( (double) pos);
}

plasma_var_t plasma_cos(plasma_var_t pos)
{
	return plasma_sin( pos + M_PI_2 );
}

void plasma_calc_color(plasma_var_t sat, p_plasma_var_t r, p_plasma_var_t g, p_plasma_var_t b)
{
	switch( plasma_color )
	{
		case PLASMA_RED_GREEN:
			*r = plasma_sin( sat * M_PI ); 
			*g = plasma_cos( sat * M_PI );
			*b = .0;
		break;

		case PLASMA_GREEN_BLUE:
			*r = 1.0;
			*g = plasma_cos( sat * M_PI );
			*b = plasma_sin( sat * M_PI );
		break;

		case PLASMA_RGB:
			*r = plasma_sin( sat * 1 * M_PI );
			*g = plasma_sin( sat * 2 * M_PI / 3 );
			*b = plasma_sin( sat * 4 * M_PI / 3 );
		break;

		case PLASMA_GREY:
			*r = *g = *b = plasma_cos( sat * M_PI );
		break;

		default:
			*r = *g = *b = .0;
	}

	*r = (*r + 1) / 2;
	*g = (*g + 1) / 2;
	*b = (*b + 1) / 2; 
}

plasma_var_t plasma_sat(uint8_t x, uint8_t y)
{
	plasma_var_t sinusoid1  = plasma_sinusoid1 ( x    );
	plasma_var_t sinusoid2  = plasma_sinusoid2 ( x, y );
	plasma_var_t concentric = plasma_concentric( x, y );
	plasma_var_t ret;
	
	switch( plasma_method )
	{
		case PLASMA_ADD:
			ret = (sinusoid1 + sinusoid2 + concentric + 1) / 2;
		break;

		case PLASMA_MULTIPLY:
			ret = (sinusoid1 * sinusoid2 * concentric + 1) / 2; 
		break;

		case PLASMA_SUBTRACT:
			ret = (1 - sinusoid1 - sinusoid2 - concentric - 1) / 2;
		break;

		case PLASMA_ADD_FLAT:
			ret = ( fabs( (double) sinusoid1 ) + fabs( (double) sinusoid2 ) + fabs( (double) concentric ) ) / 3;
		break;

		case PLASMA_DIVIDE:
			ret = ( NOT_NULL( sinusoid1, 1/sinusoid1 ) * NOT_NULL( sinusoid2, 1/sinusoid2 ) * NOT_NULL( concentric, 1/concentric ) + 1 ) / 2;
		break;

		default:
			ret = .0;
	}

	return ret;
}

plasma_var_t plasma_sinusoid1(uint8_t x)
{
 	return plasma_sin( x * plasma_period + plasma_step );
}

plasma_var_t plasma_sinusoid2(uint8_t x, uint8_t y)
{
	plasma_var_t calc = x * plasma_sin( plasma_step / PLASMA_X_STEP) +
			    y * plasma_sin( plasma_step / PLASMA_Y_STEP);
	return plasma_sin( calc * plasma_period + plasma_step );
}

plasma_var_t plasma_concentric(uint8_t x, uint8_t y)
{
	plasma_var_t cx = x + .5 * plasma_sin( plasma_step / plasma_concentric_horizontal ) - 
			  (15 * plasma_sin( plasma_concentric_lissajour_a * ( plasma_step / plasma_concentric_speed ) + plasma_concentric_lissajour_sigma ) + 15);
	plasma_var_t cy = y + .5 * plasma_cos( plasma_step / plasma_concentric_vertical ) - 
			  (15 * plasma_sin( plasma_concentric_lissajour_b * ( plasma_step / plasma_concentric_speed ) ) + 15);

	return plasma_sin( plasma_sqrt( plasma_concentric_scale + cx * cx + cy * cy + 1 ) + plasma_step );
}

plasma_var_t plasma_sqrt(plasma_var_t val)
{
	return (plasma_var_t) sqrt( (double) val );
}

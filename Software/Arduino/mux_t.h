#ifndef _H_MUX_T_
#define _H_MUX_T_

////////////////////////////////////////////////////////////////////////////////
// includes
#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"
 
#include "mux_defines.h"

////////////////////////////////////////////////////////////////////////////////
// type declarations

typedef uint8_t mux_color_t;

typedef struct 
{
	mux_color_t  r;
	mux_color_t  g;
	mux_color_t  b;
	
} mux_pixel_t, *p_mux_pixel_t;

typedef mux_pixel_t     mux_buffer_t[MUX_HEIGHT][MUX_WIDTH];
typedef mux_pixel_t 	(*p_mux_buffer_t)[MUX_WIDTH];

#endif // _H_MUX_T_
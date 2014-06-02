#ifndef _H_MUX_TYPES_
#define _H_MUX_TYPES_

////////////////////////////////////////////////////////////////////////////////
// FILE: mux_types.h
// DESC: defines the needed datatypes the the mux module.
////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
#define MUX_VERSION	0x0102

#define MUX_COLOR_DEPTH 4
#define MUX_HEIGHT	30
#define MUX_WIDTH	30

#if !defined(TEENSY) && !defined(DESKTOP)
#	define MUX_DELAY	500 ns
#	define MUX_SHIFT_LINE_LEN 2

#	define MUX_ROW_OFFSET	0
#	define MUX_COL_OFFSET  4

#	define MUX_STCP	GPIO_10
#	define MUX_SHCP	GPIO_09

#	define MUX_MODUL_1_DS	GPIO_11
#endif

#ifdef TEENSY
#	define MUX_PORT	"/dev/ttyACM0"
#endif

#ifdef DESKTOP
#	define MUX_GL_SCREEN_WIDTH		1024	
#	define MUX_GL_SCREEN_HEIGHT		768	
#	define MUX_GL_FPS			30

# 	define MUX_GL_MARGIN_HORIZONTAL		2
#	define MUX_GL_MARGIN_VERTICAL		2
#	define MUX_GL_TILE_SIZE_HORIZONTAL	(MUX_GL_SCREEN_WIDTH / MUX_WIDTH)
#	define MUX_GL_TILE_SIZE_VERTICAL	(MUX_GL_SCREEN_HEIGHT / MUX_HEIGHT)

#	define MUX_GL_COLOR(R,G,B)		(R), (G), (B), 1.0f
#	define MUX_GL_COLOR_SCALAR		(1/(double) MUX_COLOR_DEPTH)
#	define MUX_GL_COLOR_S(R, G, B)		(R)*MUX_GL_COLOR_SCALAR, (G)*MUX_GL_COLOR_SCALAR, (B)*MUX_GL_COLOR_SCALAR
#	define MUX_GL_COLOR_PIXEL(PIXEL)	MUX_GL_COLOR_S((PIXEL).r, (PIXEL).g, (PIXEL).b)	
#	define MUX_GL_BACKGROUND_COLOR		MUX_GL_COLOR(0.7f, 0.7f, 0.7f)	

#	define MUX_GL_DELAY			(1000 / MUX_GL_FPS)

#	define MUX_GL_TO_SCREEN_COORD(X, Y)	(Y) /* - ((float)MUX_GL_SCREEN_WIDTH / 2) */,			\
						(X) /* - ((float)MUX_GL_SCREEN_HEIGHT / 2)*/
#endif

typedef uint8_t mux_color_t;

typedef struct 
{
	mux_color_t r;
	mux_color_t g;
	mux_color_t b;
} mux_pixel_t, *p_mux_pixel_t;

typedef mux_pixel_t     mux_buffer_t[MUX_HEIGHT][MUX_WIDTH];
typedef mux_pixel_t 	(*p_mux_buffer_t)[MUX_WIDTH];

#endif // _H_MUX_TYPES_

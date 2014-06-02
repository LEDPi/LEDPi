#ifndef _H_MUX_DRAWING_
#define _H_MUX_DRAWING_

////////////////////////////////////////////////////////////////////////////////
// FILE: mux_drawing.h
// DESC: Contains some hepler functions to draw on the matrix.
////////////////////////////////////////////////////////////////////////////////

#include "mux/mux.h"
#include "mux/mux_types.h"
#include "mux/draw_buffer_t.h"

#define DRAW_POINT(X, Y, R, G, B) 						\
{									\
	mux_buffer[Y][X].r = R; 					\
	mux_buffer[Y][X].g = G;						\
	mux_buffer[Y][X].b = B;						\
}		

#define DRAW_RECTANGLE(X1, Y1, X2, Y2, R, G, B)					\
{									\
	for(int i=X1  ; i<X2 ; i++)					\
		for(int j=Y1 ; j<Y2 ; j++)				\
			DRAW_POINT(i, j, R, G, B);			\
}									 

#define DRAW_FILL(R, G, B) DRAW_RECTANGLE(0, 0, MUX_WIDTH, MUX_HEIGHT, R, G, B)

#define DRAW_CLEAR()	DRAW_FILL(0, 0, 0)

void draw_picture(p_draw_buffer_t buffer);

#endif // _H_MUX_DRAWING_

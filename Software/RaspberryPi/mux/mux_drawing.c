#include "mux/mux_drawing.h"

void draw_picture(p_draw_buffer_t picture)
{
	for( int i=0 ; i<MUX_WIDTH ; ++i )
		for( int j=0 ; j<MUX_HEIGHT ; ++j )
			DRAW_POINT( i, j, picture[i][j].r * MUX_COLOR_DEPTH,
					  picture[i][j].g * MUX_COLOR_DEPTH,
					  picture[i][j].b * MUX_COLOR_DEPTH );
}

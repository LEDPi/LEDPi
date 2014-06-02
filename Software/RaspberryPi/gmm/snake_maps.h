#ifndef _H_SNAKE_MAPS_
#define _H_SNAKE_MAPS_

///////////////////////////////////////////////////////////////////////////////
// FILE: snake
// DESC: Contains the predefined snake makes
///////////////////////////////////////////////////////////////////////////////

#include "mux/mux_types.h"

typedef enum
{
	SNAKE_EMPTY 		= 0x01,
	SNAKE_ONE_BORDER 	= 0x02,
	SNAKE_MAZE_1		= 0x03,
	SNAKE_MAZE_2		= 0x04,
	SNAKE_WELCOME		= 0x05
} snake_maps_t, *p_snake_maps_t;

typedef uint8_t snake_map_t[MUX_HEIGHT][MUX_WIDTH];

extern snake_map_t snake_map_empty;
extern snake_map_t snake_map_one_border;
extern snake_map_t snake_map_maze_1;
extern snake_map_t snake_map_maze_2;
extern snake_map_t snake_map_welcome;

#endif // _H_SNAKE_MAPS_

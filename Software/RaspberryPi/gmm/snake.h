#ifndef _SNAKE_H_
#define _SNAKE_H_

///////////////////////////////////////////////////////////////////////////////
// FILE: snake
// DESC: Simple snake game
///////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#include "mux/mux.h"
#include "mux/mux_drawing.h"
#include "gui/logger.h"
#include "module_id.h"
#include "net/net.h"
#include "utils/llist.h"

#include "gmm/snake_maps.h"

#define SNAKE_VERSION 0x0106

#define SNAKE_START_LEN	5
#define SNAKE_START_SPEED 200	// [ms]
#define SNAKE_MIN_SPEED	50
#define SNAKE_DELTA	20

#define SNAKE_RARE_FOOD_DELTA 0.5f
#define SNAKE_RARE_FOOD_TIME 31

typedef enum
{
	SNAKE_UP 	= 0x01,
	SNAKE_RIGHT	= 0x02,
	SNAKE_DOWN	= 0x03,
	SNAKE_LEFT	= 0x04

} snake_dir_t, *p_snake_dir_t;

typedef enum
{
	SNAKE_WALL 	= 0x01,
	SNAKE_SNAKE 	= 0x02,
	SNAKE_FOOD 	= 0x03,
	SNAKE_RARE_FOOD = 0x04

} snake_tile_t, *p_snake_tile_t;

typedef struct
{
	float r;
	float g; 
	float b;

} snake_color_t, *p_snake_color_t;

typedef struct 
{
	int8_t x;
	int8_t y;

} snake_part_t, *p_snake_part_t;

///////////////////////////////////////////////////////////////////////////////
// Creates a new thread and starts to control the led wall 
///////////////////////////////////////////////////////////////////////////////
bool snake_init();

///////////////////////////////////////////////////////////////////////////////
// Starts a new snake game with the given map.
///////////////////////////////////////////////////////////////////////////////
void MsgSnake_Start(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);

///////////////////////////////////////////////////////////////////////////////
// Starts a new snake game with the given map.
///////////////////////////////////////////////////////////////////////////////
void MsgSnake_Direction(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);

///////////////////////////////////////////////////////////////////////////////
// Stop the thread and clear resources
///////////////////////////////////////////////////////////////////////////////
void snake_deinit();

#endif //_MONO_H_

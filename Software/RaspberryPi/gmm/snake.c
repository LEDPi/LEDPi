#include "snake.h"

///////////////////////////////////////////////////////////////////////////////
// module private variables

static pthread_t snake_thread;

static snake_map_t snake_map;
static bool snake_alive = false;
static bool snake_toggle = false;

static p_ll_list_t snake = NULL;
static snake_dir_t snake_direction = SNAKE_RIGHT;
static snake_dir_t snake_new_direction = SNAKE_RIGHT;

static uint32_t snake_speed = SNAKE_START_SPEED;
static float snake_food_timer = .0f;

static snake_part_t snake_food;
static snake_part_t snake_rare_food;

static const snake_color_t color_snake 		= { .1f, .2f, .8f };
static const snake_color_t color_wall  		= { .9f, .9f, .9f };
static const snake_color_t color_food 		= { .8f, .8f, .2f };
static const snake_color_t color_rare_food 	= { .0f, .8f, .8f };

///////////////////////////////////////////////////////////////////////////////
//private function declaration

void snake_start_game(uint8_t map);
void snake_delete_element(void *element);
void snake_simulate();
void snake_draw();
bool snake_move_head(p_snake_part_t part);
void snake_eat();
void snake_eat_rare();
void snake_create_food();
void snake_create_rare_food();
void snake_simulate_rare_food();
void snake_speed_up();

///////////////////////////////////////////////////////////////////////////////
// Thread function of the module. Controls the mux modul and changes color and
// and on/off time.
//
// PARA: 
//	void * unnamed: needed to match the thread entry point method signature
//			but is not used. Passed data will be ignored.
//	return value:	is also not used, function will not return anything
///////////////////////////////////////////////////////////////////////////////
void *snake_run_thread(void *);

///////////////////////////////////////////////////////////////////////////////
// public function implementation
///////////////////////////////////////////////////////////////////////////////

bool snake_init()
{
	memcpy( snake_map, snake_map_welcome, sizeof( snake_map_t ));
	
	if( snake != NULL )
		ll_delete( snake );
	
	snake_alive = false;
	snake_new_direction = snake_direction = SNAKE_RIGHT;
	snake_speed = SNAKE_START_SPEED;
	snake_food_timer = .0f;

	snake_draw();

	if(pthread_create(&snake_thread, NULL, snake_run_thread, NULL) != 0)
	{
		log_error("Unable to create the snake thread");
		return false;
	}

	return true;
}

void MsgSnake_Start(void *sender, uint16_t fc, uint16_t len, uint8_t data[]) 
{
	if(len != 1)
	{
		net_senderror(sender, MODULE_ID_SNAKE, ERR_CODES_UNEXPECTED_PAYLOAD, len, data);	
		return;
	}

	snake_start_game( data[0] );
}

void MsgSnake_Direction(void *sender, uint16_t fc, uint16_t len, uint8_t data[]) 
{
	if(len != 1 || data[0] == 0x00 || data[0] > 0x04 )
	{
		net_senderror(sender, MODULE_ID_SNAKE, ERR_CODES_UNEXPECTED_PAYLOAD, len, data);	
		return;
	}

	if( (snake_direction == SNAKE_RIGHT && data[0] != SNAKE_LEFT ) ||
	    (snake_direction == SNAKE_LEFT  && data[0] != SNAKE_RIGHT) || 
	    (snake_direction == SNAKE_UP    && data[0] != SNAKE_DOWN ) ||
            (snake_direction == SNAKE_DOWN  && data[0] != SNAKE_UP   ) )
		snake_new_direction = (snake_dir_t) data[0];
}

void snake_deinit()
{
	pthread_cancel(snake_thread);
	log_debug("snake thread cancelled");
}

///////////////////////////////////////////////////////////////////////////////
// private function implemenatation
///////////////////////////////////////////////////////////////////////////////
void *snake_run_thread(void *)
{
	while( true )
	{
		snake_toggle = !snake_toggle;
		
		snake_direction = snake_new_direction;

		snake_simulate();
		snake_draw();
		usleep( snake_speed * 1000 );
	} 
}

void snake_start_game(uint8_t map)
{
	srand( time( NULL) );

	switch(map)
	{
		case SNAKE_EMPTY:
			memcpy( snake_map, snake_map_empty,	 sizeof( snake_map_t ) );
		break;
		case SNAKE_ONE_BORDER:
			memcpy( snake_map, snake_map_one_border, sizeof( snake_map_t ) );
		break;
		case SNAKE_MAZE_1:
			memcpy( snake_map, snake_map_maze_1,     sizeof( snake_map_t ) );
		break;
		case SNAKE_MAZE_2:
			memcpy( snake_map, snake_map_maze_2,     sizeof( snake_map_t ) );
		break;
		default:
			memset( snake_map, 0x00, sizeof( snake_map_t ) );
	} 
	
	if( snake != NULL )
		ll_delete( snake );

	snake = ll_create( snake_delete_element );
	for( int i=0 ; i<=SNAKE_START_LEN ; ++i)
	{
		log_debug("snake part added");

		p_snake_part_t element = (p_snake_part_t) malloc( sizeof( snake_part_t ) );
		element->x = 15;
		element->y = 15;
		ll_append( snake, (void *) element ); 
	}	

	snake_create_food();
	snake_speed = SNAKE_START_SPEED;
	snake_direction = SNAKE_RIGHT;
	snake_new_direction = SNAKE_RIGHT;
	snake_food_timer = .0f;

	snake_alive = true;
}

void snake_delete_element(void *element)
{
	if( element != NULL)
		free( element );
}

void snake_draw()
{
	DRAW_CLEAR();

	for(int i=0 ; i<MUX_HEIGHT-1 ; ++i)
	{
		for(int j=0 ; j<MUX_WIDTH ; ++j)
		{
			switch(snake_map[i][j])
			{
				case SNAKE_WALL: // WALL
					DRAW_POINT( i, j, color_wall.r * MUX_COLOR_DEPTH,
							  color_wall.g * MUX_COLOR_DEPTH,
							  color_wall.b * MUX_COLOR_DEPTH );
				break;
		
				case SNAKE_SNAKE: // SNAKE
					if( snake_alive || snake_toggle )
					{
						DRAW_POINT( i, j, color_snake.r * MUX_COLOR_DEPTH,
							  color_snake.g * MUX_COLOR_DEPTH,
							  color_snake.b * MUX_COLOR_DEPTH );
					}
				break;

				case SNAKE_FOOD: // FOOD
					DRAW_POINT( i, j, color_food.r * MUX_COLOR_DEPTH,
							  color_food.g * MUX_COLOR_DEPTH,
							  color_food.b * MUX_COLOR_DEPTH );
				break;

				case SNAKE_RARE_FOOD: // RARE FOOD
					DRAW_POINT( i, j, color_rare_food.r * MUX_COLOR_DEPTH,
							  color_rare_food.g * MUX_COLOR_DEPTH,
							  color_rare_food.b * MUX_COLOR_DEPTH ); 
				break;

				default: DRAW_POINT( i, j, 0x00, 0x00, 0x00 ); 
			}
		}
	}

	// for( int i=0 ; i<30 ; ++i)
	//	DRAW_POINT(29, i, 0, 0, 0);	

	if(snake_food_timer > 0)
		for( int i=0 ; i<(30 - snake_food_timer) ; ++i)
			if( i <= 15 )
			{
				DRAW_POINT(29, i, 
					((float)1/15) * i * MUX_COLOR_DEPTH, 
					MUX_COLOR_DEPTH, 0);
			}
			else
			{
				DRAW_POINT(29, i, 
					MUX_COLOR_DEPTH, 
					(1 - (((float)i - 15)/15)) * MUX_COLOR_DEPTH, 0);
			}

	mux_swap_buffer();
}

void snake_simulate()
{
	if( !snake_alive ) return;
	
	ll_first( snake );
	ll_next( snake );

	snake_part_t prev = *((p_snake_part_t) ll_get( snake ));
	snake_map[prev.x][prev.y] = 0x00;
	if( snake_move_head( (p_snake_part_t) ll_get( snake ) ) )
	{
		snake_map[prev.x][prev.y] = SNAKE_SNAKE;
	
		while( ll_next( snake ) )
		{
			p_snake_part_t item = (p_snake_part_t) ll_get( snake );

			if( item->x >= 0 && item->y >= 0 )
				snake_map[item->x][item->y] = 0x00;

			snake_part_t prev_cpy = prev;
			prev = *item;
			item->x = prev_cpy.x;
			item->y = prev_cpy.y;

			if( item->x >= 0 && item->y >= 0 )
				snake_map[item->x][item->y] = SNAKE_SNAKE;
	 	} 
		
		snake_simulate_rare_food();		
	}
}

void snake_simulate_rare_food()
{
		if( snake_food_timer > 0 )
		{
			snake_food_timer -= SNAKE_RARE_FOOD_DELTA;
			if( snake_food_timer <= 0)
			{
				for( int i=0 ; i<3 ; ++i )
				for( int j=0 ; j<3 ; ++j )
					snake_map[snake_rare_food.x + i][snake_rare_food.y + j] = 0x00;
			}
		}
		else 
		{
			if( (rand() %  1000)  < 5) 
			{
				snake_food_timer = SNAKE_RARE_FOOD_TIME;
				snake_create_rare_food();
			}
		}		
}

bool snake_move_head(p_snake_part_t part)
{
	int8_t x = part->x;
	int8_t y = part->y;

	switch( snake_direction )
	{
		case SNAKE_UP:
			if( --x < 0 ) x = MUX_HEIGHT-2;
		break;

		case SNAKE_DOWN:
			if( ++x > MUX_HEIGHT-2 ) x = 0;
		break;

		case SNAKE_LEFT:
			if( --y < 0 ) y = MUX_WIDTH - 1;
		break;

		case SNAKE_RIGHT:
			if( ++y > MUX_WIDTH - 1 ) y = 0;
		break;
	}

	if( snake_map[x][y] != 0)
	{
		if( snake_map[x][y] == SNAKE_FOOD )
			snake_eat();			
		else if( snake_map[x][y] == SNAKE_RARE_FOOD )
			snake_eat_rare();	
		else
		{
			snake_alive = false;
		}	
	}

	part->x = x;
	part->y = y;

	return true;
}

void snake_eat()
{
	p_snake_part_t element = (p_snake_part_t) malloc( sizeof( snake_part_t ) );
	element->x = element->y = -5;
	ll_append( snake, element );

	snake_create_food();
	
	snake_speed_up();
}

void snake_eat_rare()
{
	snake_food_timer = 0;

	for( int i=0 ; i<3 ; ++i)
	{
		p_snake_part_t element = (p_snake_part_t) malloc( sizeof( snake_part_t ) );
		element->x = element->y = -5;
		ll_append( snake, element );
	}

	for( int i=0 ; i<3 ; ++i)
		for(int j=0 ; j<3 ; ++j )
			snake_map[snake_rare_food.x + i][snake_rare_food.y + j] = 0x00;

	snake_speed_up();
}

void snake_create_food()
{
	do
	{
		snake_food.x = rand() % 29;
		snake_food.y = rand() % 30;

	} while( snake_map[snake_food.x][snake_food.y] != 0x00 );
	
	snake_map[snake_food.x][snake_food.y] = SNAKE_FOOD;

	log_debug("Food at %d.%d", snake_food.x, snake_food.y);
}

void snake_create_rare_food()
{
	bool cont = true;
	do
	{
		snake_rare_food.x = rand() % 26;
		snake_rare_food.y = rand() % 27;

		cont = false;
		for( int i=0 ; i<3 ; ++i)
			for(int j=0 ; j<3 ; ++j )
				if( snake_map[snake_rare_food.x + i][snake_rare_food.y + j] 
					!= 0x00 )
					cont = true;
	} while( cont );

	for( int i=0 ; i<3 ; ++i)
		for(int j=0 ; j<3 ; ++j )
			snake_map[snake_rare_food.x + i][snake_rare_food.y + j] = SNAKE_RARE_FOOD;

	log_debug("Rare Food at %d.%d", snake_food.x, snake_food.y);
}

void snake_speed_up()
{
	snake_speed -= SNAKE_DELTA;
	if( snake_speed < SNAKE_MIN_SPEED )
		snake_speed = SNAKE_MIN_SPEED;

}

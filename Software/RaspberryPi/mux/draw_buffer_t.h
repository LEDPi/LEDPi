#ifndef _DRAW_BUFFER_T_H_
#define _DRAW_BUFFER_T_H_

typedef struct
{
	float r;
	float g;
	float b;
} draw_color_t, *p_draw_color_t;

typedef draw_color_t draw_buffer_t[MUX_HEIGHT][MUX_WIDTH];
typedef draw_color_t (*p_draw_buffer_t)[MUX_WIDTH];

#endif // _DRAW_BUFFER_T_H_

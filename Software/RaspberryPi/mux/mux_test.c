#include "mux_test.h"

void mux_test_fill(mux_color_t r, mux_color_t g, mux_color_t b)
{
	DRAW_FILL(r, g, b);
	mux_request_swap_buffer();
	mux_wait_swap_buffer();
}

void mux_test_red()
{
	mux_test_fill(MUX_COLOR_DEPTH, 0, 0);
}

void mux_test_green()
{
	mux_test_fill(0, MUX_COLOR_DEPTH, 0);
}

void mux_test_blue()
{
	mux_test_fill(0, 0, MUX_COLOR_DEPTH);
}

void mux_test_white()
{
	mux_test_fill(MUX_COLOR_DEPTH, MUX_COLOR_DEPTH, MUX_COLOR_DEPTH);
}

void mux_test_off()
{
	mux_test_fill(0, 0, 0);
}

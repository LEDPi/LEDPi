#ifndef _H_MUX_
#define _H_MUX_

////////////////////////////////////////////////////////////////////////////////
// FILE: mux
// DESC: Controls the led matrix.
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>

#ifdef DESKTOP
#	include <GL/freeglut.h>
#	include <GL/gl.h>
#	include <GL/glu.h>
#endif

#ifdef TEENSY
#	include <stdio.h>
#	include <string.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#	include <fcntl.h>
#	include <unistd.h>
#	include <termios.h>
#endif

#include "gui/logger.h"
#include "mux/mux_debug.h"
#include "mux/gpio.h"
#include "mux/shift.h"
#include "mux/shiftmgr.h"
#include "utils/llist.h"
#include "mux/units.h"
#include "mux/mux_types.h"
#include "gmm/photo_photo.h"

////////////////////////////////////////////////////////////////////////////////
// Function declaration

bool mux_init();
void mux_deinit();
void mux_run();
void mux_swap_buffer();
void mux_request_swap_buffer();
void mux_wait_swap_buffer();

extern p_mux_buffer_t mux_buffer;

#endif // _H_MUX_

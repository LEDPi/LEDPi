#ifndef _H_MUX_
#define _H_MUX_

////////////////////////////////////////////////////////////////////////////////
// includes

#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"

#include "mux_defines.h"
#include "mux_t.h"

#include "shift_t.h"
#include "shift.h"
#include "shiftmgr_t.h"
#include "shiftmgr.h"
#include "default.h"

////////////////////////////////////////////////////////////////////////////////
// extern variable forward declarations

volatile extern p_mux_buffer_t mux_rec_buffer;

////////////////////////////////////////////////////////////////////////////////
// Function declarations

void mux_init();
void mux_swap();
void mux_plex();

#endif // _H_MUX_
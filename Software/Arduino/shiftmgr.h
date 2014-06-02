#ifndef _H_SHIFT_MGR_
#define _H_SHIFT_MGR_

////////////////////////////////////////////////////////////////////////////////
// includes

#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"

#include "mux_defines.h"

#include "shift_t.h"
#include "shift.h"

#include "shiftmgr_t.h"

////////////////////////////////////////////////////////////////////////////////
// Function declarations

////////////////////////////////////////////////////////////////////////////////
/// Writes the data for each shift register line to their shift register.
///
/// PARA:
///	mgr:	the shift register manager pointer
////////////////////////////////////////////////////////////////////////////////
extern "C" void shift_mgr_write(p_shift_mgr_t mgr);

////////////////////////////////////////////////////////////////////////////////
/// Activates the previously written data and switches it to the output pins.
///
/// PARA:
///	mgr:	the shift register manager pointer
////////////////////////////////////////////////////////////////////////////////
extern "C" void shift_mgr_activate(p_shift_mgr_t mgr);

#endif // _H_SHIFT_MGR_
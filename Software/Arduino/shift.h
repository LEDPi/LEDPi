#ifndef _H_SHIFT_
#define _H_SHIFT_

////////////////////////////////////////////////////////////////////////////////
// includes
#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"
 
#include "mux_defines.h"
#include "shift_t.h"

////////////////////////////////////////////////////////////////////////////////
// Function declarations

inline void shift_set_pin(p_shift_t reg, uint32_t register_no, uint8_t bit)
{
	if(register_no < reg->Size)
		digitalWriteFast(reg->DS, (reg->Data[register_no] & (1 << bit)));
} 

#endif // _H_SHIFT_
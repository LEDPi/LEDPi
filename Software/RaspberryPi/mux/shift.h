#ifndef _H_SHIFT_
#define _H_SHIFT_

////////////////////////////////////////////////////////////////////////////////
/// FILE: shift
/// DESC: Sets all io pins for one shift register line of any length. Needs the
///	  shift manager to control the given shift register lines. This means
///	  all shift register lines have the same clock (SHCP and STCP) pins.
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdint.h>

#include "mux/gpio_pin.h"
#include "mux/mux_debug.h"
#include "mux/gpio.h"
#include "mux/shift_register_t.h"

////////////////////////////////////////////////////////////////////////////////
/// Creates a shift register line and initializes the output pin.
/// 
/// PARA:
///	size:	the number of shift registers on this shift register line
///	ds:	the serial input pin of the shift register line 
////////////////////////////////////////////////////////////////////////////////
p_shift_register_t shift_create(uint32_t size, gpio_pin_t ds);

////////////////////////////////////////////////////////////////////////////////
/// Deletets the shift register line and frees the memory.
///
/// PARA:
///	reg:	the shift register pointer
////////////////////////////////////////////////////////////////////////////////
void shift_delete(p_shift_register_t reg);

////////////////////////////////////////////////////////////////////////////////
/// Sets the given bit to the serial output pin (DS).
///
/// PARA:
///	reg:		the shift register pointer
///	registerNo:	the shift register number
///	bit:		the bit number
////////////////////////////////////////////////////////////////////////////////
void shift_set_pin(p_shift_register_t reg, uint32_t register_no, uint8_t bit);

#endif // _H_SHIFT_

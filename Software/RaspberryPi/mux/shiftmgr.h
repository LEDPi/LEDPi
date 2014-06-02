#ifndef _H_SHIFT_MGR_
#define _H_SHIFT_MGR_

////////////////////////////////////////////////////////////////////////////////
// FILE: shift manager
// DESC: Handles all attached shift register lines wich have common clock pins
//	 (SHCP and SCTP). Write will write the data to the shift registers. 
//	 Activate will switch the previously written data to the output pins. 
////////////////////////////////////////////////////////////////////////////////
 
#include <stdint.h> 
#include <stdlib.h>

#include "mux/gpio_pin.h"
#include "mux/shift_register_t.h"
#include "mux/mux_debug.h"
#include "mux/gpio.h"
#include "mux/shift.h"
#include "utils/llist.h"

typedef struct
{
	p_ll_list_t ShiftRegister;
	uint32_t MaxRegisterLen;
	bool Written;
	gpio_pin_t SHCP;
	gpio_pin_t STCP;
} shift_mgr_t, *p_shift_mgr_t;

////////////////////////////////////////////////////////////////////////////////
/// Creates a new shift register manager and initalizes the output pins.
///
/// PARA:
///	schp:	the shift register clock
///	stcp: 	the storage clock
//////////////////////////////////////////////////////////////////////////////// 
p_shift_mgr_t shift_mgr_create(gpio_pin_t shcp, gpio_pin_t stcp);

////////////////////////////////////////////////////////////////////////////////
/// Frees the memory of the given shift register manager.
///
/// PARA:
///	mgr:	the shift register manager pointer
////////////////////////////////////////////////////////////////////////////////
void shift_mgr_delete(p_shift_mgr_t mgr);

////////////////////////////////////////////////////////////////////////////////
/// Registers the given shift register line to  this shift register manager.
///
/// PARA:
///	mgr:	the shift register manager pointer
///	reg:	the shift register line
////////////////////////////////////////////////////////////////////////////////
void shift_mgr_register(p_shift_mgr_t mgr, p_shift_register_t reg);

////////////////////////////////////////////////////////////////////////////////
/// Writes the data for each shift register line to their shift register.
///
/// PARA:
///	mgr:	the shift register manager pointer
////////////////////////////////////////////////////////////////////////////////
void shift_mgr_write(p_shift_mgr_t mgr);

////////////////////////////////////////////////////////////////////////////////
/// Activates the previously written data and switches it to the output pins.
///
/// PARA:
///	mgr:	the shift register manager pointer
////////////////////////////////////////////////////////////////////////////////
void shift_mgr_activate(p_shift_mgr_t mgr);

#endif // _H_SHIFT_MGR_

#ifndef _H_SHIFT_MGR_T_
#define _H_SHIFT_MGR_T_

////////////////////////////////////////////////////////////////////////////////
// includes

#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"

#include "mux_defines.h"

#include "shift_t.h"

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct
{
	p_shift_t	ShiftRegister[MUX_PANEL_COUNT];
	uint8_t 	MaxRegisterLen;
	bool 		Written;
	uint8_t 	SHCP;
	uint8_t 	STCP;
	
} shift_mgr_t, * p_shift_mgr_t;

#ifdef __cplusplus
}
#endif

#endif // _H_SHIFT_MGR_T_
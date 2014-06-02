#ifndef _H_SHIFT_T_
#define _H_SHIFT_T_

////////////////////////////////////////////////////////////////////////////////
// includes
#include <stdint.h>

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"
#include "mux_defines.h"

////////////////////////////////////////////////////////////////////////////////
// type declarations

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct
{
	uint32_t 	Size					;
	uint8_t  	Data[MUX_SHIFT_LINE_LEN]; 
	uint8_t 	DS						;
	
} shift_t, * p_shift_t;

#ifdef __cplusplus
}
#endif

#endif // _H_SHIFT_T_
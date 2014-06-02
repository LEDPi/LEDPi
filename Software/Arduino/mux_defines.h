#ifndef _H_MUX_DEFINES_
#define _H_MUX_DEFINES_

////////////////////////////////////////////////////////////////////////////////
// includes

// includes a whole bunch of std. headers.
#include "teensy3/WProgram.h"
#include "teensy3/Arduino.h"

////////////////////////////////////////////////////////////////////////////////
// global defines

// matrix size
#define MUX_COLOR_DEPTH		 4
#define MUX_HEIGHT			30
#define MUX_WIDTH			30

// number of shift registers used per panel. Elements of the default value 
// need to match the shift line length
#define MUX_SHIFT_LINE_LEN   5
#define MUX_SHIFT_DEFAULT_VAL { 0x00, 0x00, 0x00, 0x00, 0x00 } 

// colum and row offets
#define MUX_ROW_OFFSET	 	 30
#define MUX_COL_OFFSET   	 0

#define MUX_PANEL_COUNT		 9

// shared clock and shift pins
#define MUX_STCP	 	  	 0
#define MUX_SHCP		 	 1

// serial data pins 
#define MUX_MODUL_0_DS	 	10
#define MUX_MODUL_1_DS	 	 9
#define MUX_MODUL_2_DS	 	 8
#define MUX_MODUL_3_DS	 	 7
#define MUX_MODUL_4_DS	 	 6
#define MUX_MODUL_5_DS	 	 5
#define MUX_MODUL_6_DS	 	 4
#define MUX_MODUL_7_DS		 3
#define MUX_MODUL_8_DS		 2

// pit0 start value
#define PIT0_LDVAL  14400 // 4800 == 100us period

#endif // _H_MUX_DEFINES_
#ifndef _PLASMA_H_
#define _PLASMA_H_

///////////////////////////////////////////////////////////////////////////////
// FILE: plasma
// DESC: Displays plasma like color movements.
///////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

#include "mux/mux.h"
#include "mux/mux_drawing.h"
#include "gui/logger.h"
#include "module_id.h"
#include "net/net.h"

#define PLASMA_VERSION 0x0101

#define PLASMA_SLEEP 0 

#define PLASMA_X_STEP 3
#define PLASMA_Y_STEP 2

typedef enum
{
	PLASMA_ADD       = 0x00,
	PLASMA_MULTIPLY  = 0x01,
	PLASMA_SUBTRACT  = 0x02,
	PLASMA_ADD_FLAT  = 0x03,
	PLASMA_DIVIDE    = 0x04

} plasma_method_t, *p_plasma_method_t;

typedef enum
{
	PLASMA_RED_GREEN   = 0x00,
	PLASMA_GREEN_BLUE  = 0x01,
	PLASMA_RGB         = 0x02,
	PLASMA_GREY        = 0x03,

} plasma_color_t, *p_plasma_color_t;

typedef double plasma_var_t;
typedef plasma_var_t *p_plasma_var_t;

///////////////////////////////////////////////////////////////////////////////
// Creates a new thread and starts to control the led wall 
///////////////////////////////////////////////////////////////////////////////
bool plasma_init();

///////////////////////////////////////////////////////////////////////////////
// The message handler function 
///////////////////////////////////////////////////////////////////////////////
void MsgPlasma_Change(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);

///////////////////////////////////////////////////////////////////////////////
// Stop the thread and clear resources
///////////////////////////////////////////////////////////////////////////////
void plasma_deinit();

#endif // _PLASMA_H_

#ifndef _H_MESSAGES_
#define _H_MESSAGES_

////////////////////////////////////////////////////////////////////////////////
// FILE: messages
// DESC: contains the messages definitions
//	 The function handler signature:
//		void handler(void *sender, fc, len, data);
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "net/msg_fc.h"
#include "net/msg_handler.h"
#include "gui/logger.h"

////////////////////////////////////////////////////////////////////////////////
// Message receive callback
// Parameter:	void *	 : sender: The sender, pass this to the send function to
//				   respond to the request.
//		uint16_t : fc	 : the received function code
//		uint16_t : len   : the number of the received data bytes
// 		uint8_t[]: data  : the data bytes 
///////////////////////////////////////////////////////////////////////////////
typedef void (*interpreter_callback_t) (void *, uint16_t, uint16_t, uint8_t[]);

typedef struct 
{
	uint16_t len_min;
	uint16_t len_max;
	interpreter_callback_t callback;
} interpreter_t, *pinterpreter_t;

////////////////////////////////////////////////////////////////////////////////
// Additional information about the messages
////////////////////////////////////////////////////////////////////////////////
extern const interpreter_t tblInterpreter[];

////////////////////////////////////////////////////////////////////////////////
// Contains the number of existing messages.
////////////////////////////////////////////////////////////////////////////////
extern uint16_t interpreterCount;

#endif // _H_MESSAGES_

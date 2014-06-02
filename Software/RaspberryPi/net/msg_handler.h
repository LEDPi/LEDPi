#ifndef _H_MSG_HANDLER_
#define _H_MSG_HANDLER_

////////////////////////////////////////////////////////////////////////////////
// FILE: msg_handler
// DESC: Include all message handler in this file.
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "main.h"
#include "net/net.h"
#include "gui/gui.h"
#include "mux/mux.h"
#include "module_id.h"


////////////////////////////////////////////////////////////////////////////////
// custom includes here
#include "gmm/gmm.h"
#include "gmm/mono.h"
#include "gmm/snake.h"
#include "gmm/photo.h"
#include "gmm/plasma.h"
#include "gmm/ball.h"

////////////////////////////////////////////////////////////////////////////////
// generic msg handler

void MsgHandlerHandshake(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);
void MsgHandlerVersionInfo(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);

#endif // _H_MSG_HANDLER_

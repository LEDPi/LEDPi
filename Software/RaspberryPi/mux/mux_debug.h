#ifndef _H_MUX_DEBUG_H
#define _H_MUX_DEBUG_H

////////////////////////////////////////////////////////////////////////////////
// FILE: mux_debug
// DESC: Creates the debug constants for the mux module.
////////////////////////////////////////////////////////////////////////////////

#include "gui/logger.h"

#if defined(DEBUG_MUX)
#	define MUX_DEBUG(msg, args...) log_debug(msg, ## args)
#else
#	define MUX_DEBUG(msg, args...)
#endif

#endif // _H_MUX_DEBUG_

#ifndef _H_GMM_
#define _H_GMM_

////////////////////////////////////////////////////////////////////////////////
// FILE: gmm.h
// DESC: the graphic module manager activates and deactivates the grahpic 
//	 modules. Each gmodule hast therefore a init and deinit function.
//	 The gmodule should use as less processing time as possible and should
//	 contain a minumum sleep of 10ms between each iteration.
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "net/net.h"
#include "gmm/mono.h"
#include "gmm/snake.h"
#include "gmm/photo.h"
#include "gmm/plasma.h"
#include "gmm/ball.h"
#include "module_id.h"
#include "gui/logger.h"

#define GMM_VERSION 0x0002

////////////////////////////////////////////////////////////////////////////////
// Retreives the current active module or changes the current acitve module.
////////////////////////////////////////////////////////////////////////////////
void gmm_change(void *sender, uint16_t fc, uint16_t len, uint8_t data[]);

////////////////////////////////////////////////////////////////////////////////
// Returns the current acite gmodule
////////////////////////////////////////////////////////////////////////////////
module_id_t gmm_active_module();

#endif // _H_GMM_

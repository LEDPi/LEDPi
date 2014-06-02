#ifndef _H_JOBSTACK_
#define _H_JOBSTACK_

///////////////////////////////////////////////////////////////////////////////
// FILE: jobstack
// DESC: Handles the communiction jobs.
// 	 Adds jobs to the stack and execute them
///////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>

#include "net/net.h"
#include "net/netsenderinfo.h"
#include "gui/gui.h"
#include "gui/logger.h"
#include "utils/llist.h"

#define JOBSTACK_SIZE 	303030 
typedef struct
{
	netsenderinfo_t senderinfo;
	uint16_t fc;
	uint16_t len;
	uint8_t *data;
	void (*function) (void *sender, uint16_t fc, uint16_t len, uint8_t* data);

} jobstackjob_t, *pjobstackjob_t;

///////////////////////////////////////////////////////////////////////////////
// Creates the jobstack and reserve memory
///////////////////////////////////////////////////////////////////////////////
bool jobstack_init();

///////////////////////////////////////////////////////////////////////////////
// Starts the jobstack thread
///////////////////////////////////////////////////////////////////////////////
void jobstack_run();

///////////////////////////////////////////////////////////////////////////////
// Frees all used memory and delete the jobstack data. 
// Terminates the jobstack thread
//////////////////////////////////////////////////////////////////////////////
void jobstack_deinit();

///////////////////////////////////////////////////////////////////////////////
// Adds a job to a jobstack
// 
// Para:
//	senderinfo: contains net_adress of the client and the fc of the received
//		    message
//	fc:	    functioncode of the to send message
//	data:	    pointer to the to send byte array
//	function:   function pointer to the desired function	
///////////////////////////////////////////////////////////////////////////////
void jobstack_addjob(netsenderinfo_t senderinfo, uint16_t fc, uint16_t len, uint8_t *data, void (*function) (void*,uint16_t, uint16_t, uint8_t*));
#endif

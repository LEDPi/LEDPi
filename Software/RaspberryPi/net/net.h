#ifndef _H_NET_
#define _H_NET_

////////////////////////////////////////////////////////////////////////////////
// FILE: net
// DESC: Handles the communication. Receives and decodes the data and calls the
//	 received message handler.
//	 Contains also functions to send data back to an client.
////////////////////////////////////////////////////////////////////////////////

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <inttypes.h>

#include "net/net_buffer.h"
#include "net/messages.h"
#include "net/error.h"
#include "net/client_type.h"
#include "net/jobstack.h"
#include "net/netsenderinfo.h"
#include "gui/gui.h"
#include "gui/logger.h"
#include "module_id.h"

#ifdef DEBUG_NET
#	define DEBUG(msg, args...) log_debug(msg, ## args)
#else
#	define DEBUG(msg, args...)
#endif

#define NET_PORT 8000
#define DEST_PORT 8100
#define NET_BUFSIZE 8192

#define NET_VERSION 0x0002


////////////////////////////////////////////////////////////////////////////////
// Initializes the network socket. Prepares the net module to receivde data.
//////////////////////////////////////////////////////////////////////////////// 
bool net_init();

////////////////////////////////////////////////////////////////////////////////
// Starts the receiving thread.
////////////////////////////////////////////////////////////////////////////////
void net_run();

////////////////////////////////////////////////////////////////////////////////
// Frees all needed memory and closes the network socket again. If "net_run" was
// started in a different thread, terminate this thread firt. Because accessing
// the receive fruntion on a closed socket can cause problems.
////////////////////////////////////////////////////////////////////////////////
void net_close();

///////////////////////////////////////////////////////////////////////////////
//Sends data to udp client. 
//
//PARA:
//	senderinfo: contains net_adress of the client
//	data:	    contains the data to send
//sending sokcet.
///////////////////////////////////////////////////////////////////////////////
void net_send(void* senderinfo, uint16_t fc, uint16_t len, uint8_t data[]);

////////////////////////////////////////////////////////////////////////////////
//Sends an error message to the udp client.
//The sent message has got the General Error Message Format
//
//Para 
//	senderinfo: contains net_adress of the client and the fc of the received
//		    message
//	module_id:  enum modul_id_t contains the modul specific id
//	error_code: enum error_code_t contains the possible error codes
////////////////////////////////////////////////////////////////////////////////
void net_senderror(void* psenderinfo, module_id_t modul_id, error_code_t error_code, uint16_t len, uint8_t data[]);

#endif // _H_NET_ 

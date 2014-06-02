#ifndef _SEND_H
#define _SEND_H

//////////////////////////////////////////////////////////////////
// FILE: send
// DESC: Creates the sockets, defines the ip destination adress
//       and port, provides the send functions
//////////////////////////////////////////////////////////////////

#include "socketHandling.h"

#define DESTINATION_IP     "192.168.0.15"         // IP adress of the the destination device
#define SEND_PORT 6789                         // Port on which the client recieves the message

int initSendSocket(socketHandle* sendeHandle);
int sendMsg(socketHandle* senderHandle);
int closeSenderSocket(int sock);
#endif



#ifndef _SERVER_H
#define _SERVER_H

#include "socketHandling.h"

#define RECIEVE_PORT 5555//6789                 // Port on which the the messages from the client come in

int initRecieveSocket(socketHandle* recieverHandle);
int recieve(socketHandle* recieverHandle);
int closeRecieverSocket(int sock);
#endif

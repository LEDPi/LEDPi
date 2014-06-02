#ifndef _MAIN_H
#define _MAIN_H

////////////////////////////////////////////////////////////////////////////
// FILE: main
// DESC: Initializes the communications modules
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "send.h"
#include "recieve.h"

void * sendThreadFnc(void * argument);
void * recvThreadFnc(void *argument);

struct SendThreadFuncArgument{
    struct socketHandle SendHandle;
};

struct RecvThreadFuncArgument{
    struct socketHandle RecvHandle;
};

#endif // _MAIN_H

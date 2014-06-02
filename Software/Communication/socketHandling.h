#ifndef SOCKETHANDLING_H
#define SOCKETHANDLING_H

//////////////////////////////////////////////////////////////////
// FILE: socketHandling
// DESC: Holds all important headerfiles for sockets,
//       defines common handling struct
//////////////////////////////////////////////////////////////////


#include <iostream>
#include <sys/ioctl.h>
#include <cstdio>       //Here is Bufsize declared
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEBUG_CONSOLE(X);    std::cout<<X<<std::endl;
#define OK      1
#define ERROR   -1



struct socketHandle
{
    int sock;
    struct sockaddr_in client;
    socklen_t client_len;
};


#endif // SOCKETHANDLING_H

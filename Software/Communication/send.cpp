#include "send.h"

static char bufSend[BUFSIZ];

int initSendSocket(socketHandle* senderHandle)
{
    int sock;
    struct sockaddr_in client, sender;
    struct hostent *host;

    if (!(host=gethostbyname(DESTINATION_IP)))
    {
        DEBUG_CONSOLE("Could not find desired ip");
        return ERROR;
    }

    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    memcpy(&client.sin_addr, host->h_addr, host->h_length);
    client.sin_port   = htons(SEND_PORT);



    if ((sock=socket(PF_INET, SOCK_DGRAM, 0)) < 0 )
    {
        DEBUG_CONSOLE("Send socket creation failed");
        return ERROR;
    }

    memset(&sender, 0, sizeof(sender));
    sender.sin_family      = AF_INET;
    sender.sin_addr.s_addr = htonl(INADDR_ANY);
    sender.sin_port        = htons( 0 );

    if (bind(sock, (struct sockaddr *) &sender, sizeof(sender)) < 0)
    {
        DEBUG_CONSOLE("Binding socket failed");
        return ERROR;
    }

    senderHandle->sock = sock;
    senderHandle->client = client;
    senderHandle->client_len = sizeof(client);
    return OK;
}



int sendMsg(socketHandle* senderHandle)
{
  std::cout << "Please write the message" << std::endl;

  while(read(fileno(stdin), bufSend, BUFSIZ) != 0)
  {
      std::cout << "Input Successfull" << std::endl;
    socklen_t client_len = sizeof(senderHandle->client);
    
    if (sendto(senderHandle->sock, bufSend, strlen(bufSend), 0,(struct sockaddr *) &senderHandle->client, client_len) < 0 )
    {
        DEBUG_CONSOLE("Sending message failed")
        close(senderHandle->sock);
        return ERROR;
    }
    memset(bufSend,0,BUFSIZ);
  }
  return OK;
}


int closeSenderSocket(int sock)
{
    close(sock);
    return OK;
}



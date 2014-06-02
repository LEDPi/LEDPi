#include "recieve.h"

static char bufRecieve[BUFSIZ];               // Buffer for messages

int initRecieveSocket(socketHandle* recieverHandle)
{
  int sock;
  socklen_t reciever_len;
  struct sockaddr_in reciever,client;
  
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
  {
      DEBUG_CONSOLE("Reciever socket creation failed");
      return ERROR;
  }

  memset(&reciever, 0, sizeof(reciever));
  reciever.sin_family      = AF_INET;
  reciever.sin_addr.s_addr = htonl(INADDR_ANY);
  reciever.sin_port        = htons(RECIEVE_PORT);

  if (bind(sock, (struct sockaddr *) &reciever, sizeof(reciever) ) < 0)
  {
    DEBUG_CONSOLE("Binding socket failed");
    return ERROR;
  }
  
  reciever_len = sizeof(reciever);
  if (getsockname(sock, (struct sockaddr *) &reciever,&reciever_len) < 0)
  {
    DEBUG_CONSOLE("Get socketname failed");
    return ERROR;
  }

  recieverHandle->sock = sock;
  recieverHandle->client = client;
  recieverHandle->client_len = sizeof(client);

  return OK;
}

int recieve(socketHandle* recieverHandle)
{
   int size;
   memset(bufRecieve, 0, BUFSIZ);

   if ((size=recvfrom(recieverHandle->sock, bufRecieve, BUFSIZ, 0, (struct sockaddr *) &recieverHandle->client, &recieverHandle->client_len)) < 0)
   {
        DEBUG_CONSOLE("Recieving message failed")
        return ERROR;
   }

   // Displays recieved message
   write(fileno(stdout), bufRecieve, size);

   printf("Source Port: %d \n", recieverHandle->client.sin_port);
   char *client_adress;
   client_adress = inet_ntoa(recieverHandle->client.sin_addr);
   std::cout<<"Source IP Adress: " << client_adress << std::endl;

   memset(bufRecieve, 0, BUFSIZ);

   return OK;

}

int closeRecieverSocket(int sock)
{
    close(sock);
    return OK;
}




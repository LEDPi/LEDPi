#include "main.h"

int main()
{
    std::cout << "Communication Porgram is running" << std::endl;

    SendThreadFuncArgument sendThrArgu;
    RecvThreadFuncArgument recvThrArgu;
    void *ptrSend,*ptrReceive;
    ptrSend = &sendThrArgu;
    ptrReceive = &recvThrArgu;
    pthread_t sendThread,recvThread;
    pthread_create(&sendThread,NULL,sendThreadFnc,ptrSend);
    pthread_create(&recvThread,NULL,recvThreadFnc,ptrReceive);
    printf("Threads were created !!!!\n");
    pthread_exit(NULL);

    /*
     *
     socketHandle senderHandle,recieveHandle;
    initRecieveSocket(&recieveHandle);

    while(1)
    {
        recieve(&recieveHandle);
        std::cout<<"Another messages was recieved"<<std::endl;

    }

    initSendSocket(&senderHandle);

    while(1)
    {
    sendMsg(&senderHandle);
    }
    */



    return 0;
}

void* sendThreadFnc(void * arg)
{
    SendThreadFuncArgument* argument =(SendThreadFuncArgument*) arg;
    initSendSocket(&argument->SendHandle);

    while(1)
    {
        sendMsg(&argument->SendHandle);
        printf("******************************\n");
    }
    return 0;
}

void* recvThreadFnc(void * arg)
{
    RecvThreadFuncArgument* argument = (RecvThreadFuncArgument*) arg;


    while(1)
    {
        initRecieveSocket(&argument->RecvHandle);
        recieve(&argument->RecvHandle);
        closeRecieverSocket(argument->RecvHandle.sock);
        printf("*******************************\n");
    }
    return 0;
}


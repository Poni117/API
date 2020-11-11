#include "AntiSound_API.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

int main()
{

    antiSound_api_testInitializeServer();

    server_t* server = antiSound_api_initializeServer();

    antiSound_api_testNewServer(server);

    system("../AntiSound_API/Compile_AntiSound_API_TestConnect.sh");

    while(true)
    {
        antiSound_api_testReceive(server);
    }
}

void antiSound_api_testInitializeServer()
{
    bool isInitializeSuccess = false;

    bool isServerSocketInitialized = false;

    server_t* server = antiSound_api_initializeServer();

    if(server->serverSocket == -1)
    {
        isServerSocketInitialized = true;
    }

    if(isServerSocketInitialized == true)
    {
        isInitializeSuccess = true;
    }

    if(isInitializeSuccess == false)
    {
        printf("----------------------------------\n");
        printf("antiSound_api_testInitializeServer\n");
        printf("isInitializeSuccess[%d]\n", isInitializeSuccess);
    }
    
    free(server);
}

void antiSound_api_testNewServer(server_t* server)
{
    bool isServerCreated = false;

    isServerCreated = antiSound_api_newServer(server);

    if(isServerCreated == false)
    {
        printf("----------------------------------\n");
        printf("antiSound_api_testNewServer\n");
        printf("isServerCreated[%d]\n", isServerCreated);
    }
}

void antiSound_api_testReceive(server_t* server)
{
    bool isReceiveSuccess = false;

    isReceiveSuccess = antiSound_api_receive(server);

    if(isReceiveSuccess == false)
    {
        printf("----------------------------------\n");
        printf("antiSound_api_testReceive\n");
        printf("isReceiveSuccess[%d]\n", isReceiveSuccess);
    }
}


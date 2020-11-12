#include "AntiSound_API.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

server_t* antiSound_api_initializeServer()
{
    server_t* server = malloc(sizeof(server_t));
    server->serverSocket = -1;

    return server;
}

bool antiSound_api_newServer(server_t* server)
{
    bool isServerSuccess = false;

    bool isBindExist = false;
    bool isListenExist = false;

    server->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server->setConnect.sin_family = AF_INET;
    server->setConnect.sin_port = ntohs(8090);
    server->setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindStatus = bind(server->serverSocket, (struct sockaddr *) &server->setConnect, sizeof(server->setConnect));

    if(bindStatus != -1)
    {
        isBindExist = true;
    }

    int listenStatus = listen(server->serverSocket, 1);

    if(listenStatus != -1)
    {
        isListenExist = true;
    }

    if(isBindExist == true && isListenExist == true)
    {
        isServerSuccess = true;
    }

    return isServerSuccess;
}

bool antiSound_api_receive(server_t* server)
{
    static int i = 0;

    bool isRecieveSucsess = false;

    bool isClientSocketExist = false;

    int clientSocket = accept(server->serverSocket, NULL, NULL);

    char buffer[256] = "\0";

    recv(clientSocket, &buffer, strlen(buffer), 0);
    printf("%s\n", buffer);

    if(clientSocket != -1)
    {
        isClientSocketExist = true;
    }

    if(isClientSocketExist == true )
    {
        isRecieveSucsess = true;
    }

    i++;
    return isRecieveSucsess;
}
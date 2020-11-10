#include "AntiSound_API.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void antiSound_api_start()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;
    setConnect.sin_family = AF_INET;
    setConnect.sin_port = ntohl("8090");
    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (const struct sockaddr*) &setConnect, sizeof(setConnect);

    listen(serverSocket, 1);

    while (true)
    {
        int clientSocket = accept(serverSocket, NULL, NULL);
    }
}

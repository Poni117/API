#include "AntiSound_API.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>


int main()
{
    antiSound_api_testTestConnect();
}

bool antiSound_api_testConnect()
{
    bool isServerExist = false;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;
    setConnect.sin_family = AF_INET;
    setConnect.sin_port = ntohs(8090);
    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connectStatus = connect(clientSocket, (struct sockaddr*) &setConnect, sizeof(setConnect));
 
    if(connectStatus != -1)
    {
        isServerExist = true;
    }

    char buffer[256] = "\0";

    printf("%s\n", buffer);

    return isServerExist;
}

void antiSound_api_testTestConnect()
{
    bool isConnectSuccess = false;

    isConnectSuccess = antiSound_api_testConnect();

    if(isConnectSuccess == false)
    {
        printf("----------------------------------\n");
        printf("antiSound_api_testTestConnect\n");
        printf("isConnectSuccess[%d]\n", isConnectSuccess);
    }
}
#include "AntiSound_API.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Handler/AntiSound_Handler.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool antiSound_api_newServer()
{
    printf("%s\n",antiSound_constructor_generateKey());

    int serverSocket = antiSound_api_copySocket();

    binaryTree_t* root = antiSound_binaryTree_initializeNode();

    while (true)
    {
        int clientSocket = accept(serverSocket, NULL, NULL);

        char buffer[1000] = "\0";
        recv(clientSocket, buffer, sizeof(buffer), 0);
        size_t sizeOfBuffer = strlen(buffer);

        char* requestData = calloc(sizeOfBuffer + 1, sizeof(char));
        strncpy(requestData, buffer, sizeOfBuffer);

        request_t* request = antiSound_http_parseRuqest(antiSound_api_removeCorrector(requestData));

        if(strcmp(request->path, "tasks") == 0)
        {
            response_t* response = antiSound_handler_handler(request, root);
            
            char* message = antiSound_handler_collectResponse(response);

            send(clientSocket, message, strlen(message), 0);

            if(antiSound_binaryTree_isBalanced(root) == false)
            {
                antiSound_binaryTree_balancingSubNodes(root);
                root = balancingNode(root);
            }

            free(request);
            free(response);
            free(requestData);
        }

        close(clientSocket);
    }

    return true;
}

char* antiSound_api_removeCorrector(char* requestData)
{
    int i = 0;
    int j = 0;
    
    char buffer[1000] = "\0";

    while (i < strlen(requestData))
    {
        if (requestData[i] != '\r')
        {
            buffer[j] = requestData[i];
            j++;
        }
        i++;
    }
    
    char* alteratedRequest = calloc(strlen(buffer) + 1, sizeof(char));
    strncpy(alteratedRequest, buffer, strlen(buffer));

    return alteratedRequest;
}

int antiSound_api_copySocket()
{
    bool isServerExist = false;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;
    setConnect.sin_family = AF_INET;
    setConnect.sin_port = ntohs(8090);
    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindStatus = bind(serverSocket, (const struct sockaddr *) &setConnect, sizeof(setConnect));

    if(bindStatus != -1)
    {
        isServerExist = true;
    }
    
    printf("isServerExist[%d]\n", isServerExist);

    listen(serverSocket, 1);

    return serverSocket;
}
#include "AntiSound_API.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Handler/AntiSound_Handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

bool antiSound_api_newServer()
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

    list_t* taskList = antiSound_list_new();

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

            response_t* response = antiSound_handler_handler(request, taskList);
          
            send(clientSocket, response->response, strlen(response->response), 0);
        }
    }

    return true;
}

char* antiSound_api_removeCorrector(char* requestData)
{
    int i = 0;
    int j = 0;
    char* alterateRequestData = calloc(j, sizeof(char));

    while (i < strlen(requestData))
    {
        if (requestData[i] != '\r')
        {
            alterateRequestData = realloc(alterateRequestData, j + 1);
            alterateRequestData[j] = requestData[i];
            j++;
        }
        i++;
    }

    return alterateRequestData;
}


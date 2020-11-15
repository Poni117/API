
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>

bool antiSound_api_newServer()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;
    setConnect.sin_family = AF_INET;
    setConnect.sin_port = ntohs(8090);
    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (const struct sockaddr *) &setConnect, sizeof(setConnect));

    listen(serverSocket, 1);

    while (true)
    {
        int clientSocket = accept(serverSocket, NULL, NULL);

        char buffer[1000] = "\0";
        recv(clientSocket, buffer, sizeof(buffer), 0);
        size_t sizeOfBuffer = strlen(buffer);

        char* requestData = calloc(sizeOfBuffer + 1, sizeof(char));
        strncpy(requestData, buffer, sizeOfBuffer);


        request_t* request = antiSound_http_parseRuqest(requestData);


        printf("%s\n", request->method);
        
    }

    return true;
}

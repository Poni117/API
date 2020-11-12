#include "AntiSound_API.h"

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

        char buffer[256] = "\0";
        recv(clientSocket, buffer, strlen(buffer), 0);
        
        char response[] = 
        "HTTP/1.1 200 OK\n"
        "Content-Length: 0\n"
        "\n";

        send(clientSocket, &response, strlen(response), 0);

        printf("%s\n", buffer);

    }

    return true;
}

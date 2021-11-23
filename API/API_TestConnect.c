
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>


int main()
{
    api_testConnect();
}

bool api_testConnect()
{
    bool isServerExist = false;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;

    setConnect.sin_family = AF_INET;

    setConnect.sin_port = ntohs(8090);

    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (const struct sockaddr*) &setConnect, sizeof(setConnect));

    char buffer[256] = "\0";

    recv(clientSocket, buffer, sizeof(buffer), 0);

    char request[256] =
    "GET / HTTP/1.1\n"
    "Content-Length: 0\n"
    "Content-Type: application/json\n"
    "\n";
    
    send(clientSocket, request, strlen(request), 0);

    printf("%s\n", buffer);

    return isServerExist;
}

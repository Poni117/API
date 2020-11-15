#ifndef ANTISOUND_API_H
#define ANTISOUND_API_H

#include <stdbool.h>
#include <arpa/inet.h>

typedef struct Server
{
    int serverSocket;
    struct sockaddr_in setConnect;
}server_t;


/*
 * initialize struct server_t and returns pointer to server_t
 */
server_t* antiSound_api_initializeServer();

/*
 * create new server and returns true if successful, otherwise returns false
 */
bool antiSound_api_newServer();

/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
bool antiSound_api_receive(server_t* server);

/*
 * creates test client socket and checks connect with server, returns true if successful, otherwise returns false
 */
bool antiSound_api_testConnect();

/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
void antiSound_api_response(int serverSocket);


//=============================================================================================================================

/*
 * test antiSound_api_initializeServer
 */
void antiSound_api_testInitializeServer();

/*
 * test antiSound_api_createNewServer
 */
void antiSound_api_testNewServer();

/*
 * test antiSound_api_receieve
 */
void antiSound_api_testReceive(server_t* server);

/*
 * test antiSound_api_createTestClientSocket
 */
void antiSound_api_testTestConnect();


#endif // ANTISOUND_API_H
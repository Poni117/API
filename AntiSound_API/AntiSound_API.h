#ifndef ANTISOUND_API_H
#define ANTISOUND_API_H

#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include <stdbool.h>
#include <arpa/inet.h>

/*
 * create new server and returns true if successful, otherwise returns false
 */
bool antiSound_api_newServer();

/*
 * removes correctors from requestData(for Linux)
 */
char* antiSound_api_removeCorrector(char* requestdata);
/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
bool antiSound_api_receive();

/*
 * creates test client socket and checks connect with server, returns true if successful, otherwise returns false
 */
bool antiSound_api_testConnect();

/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
void antiSound_api_response(int serverSocket);

void antiSound_api_freeDatas(request_t* request, response_t* response);

void* antiSound_api_processRequest(void* data);

int antiSound_api_copySocket();

bool antiSound_api_sendKey(int clientSocket, char* key);

void antiSound_api_addtask(binaryTree_t* responses, char* messege, char* key);

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
void antiSound_api_testReceive();

/*
 * test antiSound_api_createTestClientSocket
 */
void antiSound_api_testTestConnect();


#endif // ANTISOUND_API_H
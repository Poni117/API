#ifndef ANTISOUND_API_H
#define ANTISOUND_API_H

#include "../HTTP/HTTP.h"
#include <stdbool.h>
#include <arpa/inet.h>

/*
 * create new server and returns true if successful, otherwise returns false
 */
bool api_newServer();

/*
 * removes correctors from requestData(for Linux)
 */
char* api_removeCorrector(char* requestdata);
/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
bool api_receive();

/*
 * creates test client socket and checks connect with server, returns true if successful, otherwise returns false
 */
bool api_testConnect();

/*
 * receives a request from the client Socket and returns true if successful, otherwise returns false
 */
void api_response(int serverSocket);


void* api_processRequest(request_t* request, response_t* response, binaryTree_t* root);

int api_copySocket();

bool api_sendKey(int clientSocket, char* key);

void api_addtask(binaryTree_t* responses, char* messege, char* key);

//=============================================================================================================================

/*
 * test antiSound_api_initializeServer
 */
void api_testInitializeServer();

/*
 * test antiSound_api_createNewServer
 */
void api_testNewServer();

/*
 * test antiSound_api_receieve
 */
void api_testReceive();

/*
 * test antiSound_api_createTestClientSocket
 */
void api_testTestConnect();


#endif // ANTISOUND_API_H
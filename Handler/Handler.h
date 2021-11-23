#include <stdio.h>
#include <stdlib.h>

#include "../BinaryTree/BinaryTree.h"
#include "../HTTP/HTTP.h"

response_t* handler_initializeResponse();

void handler_tasksHandler(request_t* request, response_t* response, binaryTree_t* root);

char* handler_collectResponse(response_t* response);

void* handler_messageHandler(int clientSocket, request_t* request, binaryTree_t* messages);
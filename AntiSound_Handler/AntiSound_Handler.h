#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>

response_t* antiSound_handler_initializeResponse();

void antiSound_handler_tasksHandler(request_t* request, response_t* response, binaryTree_t* root);

char* antiSound_handler_collectResponse(response_t* response);

void* antiSound_handler_messageHandler(int clientSocket, request_t* request, binaryTree_t* messages);
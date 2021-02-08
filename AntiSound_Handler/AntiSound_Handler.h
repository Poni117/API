#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>

response_t* antiSound_handler_initializeResponse();

response_t* antiSound_handler_tasksHandler(request_t* request, binaryTree_t* root);

char* antiSound_handler_collectResponse(response_t* response);

void* antiSound_handler_messageHandler(void* data);
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"

#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>

response_t* antiSound_handler_initializeResponse();

response_t* antiSound_handler_handler(request_t* request, list_t* list, binaryTree_t* root);

char* antiSound_handler_collectResponse(response_t* response);

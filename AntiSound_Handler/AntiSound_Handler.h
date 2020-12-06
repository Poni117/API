#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>

response_t* antiSound_handler_initializeResponse();

response_t* antiSound_handler_handler(request_t* request, list_t* list);

char* antiSound_handler_collectResponse(response_t* response);

void antiSound_handler_defineStatus(response_t* response, bool isMethodSuccess);

char* antiSound_handler_decodeToJson(request_t* request, list_t* taskList);

bool antiSound_handler_updateTask(request_t* request, list_t* taskList);

bool antiSound_handler_readTask(request_t* request, list_t* taskList, response_t* response);

bool antiSound_handler_createTask(request_t* request, list_t* taskList);

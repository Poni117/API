#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>

response_t* antiSound_handler_initializeResponse();

response_t* antiSound_handler_handler(request_t* request, list_t* list);

char* antiSound_handler_collectResponse(response_t* response);

queryParameter_t* antiSound_handler_getQueryParamter(request_t* request, char* id);

bool antiSound_handler_getTask(request_t* request, list_t* taskList, response_t* response);

void antiSound_handler_defineStatus(response_t* response, bool isMethodSuccess);

char* antiSound_handler_json(request_t* request, list_t* taskList);

headerParameter_t* antiSound_handler_getHeaderParamter(request_t* request, char* id);

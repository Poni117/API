#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>


response_t* antiSound_handler_handler(request_t* request, list_t* list);

char* antiSound_handler_collectResponse(char* body);

queryParameter_t* antiSound_handler_getQueryParamter(request_t* request);

char* antiSound_handler_getTask(request_t* request, list_t* taskList);
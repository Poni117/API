#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>



task_t* antiSound_handler_initializeTask();

response_t* antiSound_handler_handler(request_t* request, list_t* list);

char* antiSound_handler_responseBody(list_t* taskList);

char* antiSound_handler_buildTasks(list_t* taskList);

char* antiSound_handler_collectResponse(list_t* taskList);

int antiSound_handler_findRequestData(request_t* request);
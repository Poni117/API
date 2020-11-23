#include "../AntiSound_HTTP/AntiSound_HTTP.h"

#include <stdio.h>
#include <stdlib.h>



task_t* antiSound_handler_initializeTask();

bool antiSound_handler_taskManagement(request_t* request, list_t* list);

response_t* antiSound_handler_handler(request_t* request, list_t* list);

char* antiSound_handler_convertToJson(char* id, char* name);

char* antiSound_handler_collector(char* dataA, char* dataB);

char* antiSound_handler_collectResponse(list_t* taskList);
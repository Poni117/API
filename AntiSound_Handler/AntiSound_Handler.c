#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

task_t* antiSound_handler_initializeTask()
{
    task_t* task = malloc(sizeof(task_t));
    
    task->id = NULL;
    task->name = NULL;

    return task;
}

response_t* antiSound_handler_handler(request_t* request, list_t* taskList)
{
    response_t* response = malloc(sizeof(response_t));

    if(strcmp(request->method, "GET") == 0)
    {   
        response->response = antiSound_handler_collectResponse(taskList);
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        antiSound_list_add(taskList, request->body);
        response->response = "HTTP/1.1 200 OK\n";
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        antiSound_list_update(taskList, antiSound_handler_findRequestData(request), request->body);
        response->response = "HTTP/1.1 200 OK\n";
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        antiSound_list_remove(taskList, antiSound_handler_findRequestData(request));
        response->response = "HTTP/1.1 200 OK\n";
    }

    return response;
}

char* antiSound_handler_responseBody(list_t* taskList)
{
    char* macketOfResponse = "{\"tasks\":[%s]}";

    return antiSound_constructor_addLayout(antiSound_constructor_decodeTasksToJson(taskList), macketOfResponse);
}

char* antiSound_handler_collectResponse(list_t* taskList)
{
    char* status = "HTTP/1.1 200 OK\n";
    char* contentType = "Content-Type: application/json\n";
    char* contentLength = "Content-Length: ";
    char* lineBreak = "\n";

    char* collectedResponse = "\0";

    char* fullCollectedTasks = antiSound_handler_responseBody(taskList);

    char* charLength = calloc(strlen(fullCollectedTasks) + 1, sizeof(char));
    sprintf(charLength, "%ld", strlen(fullCollectedTasks));

    char* fullContentLength = antiSound_constructor_collector(contentLength, charLength);

    collectedResponse = antiSound_constructor_collector(collectedResponse, status);
    collectedResponse = antiSound_constructor_collector(collectedResponse, contentType);
    collectedResponse = antiSound_constructor_collector(collectedResponse, fullContentLength);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_constructor_collector(collectedResponse, fullCollectedTasks);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);

    printf("%s\n", collectedResponse);
    return collectedResponse;
}

int antiSound_handler_findRequestData(request_t* request)
{
    int id;

    list_t* pointerByQueryParameter = request->url->queryParameters;

    if(pointerByQueryParameter->id == -1)
    {
        pointerByQueryParameter = pointerByQueryParameter->next;
    }

    while (pointerByQueryParameter != NULL)
    {
        queryParameter_t* queryParameter = pointerByQueryParameter->data;

        if(strcmp(queryParameter->id, "id") == 0)
        {
            id = atoi(queryParameter->name);
            break;
        }
        pointerByQueryParameter = pointerByQueryParameter->next;
    }
    
    return id;
}

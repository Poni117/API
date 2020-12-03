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
        response->response = antiSound_handler_collectResponse(antiSound_handler_getTask(request, taskList));
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        antiSound_list_add(taskList, request->body);
        response->response = "HTTP/1.1 200 OK\n";
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        antiSound_list_update(taskList, atoi(antiSound_handler_getQueryParamter(request)->name), request->body);
        response->response = "HTTP/1.1 200 OK\n";
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        antiSound_list_remove(taskList, atoi(antiSound_handler_getQueryParamter(request)->name));
        response->response = "HTTP/1.1 200 OK\n";
    }

    return response;
}

char* antiSound_handler_responseBody(list_t* taskList)
{
    char* layoutOfResponse = "{\"tasks\":[%s]}";

    return antiSound_constructor_addLayout(antiSound_constructor_decodeListToJson(taskList), layoutOfResponse);
}

char* antiSound_handler_collectResponse(char* body)
{
    char* status = "HTTP/1.1 200 OK\n";
    char* contentType = "Content-Type: application/json\n";
    char* contentLength = "Content-Length: ";
    char* lineBreak = "\n";

    char* collectedResponse = "\0";


    char* charLength = calloc(strlen(body) + 1, sizeof(char));
    sprintf(charLength, "%ld", strlen(body));

    char* fullContentLength = antiSound_constructor_collector(contentLength, charLength);

    collectedResponse = antiSound_constructor_collector(collectedResponse, status);
    collectedResponse = antiSound_constructor_collector(collectedResponse, contentType);
    collectedResponse = antiSound_constructor_collector(collectedResponse, fullContentLength);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_constructor_collector(collectedResponse, body);
    collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);

    printf("%s\n", collectedResponse);
    return collectedResponse;
}

queryParameter_t* antiSound_handler_getQueryParamter(request_t* request)
{
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
            return queryParameter;
        }

        pointerByQueryParameter = pointerByQueryParameter->next;
    }
    
    return NULL;
}

char* antiSound_handler_getTask(request_t* request, list_t* taskList)
{
    queryParameter_t* queryParameter = antiSound_handler_getQueryParamter(request);

    char* body = NULL;

    if(queryParameter == NULL)
    {
        char* layoutOfResponse = "{\"tasks\":[%s]}";

        body = antiSound_constructor_addLayout(antiSound_constructor_decodeListToJson(taskList), layoutOfResponse);
    }
    if(queryParameter != NULL)
    {
        char* layoutOfResponse = "{\"task\":%s}";
        
        body = antiSound_constructor_addLayout(antiSound_constructor_decodeTaskToJson(antiSound_list_getData(taskList, atoi(queryParameter->name))), layoutOfResponse);   
    }

    return body;
}
#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

response_t* antiSound_handler_initializeResponse()
{
    response_t* response = malloc(sizeof(response_t));

    response->status = NULL;
    response->httpVersion = NULL;
    response->contentType = NULL;
    response->contentLength = NULL;
    response->body = NULL;

    return response;
}

response_t* antiSound_handler_handler(request_t* request, list_t* taskList)
{
    response_t* response = antiSound_handler_initializeResponse();
    
    if(strcmp(request->method, "GET") == 0)
    {   
        bool isGetSuccess = false;

        isGetSuccess = antiSound_handler_getTask(request, taskList, response);

        antiSound_handler_defineStatus(response, isGetSuccess);
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        bool isAddSuccess = false;

        int id = antiSound_list_add(taskList, request->body);

        if(id != -1)
        {
            isAddSuccess = true;
        }

        antiSound_handler_defineStatus(response, isAddSuccess);
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        bool isUpdateSuccess = false;

        isUpdateSuccess = antiSound_list_update(taskList, atoi(antiSound_handler_getQueryParamter(request, "id")->name), request->body);

        antiSound_handler_defineStatus(response, isUpdateSuccess);
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        bool isDeleteSuccess = false;

        antiSound_list_remove(taskList, atoi(antiSound_handler_getQueryParamter(request, "id")->name));

        antiSound_handler_defineStatus(response, isDeleteSuccess);
    }

    return response;
}

char* antiSound_handler_collectResponse(response_t* response)
{
    char* contentLength = "Content-Length: ";

    char* lineBreak = "\n";

    char* collectedResponse = "\0";
    collectedResponse = antiSound_constructor_collector(collectedResponse, response->status);

    if(response->contentType != NULL)
    {
        collectedResponse = antiSound_constructor_collector(collectedResponse, response->contentType);
    }

    if(response->body != NULL)
    {
        char* charLength = calloc(strlen(response->body), sizeof(char));
        sprintf(charLength, "%ld", strlen(response->body));

        char* fullContentLength = antiSound_constructor_collector(contentLength, charLength);
        
        collectedResponse = antiSound_constructor_collector(collectedResponse, fullContentLength);
        collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
        collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
        collectedResponse = antiSound_constructor_collector(collectedResponse, response->body);
    }

    printf("%s\n", collectedResponse);
    return collectedResponse;
}

queryParameter_t* antiSound_handler_getQueryParamter(request_t* request, char* id)
{
    list_t* pointerByQueryParameter = request->url->queryParameters;

    if(pointerByQueryParameter->id == -1)
    {
        pointerByQueryParameter = pointerByQueryParameter->next;
    }

    while (pointerByQueryParameter != NULL)
    {
        queryParameter_t* queryParameter = pointerByQueryParameter->data;

        if(strcmp(queryParameter->id, id) == 0)
        {
            return queryParameter;
        }

        pointerByQueryParameter = pointerByQueryParameter->next;
    }
    
    return NULL;
}

bool antiSound_handler_getTask(request_t* request, list_t* taskList, response_t* response)
{
    bool isGetSuccess = false;
    
    response->contentType = "Content-Type: application/json\n";

    char* tasks = antiSound_handler_json(request, taskList);

    if(tasks != NULL)
    {
        isGetSuccess = true;
        response->body = tasks;
    }

    return isGetSuccess;
}

void antiSound_handler_defineStatus(response_t* response, bool isMethodSuccess)
{
    if(isMethodSuccess == true)
    {
        response->status = "HTTP/1.1 200 OK\n";
    }
    else
    {
        response->status = "HTTP/1.1 404\n";
    }
}

headerParameter_t* antiSound_handler_getHeaderParamter(request_t* request, char* id)
{
    list_t* pointer = request->headers;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while (pointer != NULL)
    {
        headerParameter_t* headerParameter = pointer->data;

        if(strcmp(headerParameter->id, id) == 0)
        {
            return headerParameter;
        }

        pointer = pointer->next;
    }
    
    return NULL;
}

char* antiSound_handler_json(request_t* request, list_t* taskList)
{
    queryParameter_t* queryParameter = antiSound_handler_getQueryParamter(request, "id");

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
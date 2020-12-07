#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"
#include "../AntiSound_Item/AntiSound_Item.h"

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
    
    if(antiSound_http_checkParameters(request, taskList, response) == false)
    {
        return response;
    }

    if(strcmp(request->method, "GET") == 0)
    {   
        antiSound_item_read(request, taskList, response);
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        antiSound_item_create(request, taskList);
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        antiSound_item_update(request, taskList);
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        antiSound_item_remove(request, taskList);
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

void antiSound_handler_defineStatus(response_t* response, char* status)
{
    response->status = status;
}

bool antiSound_http_checkExistingId(request_t* request, list_t* taskList)
{
    bool isTaskExist = false;

    body_t* body = antiSound_http_getBodyParamter(request, "id");

    item_t* item = antiSound_item_getItem(taskList, atoi(body->name));

    if(item != NULL)
    {
        isTaskExist = true;
    }

    return isTaskExist;
}


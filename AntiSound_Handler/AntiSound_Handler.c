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

        isGetSuccess = antiSound_handler_readTask(request, taskList, response);

        antiSound_handler_defineStatus(response, isGetSuccess);
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        bool isAddSuccess = antiSound_handler_createTask(request, taskList);

        antiSound_handler_defineStatus(response, isAddSuccess);
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        bool isUpdateSuccess = false;

        isUpdateSuccess = antiSound_handler_updateTask(request, taskList );

        antiSound_handler_defineStatus(response, isUpdateSuccess);
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        bool isDeleteSuccess = false;

        isDeleteSuccess = antiSound_list_remove(taskList, atoi(antiSound_http_getQueryParamter(request, "id")->name));

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


bool antiSound_handler_readTask(request_t* request, list_t* taskList, response_t* response)
{
    bool isGetSuccess = false;
    
    response->contentType = "Content-Type: application/json\n";

    char* tasks = antiSound_handler_decodeToJson(request, taskList);

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
        response->status = "HTTP/1.1 404 - Not Found\n";
    }
}

char* antiSound_handler_decodeToJson(request_t* request, list_t* taskList)
{
    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    char* body = NULL;

    if(queryParameter == NULL)
    {
        body = antiSound_constructor_decodeListToJson(taskList);
    }

    if(queryParameter != NULL)
    {
        item_t* item = antiSound_http_getItem(taskList, atoi(queryParameter->name));
        body = antiSound_constructor_decodeTaskToJson(item->data);   
    }

    return body;
}

bool antiSound_handler_createTask(request_t* request, list_t* taskList)
{
    bool isPostTaskSuccess = false;

    if(antiSound_http_testInitializeItem() == false)
    {
        return isPostTaskSuccess;
    }

    item_t* item = antiSound_http_initializeItem();

    item->data = request->body;

    bool isDefineTaskSuccess = antiSound_http_setItemId(item);

    list_t* pointer = item->data;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while (pointer != NULL)
    {
        body_t* body = pointer->data;
        
        printf("%s\n", body->id);
        printf("%s\n", body->name);

        pointer = pointer->next;
    }

    int id = antiSound_list_add(taskList, item);
    
    if(id != -1 && isDefineTaskSuccess == true)
    {
        isPostTaskSuccess = true;
    }

    return isPostTaskSuccess;
}

bool antiSound_http_setItemId(item_t* item)
{
    bool isDefineIdSuccess = false;

    list_t* pointer = item->data;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while(pointer != NULL)
    {
        body_t* body = pointer->data;

        if(strcmp(body->id, "id") == 0)
        {
            item->id = atoi(body->name);
            isDefineIdSuccess = true;
            break;
        }
        
        pointer = pointer->next;
    }

    return isDefineIdSuccess;
}

bool antiSound_handler_updateTask(request_t* request, list_t* taskList)
{
    bool isUpdateItemSuccess = false;
    
    if(antiSound_http_testGetQueryParamter(request, "id") == false)
    {
        return isUpdateItemSuccess;
    }

    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    if(antiSound_http_testGetItem(taskList, atoi(queryParameter->name)) == false)
    {
        return isUpdateItemSuccess;
    }

    item_t* item = antiSound_http_getItem(taskList, atoi(queryParameter->name));

    if (item != NULL)
    {
        isUpdateItemSuccess = true;
    }

    free(item->data);

    item->data = request->body;
    
    if(antiSound_http_testGetBodyParamter(request, "id") == false)
    {
        return isUpdateItemSuccess;
    }
    body_t* body = antiSound_http_getBodyParamter(request, "id");

    free(body->name);
    body->name = calloc(sizeof(char), item->id);
    sprintf(body->name, "%d", item->id);

    return isUpdateItemSuccess;
}
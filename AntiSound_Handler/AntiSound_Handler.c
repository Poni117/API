#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"

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
    
    if(strcmp(request->method, "POST") == 0 || strcmp(request->method, "PUT") == 0)
    {
        antiSound_handler_addObjectToList(request->body, taskList);
        response->response = "HTTP/1.1 200 OK\n";
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        antiSound_handler_addObjectToList(request->url->queryParameters, taskList);
        response->response = "HTTP/1.1 200 OK\n";

    }

    return response;
}

char* antiSound_handler_response(list_t* taskList)
{
    char* macketOfResponse = "{\"tasks\":[%s]}";
    char* body = calloc(0, sizeof(char));

    char* arrayJsonTasks = antiSound_handler_getTasks(taskList);

    body = realloc(body, strlen(macketOfResponse) + strlen(arrayJsonTasks));
    sprintf(body, macketOfResponse, arrayJsonTasks);

    return body;
}


bool antiSound_handler_addObjectToList(list_t* parameters, list_t* taskList)
{
    bool isAddObjectExist = false;

    antiSound_list_add(taskList, parameters);

    return isAddObjectExist = true;
}

char* antiSound_handler_getTasks(list_t* taskList)
{
    char* delimiter = ", ";
    char* brackets = "{%s}";

    char* arrayJsonTask = calloc(0, sizeof(char));

    list_t* pointer = taskList;

    if (pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while (pointer != NULL)
    {
        list_t* pointerToTask = pointer->data;

        char* jsonTask = calloc(0, sizeof(char));

        char* buffer = calloc(0, sizeof(char));

        while (pointerToTask != NULL)
        {
            if (pointerToTask->id == -1)
            {
                pointerToTask = pointerToTask->next;
            }

            body_t* body = pointerToTask->data;
            
            char* jsonValue = antiSound_handler_json(body->id, body->name);

            buffer = realloc(buffer, strlen(buffer) + strlen(jsonValue) + strlen(delimiter));
            strncat(buffer, jsonValue, strlen(jsonValue));

            if(pointerToTask->next == NULL)
            {
                jsonTask = realloc(jsonTask, strlen(brackets) + strlen(buffer));
                strncat(jsonTask, brackets, strlen(brackets));
                sprintf(jsonTask, brackets, buffer);

                arrayJsonTask = realloc(arrayJsonTask, strlen(jsonTask) + strlen(delimiter));
                strncat(arrayJsonTask, jsonTask, strlen(jsonTask));

                break;
            }

            strncat(buffer, delimiter, strlen(delimiter));

            pointerToTask = pointerToTask->next;
        }

        if(pointer->next != NULL)
        {
            strncat(arrayJsonTask, delimiter, strlen(delimiter));
        }

        pointer = pointer->next;
    }
    
    return arrayJsonTask;
}

char* antiSound_handler_json(char* id, char* name)
{   
    char* formatJson = "\"%s\":\"%s\"";

    char* collectJson = calloc(strlen(formatJson) + strlen(id) + strlen(name), sizeof(char));

    sprintf(collectJson, formatJson, id, name);

    return collectJson;
}

char* antiSound_handler_collectResponse(list_t* taskList)
{
    char* status = "HTTP/1.1 200 OK\n";
    char* contentType = "Content-Type: application/json\n";
    char* contentLength = "Content-Length: ";
    char* lineBreak = "\n";

    char* collectedResponse = "\0";

    char* fullCollectedTasks = antiSound_handler_response(taskList);

    char* charLength = calloc(strlen(fullCollectedTasks) + 1, sizeof(char));
    sprintf(charLength, "%ld", strlen(fullCollectedTasks));

    char* fullContentLength = calloc(strlen(contentLength) + strlen(charLength) + 1, sizeof(char));
    strncat(fullContentLength, contentLength, strlen(contentLength));
    strncat(fullContentLength, charLength, strlen(charLength));

    collectedResponse = antiSound_handler_collector(collectedResponse, status);
    collectedResponse = antiSound_handler_collector(collectedResponse, contentType);
    collectedResponse = antiSound_handler_collector(collectedResponse, fullContentLength);
    collectedResponse = antiSound_handler_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_handler_collector(collectedResponse, lineBreak);
    collectedResponse = antiSound_handler_collector(collectedResponse, fullCollectedTasks);
    collectedResponse = antiSound_handler_collector(collectedResponse, lineBreak);

    printf("%s\n", collectedResponse);
    return collectedResponse;
}

char* antiSound_handler_collector(char* dataA, char* dataB)
{
    char* collectedData = calloc(strlen(dataA) + strlen(dataB) + 1, sizeof(char));
    strncat(collectedData, dataA, strlen(dataA));
    strncat(collectedData, dataB, strlen(dataB));

    return collectedData;
}
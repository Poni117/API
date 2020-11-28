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
        response->status = antiSound_handler_collectResponse(taskList);
    }
    else
    {
        antiSound_handler_taskManagement(request, taskList);
        
        response->status = "HTTP/1.1 200 OK\n";
    }

    return response;
}

bool antiSound_handler_taskManagement(request_t* request, list_t* taskList)
{
    list_t* pointer = NULL;
    
    if(strcmp(request->method, "POST") == 0)
    {
        pointer = request->body;

        if(pointer->id == -1)
        {
            pointer = pointer->next;
        }

        while(pointer != NULL)
        {
            task_t* task = antiSound_handler_initializeTask();

            body_t* body = pointer->data;

            task->id = body->id;
            task->name = body->name;

            antiSound_list_add(taskList, task);

            pointer = pointer->next;
        }
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        pointer = request->body;

        if(pointer->id == -1)
        {
            pointer = pointer->next;
        }

        while(pointer != NULL)
        {
            task_t* task = antiSound_handler_initializeTask();

            body_t* body = pointer->data;

            task->id = body->id;

            task->name = body->name;

            antiSound_list_add(taskList, task);
            
            pointer = pointer->next;
        }
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        pointer = request->url->queryParameters;

        if(pointer->id == -1)
        {
            pointer = pointer->next;
        }

        while(pointer != NULL)
        {
            task_t* task = antiSound_handler_initializeTask();

            queryParameter_t* queryParameter = pointer->data;

            task->id = queryParameter->id;

            task->name = queryParameter->name;


            antiSound_list_add(taskList, task);

            pointer = pointer->next;
        }

    }

    return true;
}

char* antiSound_handler_convertToJson(char* id, char* name)
{
    char* quotes = "\"";
    size_t sizeOfQuots = strlen(quotes);

    char* openBracket = "{";
    size_t sizeOfOpenBraket = strlen(openBracket);

    char* closeBracket = "}";
    size_t sizeOfCloseBraket = strlen(closeBracket);

    char* сolon = ":";
    size_t sizeOfColon = strlen(сolon);

    char* data = calloc(sizeOfOpenBraket + sizeOfQuots + strlen(id)
    + sizeOfQuots + sizeOfColon + sizeOfQuots + strlen(name)
    + sizeOfQuots + sizeOfCloseBraket + 1, sizeof(char));

    strncat(data, quotes, sizeOfQuots);
    strncat(data, id, strlen(id));
    strncat(data, quotes, sizeOfQuots);
    strncat(data, сolon, sizeOfColon);
    strncat(data, quotes, sizeOfQuots);
    strncat(data, name, strlen(name));
    strncat(data, quotes, sizeOfQuots);

    return data;
}

char* antiSound_handler_collector(char* dataA, char* dataB)
{
    char* collectedData = calloc(strlen(dataA) + strlen(dataB) + 1, sizeof(char));
    strncat(collectedData, dataA, strlen(dataA));
    strncat(collectedData, dataB, strlen(dataB));

    return collectedData;
}

char* antiSound_handler_collectResponse(list_t* taskList)
{
    char* tasks = "tasks";
    char* сolon = ":";
    char* openSquarebracket = "[";
    char* closeSquarebracket = "]";
    char* quotes = "\"";
    char* openBracket = "{";
    char* closeBracket = "}";

    char* status = "HTTP/1.1 200 OK\n";
    char* contentType = "Content-Type: application/json\n";
    char* contentLength = "Content-Length: ";
    char* lineBreak = "\n";

    list_t* pointer = taskList;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    char* collectedResponse = "\0";

    char* collectedTask  = "\0";

    while (pointer != NULL)
    {   
        task_t* task = pointer->data;

        char* tasks = antiSound_handler_convertToJson(task->id, task->name);
        collectedTask = antiSound_handler_collector(collectedTask, tasks);
        if(pointer->next != NULL)
        {
            collectedTask = antiSound_handler_collector(collectedTask, ",");
            collectedTask = antiSound_handler_collector(collectedTask, " ");
        }

        pointer = pointer->next;
    }
    
    char* fullCollectedTasks = antiSound_handler_collector(openBracket, quotes);

    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, tasks);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, quotes);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, сolon);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, openSquarebracket);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, collectedTask);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, closeSquarebracket);
    fullCollectedTasks = antiSound_handler_collector(fullCollectedTasks, closeBracket);

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


    return collectedResponse;
}
#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

task_t* antiSound_handler_initializeTask()
{
    task_t* task = malloc(sizeof(task_t));
    
    task->name = NULL;
    task->value = NULL;
    task->next = NULL;

    return task;
}

response_t* antiSound_handler_handler(request_t* request, list_t* list)
{
    antiSound_handler_taskManagement(request, list);
    
    response_t* response = NULL;
    
    return response;
}

bool antiSound_handler_taskManagement(request_t* request, list_t* taskList)
{
    list_t* pointer = NULL;
    task_t* task = antiSound_handler_initializeTask();

    if(strcmp(request->method, "POST") == 0 && strcmp(request->path, "AntiSound_API_Handler") == 0)
    {
        pointer = request->body->next;

        task_t* pointerTask = task;

        while(pointer->next != NULL)
        {
            body_t* body = pointer->data;

            pointerTask->name = body->name;
            pointerTask->value = body->value;

            if(pointer->next != NULL)
            {
                pointerTask->next = antiSound_handler_initializeTask();
                pointerTask = pointerTask->next;
            }

            pointer = pointer->next;
        }
    }

    if(strcmp(request->method, "PUT") == 0 && strcmp(request->path, "AntiSound_API_Handler") == 0)
    {
        pointer = request->url->queryParameters;

        if(pointer->id == -1)
        {
            pointer = pointer->next;
        }

        task_t* pointerTask = task;

        while(pointer != NULL)
        {
            queryParameter_t* queryParameter = pointer->data;

            pointerTask->name = queryParameter->name;
            pointerTask->value = queryParameter->value;

            if(pointer->next != NULL)
            {
                pointerTask->next = antiSound_handler_initializeTask();
                pointerTask = pointerTask->next;
            }
            pointer = pointer->next;
        }
    }

    if(strcmp(request->method, "DELETE") == 0 && strcmp(request->path, "AntiSound_API_Handler") == 0)
    {
        pointer = request->url->queryParameters;

        if(pointer->id == -1)
        {
            pointer = pointer->next;
        }

        task_t* pointerTask = task;

        while(pointer->next != NULL)
        {
            queryParameter_t* queryParameter = pointer->data;

            pointerTask->name = queryParameter->name;
            pointerTask->value = queryParameter->value;

            if(pointer->next != NULL)
            {
                pointerTask->next = antiSound_handler_initializeTask();
                pointerTask = pointerTask->next;
            }
            
            pointer = pointer->next;
        }
    }

    antiSound_list_add(taskList, task);

    return true;
}


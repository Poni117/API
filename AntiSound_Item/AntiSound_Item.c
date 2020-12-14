#include "AntiSound_Item.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

item_t* antiSound_item_initializeItem()
{
   item_t* item = malloc(sizeof(item_t));
   item->id = -1;
   item->data = NULL;

   return item;
}

bool antiSound_item_read(request_t* request, list_t* taskList, response_t* response)
{
    bool isGetSuccess = false;

    response->body = antiSound_constructor_decodeToJson(request, taskList);

    if(response->body != NULL)
    {
        isGetSuccess = true;
    }

    return isGetSuccess;
}

bool antiSound_item_create(request_t* request, list_t* taskList)
{
    bool isPostTaskSuccess = false;

    if(antiSound_item_testInitializeItem() == false)
    {
        return isPostTaskSuccess;
    }

    body_t* id = antiSound_http_getBodyParamter(request, "id");
    body_t* name = antiSound_http_getBodyParamter(request, "name");
    body_t* lastname = antiSound_http_getBodyParamter(request, "lastname");

    task_t* task = antiSound_http_initializeTask();
    task->id = id;
    task->name = name;
    task->lastname = lastname;

    item_t* item = antiSound_item_initializeItem();
    item->id = atoi(id->name);
    item->data = task;

    int addedId = antiSound_list_add(taskList, item);
    
    if(addedId != -1)
    {
        isPostTaskSuccess = true;
    }

    return isPostTaskSuccess;
}

bool antiSound_item_update(request_t* request, list_t* taskList)
{
    bool isUpdateItemSuccess = false;
    
    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    item_t* item = antiSound_item_getItem(taskList, atoi(queryParameter->name));

    task_t* task = item->data;

    task->name = antiSound_http_getBodyParamter(request, "name");
    
    task->lastname =  antiSound_http_getBodyParamter(request, "lastname");

    return isUpdateItemSuccess = true;
}

bool antiSound_item_remove(request_t* request, list_t* taskList)
{
    bool isDeleteSuccess = false;

    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    list_t* pointer = antiSound_item_findItem(taskList, atoi(queryParameter->name));

    isDeleteSuccess = antiSound_list_remove(taskList, pointer->id);

    return isDeleteSuccess;
}

item_t* antiSound_item_getItem(list_t* list, int id)
{
    list_t* pointer = list;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while(pointer != NULL)
    {
        item_t* item = pointer->data;

        if(item->id == id)
        {
            return item;
        }
        pointer = pointer->next;
    }

    return NULL;
}

list_t* antiSound_item_findItem(list_t* list, int id)
{
    list_t* pointer = list;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while(pointer != NULL)
    {
        item_t* item = pointer->data;

        if(item->id == id)
        {
            return pointer;
        }
        pointer = pointer->next;
    }

    return NULL;
}

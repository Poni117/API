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

    item_t* item = antiSound_item_initializeItem();

    item->data = request->body;

    bool isDefineTaskSuccess = antiSound_item_setItemId(item);

    int id = antiSound_list_add(taskList, item);
    
    if(id != -1 && isDefineTaskSuccess == true)
    {
        isPostTaskSuccess = true;
    }

    return isPostTaskSuccess;
}

bool antiSound_item_setItemId(item_t* item)
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

bool antiSound_item_update(request_t* request, list_t* taskList)
{
    bool isUpdateItemSuccess = false;
    
    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    item_t* item = antiSound_item_getItem(taskList, atoi(queryParameter->name));

    free(item->data);

    item->data = request->body;
    
    body_t* body = antiSound_http_getBodyParamter(request, "id");

    free(body->name);
    body->name = calloc(item->id + 1, sizeof(int));
    sprintf(body->name, "%d", item->id);

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

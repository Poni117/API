#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

list_t* list_new()
{
    list_t* list = malloc(sizeof(list_t));
    list->data = NULL;
    list->next = NULL;
    list->id = -1;
    list->lastItem = NULL;

    return list;
}

int list_add(list_t* list, void* data)
{
    list_t* pointer = NULL;

    if(list->lastItem != NULL)
    {
        pointer = list->lastItem;
    }
    else
    {
        pointer = list;
    }
    
    if(data == NULL)
    {
        return -1;
    }
    
    while(pointer->next != NULL)
    {   
        pointer = pointer->next;
    }
    
    pointer->next = list_new();

    pointer->next->id = pointer->id + 1;

    pointer->next->data = data;

    pointer->next->next = NULL;

    list->lastItem = pointer->next;
    
    return pointer->next->id;
}

bool list_update(list_t* list, int id, void* newData)
{
    bool isUpdateSuccess = false;

    bool isItemExist = list_testGetItem(list, id);

    if(isItemExist == false)
    {
        return isItemExist;
    }

    list_t* item = list_getItem(list, id);

    size_t sizeOfNewData = strlen(newData);

    free(item->data);

    item->data = realloc(newData, sizeOfNewData);

    return isUpdateSuccess = true;
}

void* list_getData(list_t* list, int id)
{
    list_t* item = list_getItem(list, id);

    return item->data;
}

list_t* list_getItem(list_t* list, int id)
{
    list_t* pointer = list;

    while (pointer->next != NULL)
    {
        if(pointer->id == id)
        {
            break;
        }
        pointer = pointer->next;
    }
    
    return pointer;
}

bool list_remove(list_t* list, int id)
{
    bool isRemoveSuccess = false;

    bool isItemExist = list_testGetItem(list, id);

    if(isItemExist == false)
    {
        return isItemExist;
    }

    list_t* deleteItem = list_getItem(list, id);

    list_t* pointer = list;

    while (pointer->next != deleteItem)
    {
        pointer = pointer->next;
    }
    
    pointer->next = deleteItem->next;

    free(deleteItem);

    list_redefineId(list);
    
    return isRemoveSuccess = true;
}

int list_length(list_t* list)
{  
    list_t* pointer = list;

    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }

    int lengthOfList = pointer->id + 1;
     
    return lengthOfList;
}

void list_redefineId(list_t* list)
{
    list_t* pointer = list;

    int i = -1;

    while(pointer != NULL)
    {
        pointer->id = i;

        pointer = pointer->next;
        
        i++;
    }
}

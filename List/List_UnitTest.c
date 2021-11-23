#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

void antiSound_list_message(int id);

list_t* antiSound_list_testNew()
{
    bool status = false;

    list_t* list = antiSound_list_new();

    if(list->data == NULL) // check first element
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_list_testNew >\n");
        printf("status[%d]\n", status);
        antiSound_list_message(0);
    }

    return list;
}

void antiSound_list_testAdd(list_t* list)
{
    bool status = false;

    bool isLengthCorrect = false;

    bool isItemDataCorrect = false;

    void* data = "name=Dmitry";

    int id = antiSound_list_add(list, data);

    list_t* item = list_getItem(list, id);
    
    int length = list_length(list);

    if(length == item->id + 1)
    {
        isLengthCorrect = true;
    }
    
    if(strcmp(item->data, data) == 0)
    {
        isItemDataCorrect = true;
    }

    if(isItemDataCorrect == true && isLengthCorrect == true)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_list_testAdd >\n\n");

        printf("status[%d]\n", status);
        
        antiSound_list_message(0);
    }
}

void antiSound_list_testUpdate(list_t* list, int id, void* newData)
{
    bool status = false;

    bool isUpdateSuccess = false;

    bool isItemDataCorrect = false;

    isUpdateSuccess = list_update(list, id, newData);

    list_t* item = list_getItem(list, id);

    if(strcmp(item->data, newData) == 0)
    {
        isItemDataCorrect = true;
    }

    if(isItemDataCorrect == true && isUpdateSuccess == true)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_list_testUpdate >\n\n");

        printf("status[%d]\n", status); 

        antiSound_list_message(0);
    }
}

bool antiSound_list_testGetItem(list_t* list, int id)
{
    bool status = false;

    bool isIdExist = true;

    if(id > list_length(list) || id < 0)
    {
        return isIdExist = false;
    }

    list_t* item = list_getItem(list, id);

    if(item->id == id)
    {
        status = true;
    }
    
    if(status == false)
    {
        printf("< antiSound_list_testGetItem >\n\n");

        printf("status[%d]\n", status);

        antiSound_list_message(0);
    }

    return status;
}

bool antiSound_list_testGetData(list_t* list, int id)
{
    bool status = false;

    bool isItemExist = antiSound_list_testGetItem(list, id);

    if(isItemExist == false)
    {
        return isItemExist;
    }

    list_t* item = list_getItem(list, id);

    void* data = list_getData(list, id);

    if(data != NULL && item->data == data)
    {
        status = true;
    } 
    
    if(status == false)
    {
        printf("< antiSound_list_testGetData >\n\n");

        printf("status[%d]\n", status);

        antiSound_list_message(0);
    }

    return status;

}

void antiSound_list_testRemove(list_t* list)
{
    bool status = false;

    bool isIdOrderCorrect = false;

    bool isLengthCorrect = false;

    bool isRemovableItemExist = false;

    int id = 1;

    int lengthBeforeRemove = list_length(list);
    
    list_t* removableItem = list_getItem(list, id);

    status = list_remove(list, removableItem->id);

    list_t* item = list_getItem(list, removableItem->id);

    list_t* previousItem = list_getItem(list, item->id - 1);

    list_t* nextItem = list_getItem(list, item->id + 1);

    int lengthAfterRemove = list_length(list);

    if(lengthBeforeRemove - 1 == lengthAfterRemove)
    {
        isLengthCorrect = true;
    }

    if(removableItem->data == item->data)
    {
        isRemovableItemExist = true;
    }

    if(item->id - 1 == previousItem->id && item->id + 1 == nextItem->id)
    {
        isIdOrderCorrect = true;
    }

    if(isRemovableItemExist == false && isIdOrderCorrect == true && isLengthCorrect == true)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_list_testRemove >\n\n");

        printf("status[%d]\n", status);

        antiSound_list_message(0);
    }
}

void antiSound_list_testLength(list_t* list)
{
    bool status = false;

    int lengthOfList = list_length(list);

    if(lengthOfList != -1)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_list_testLength >\n\n");

        printf("status[%d]\n", status);

        antiSound_list_message(0);
    }
}

void antiSound_list_message(int id)
{
        switch (id)
        {
        case 0:
            printf("------------------------------\n");
            break;
        }
}

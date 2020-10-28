#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AntiSound_List.h"

void antiSound_list_message(int id);

int main()
{
    antiSound_list_message(0);

    list_t* list = antiSound_list_testNew();

    antiSound_list_message(1);

    antiSound_list_testAdd(list);

    antiSound_list_testUpdate(list); 

    antiSound_list_testGetItem(list);

    antiSound_list_testGetData(list);
    antiSound_list_testRemove(list);

    antiSound_list_testLength(list);

    antiSound_list_testShowList(list);

}

list_t* antiSound_list_testNew()
{
    antiSound_list_message(0);
    printf("< antiSound_list_testNew >\n\n");

    list_t* list = antiSound_list_new();

    antiSound_list_testShowList(list);
    return list;
}

void antiSound_list_testAdd(list_t* list)
{
    printf("< antiSound_list_testAdd >\n\n");

    void* data = "name=Dmitry";
    void* data1 = "name=Petya";
    void* data2 = "name=Katya";
    void* data3 = "name=Nastya";
    void* data4 = "name=Dasha";

    antiSound_list_add(list, data);
    antiSound_list_add(list, data1);
    antiSound_list_add(list, data2);
    antiSound_list_add(list, data3);
    antiSound_list_add(list, data4);

    antiSound_list_testShowList(list);
    antiSound_list_message(0);
}

void antiSound_list_testUpdate(list_t* list)
{
    printf("< antiSound_list_testUpdate >\n\n");

    void* newData = "name=Roma";
    int id = 2;
    list_t* updatedItem = antiSound_list_getItem(list, id);
    
    printf("updateItem:\n[%d] - [%s] to [%s]\n\n", updatedItem->id, (char*)updatedItem->data, (char*)newData);

    bool isUpdateSuccess = antiSound_list_update(list, id, newData);
    printf("isUpdateSuccess[%d]\n\n", isUpdateSuccess); 

    antiSound_list_testShowList(list);

    antiSound_list_message(0);
}

void antiSound_list_testGetItem(list_t* list)
{
    printf("< antiSound_list_testGetItem >\n\n");

    int id = 3;
    list_t* item = antiSound_list_getItem(list, id);
    printf("address - [%p]\n[%d] - [%s]\n", item, item->id, (char*)item->data);
    
    antiSound_list_message(0);
}

void antiSound_list_testGetData(list_t* list)
{
    printf("< antiSound_list_testGetData >\n\n");

    int id = 3;
    void* data = antiSound_list_getData(list, id);
    printf("id - [%d]\ndata - [%s]\n", id, (char*)data);
    
    antiSound_list_message(0);
}

void antiSound_list_testRemove(list_t* list)
{
    printf("< antiSound_list_testRemove >\n\n");

    int id = 1;
    list_t* deletedItem = antiSound_list_getItem(list, id);
    printf("removedItem:\nid[%d] - [%s]\n\n", deletedItem->id, (char*)deletedItem->data);

    bool isRemoveSuccess = antiSound_list_remove(list, id);
    printf("isRemoveSuccess[%d]\n\n", isRemoveSuccess);

    antiSound_list_testShowList(list);

    antiSound_list_message(0);
}

void antiSound_list_testLength(list_t* list)
{
    printf("< antiSound_list_testLength >\n\n");

    if(list == NULL)
    {
        antiSound_list_message(1);
        return;
    }

    int lengthOfList = antiSound_list_length(list);

    printf("lengthOfList[%d]\n", lengthOfList);
    antiSound_list_message(0);

}

void antiSound_list_testShowList(list_t* list)
{
    list_t* pointer = list->next;
    if(list == NULL)
    {
        antiSound_list_message(1);
        return;
    }

    while(pointer != NULL)
    {
        printf("[%d] - ", pointer->id);
        printf("%s\n", (char* )pointer->data);
        pointer = pointer->next;
    }
}

void antiSound_list_message(int id)
{
        switch (id)
        {
        case 0:
            printf("------------------------------\n");
            break;
        case 1:
            printf("The list is epmty\n");
            antiSound_list_message(0);
            break;
        }
}

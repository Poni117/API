#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AntiSound_List.h"

int main()
{
    if(antiSound_list_testNew() == false)
    {
        return - 1;
    }
    
    list_t* list = antiSound_list_new();

    antiSound_list_testAdd(list);
    antiSound_list_testUpdate(list, 2);
    antiSound_list_testGetItem(list, 3);
    antiSound_list_testGetData(list, 3);
    antiSound_list_testRemove(list, 2);
    antiSound_list_testLength(list);
}

bool antiSound_list_testNew()
{
    printf("------------------------------\n");
    printf("< antiSound_list_testNew >\n\n");

    bool isListExist = false;

    list_t* list = antiSound_list_new();

    if(list != NULL)
    {
        isListExist = true;
    }

    printf("isListExist[%d]\n", isListExist); 
    printf("------------------------------\n");


    return isListExist;
}
void antiSound_list_testAdd(list_t* list)
{
    printf("< antiSound_list_testAdd >\n\n");

    void* data = "name=Dmitry";
    void* data2 = "name=Vasya";
    void* data3 = "name=Anastasia";
    void* data4 = "name=Katya";
    void* data5 = "name=Masha";
    void* data6 = "name=Petya";

    antiSound_list_add(list, data);
    antiSound_list_add(list, data2);
    antiSound_list_add(list, data3);
    antiSound_list_add(list, data4);
    antiSound_list_add(list, data5);
    antiSound_list_add(list, data6);


    antiSound_list_showList(list);

    printf("------------------------------\n");
}

void antiSound_list_testUpdate(list_t* list, int id)
{
    printf("< antiSound_list_testUpdate >\n\n");

    void* newData = "name=Vanya";
    bool isUpdateSuccess = antiSound_list_update(list, id, newData);

    printf("isUpdateSuccess[%d]\n\n", isUpdateSuccess); 

    antiSound_list_showList(list);

    printf("------------------------------\n");
}

void antiSound_list_testGetItem(list_t* list, int id)
{
    printf("< antiSound_list_testGetItem >\n\n");

    list_t* item  =  antiSound_list_getItem(list, id);

    printf("id - [%d]\nitem - [%p]\n", id, item);
    
    printf("------------------------------\n");
}

void antiSound_list_testGetData(list_t* list, int id)
{
    printf("< antiSound_list_testGetData >\n\n");

    void* data = antiSound_list_getData(list, id);

    printf("id - [%d]\ndata - [%s]\n", id, (char*)data);

    printf("------------------------------\n");

}

void antiSound_list_testRemove(list_t* list, int id)
{
    printf("< antiSound_list_testRemove >\n\n");

    bool isRemoveSuccess = antiSound_list_remove(list, id);

    printf("isRemoveSuccess[%d]\n\n", isRemoveSuccess);

    antiSound_list_showList(list);

    printf("------------------------------\n");
}

void antiSound_list_testLength(list_t* list)
{
    printf("< antiSound_list_testLength >\n\n");

    int lengthOfList = antiSound_list_length(list);
    printf("lengthOfList[%d]\n", lengthOfList);
    printf("------------------------------\n");
}

void antiSound_list_showList(list_t* list)
{
    list_t* pointer = list->next;
    while(pointer->next != NULL)
    {
        printf("[%d] - ", pointer->id);
        printf("%s\n", (char* )pointer->data);
        pointer = pointer->next;
    }
}
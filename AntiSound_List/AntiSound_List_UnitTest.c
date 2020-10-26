#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AntiSound_List.h"

int main()
{
    list_t* list = antiSound_list_new();

    antiSound_list_testAdd(list);
    antiSound_list_testUpdate(list);
    antiSound_list_testGetItem(list);
    antiSound_list_testRemove(list);
    antiSound_list_testLength(list);
}

void antiSound_list_testAdd(list_t* list)
{
    void* data = "name=Dmitry";
    void* data2 = "name=Vasya";
    void* data3 = "name=Anastasia";
    void* data4 = "name=Katya";
    void* data5 = "name=Masha";
    void* data6 = "name=Petya";

    printf("id[%d]\n", antiSound_list_add(list, data));
    printf("id[%d]\n", antiSound_list_add(list, data2));
    printf("id[%d]\n", antiSound_list_add(list, data3));
    printf("id[%d]\n", antiSound_list_add(list, data4));
    printf("id[%d]\n", antiSound_list_add(list, data5));
    printf("id[%d]\n", antiSound_list_add(list, data6));
    printf("------------------------------\n");
}

void antiSound_list_testUpdate(list_t* list)
{
    void* newData = "name=Vanya";
    bool isUpdateSuccess = antiSound_list_update(list, 3, newData);

    printf("isUpdateSuccess[%d]\n", isUpdateSuccess); 
    printf("------------------------------\n");
}

void antiSound_list_testGetItem(list_t* list)
{
    list_t* item  =  antiSound_list_getItem(list, 0);
    printf("getItemId[%d]\n", item->id);
    printf("------------------------------\n");
}

void antiSound_list_testRemove(list_t* list)
{
    bool isRemoveSuccess = antiSound_list_remove(list, 5);
    printf("isRemoveSuccess[%d]\n", isRemoveSuccess);
    printf("------------------------------\n");
}

void antiSound_list_testLength(list_t* list)
{
    int lengthOfList = antiSound_list_length(list);
    printf("lengthOfList[%d]\n", lengthOfList);
    printf("------------------------------\n");
}
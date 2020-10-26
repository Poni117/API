#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AntiSound_List.h"

int main()
{
    list_t* newList = antiSound_list_new();

    void* data = "name=Dmitry";
    void* data2 = "name=Vasya";
    void* data3 = "name=Anastasia";
    void* data4 = "name=Katya";
    void* data5 = "name=Masha";
    void* data6 = "name=Petya";
    void* newData = "name=Vanya";

    printf("id[%d]\n", antiSound_list_add(newList, data));
    printf("id[%d]\n", antiSound_list_add(newList, data2));
    printf("id[%d]\n", antiSound_list_add(newList, data3));
    printf("id[%d]\n", antiSound_list_add(newList, data4));
    printf("id[%d]\n", antiSound_list_add(newList, data5));
    printf("id[%d]\n", antiSound_list_add(newList, data6));

    printf("isUpdateSuccess[%d]\n", antiSound_list_update(newList, 3, newData));

    list_t* item  =  antiSound_list_getItem(newList, 0);
    printf("getItemId[%d]\n", item->id);

    printf("isRemoveSuccess[%d]\n", antiSound_list_remove(newList, 5));

    printf("lengthOfList[%d]\n", antiSound_list_length(newList));
}

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

}

list_t* antiSound_list_testNew()
{
    antiSound_list_message(0);
    printf("< antiSound_list_testNew >\n");

    bool status = false;

    list_t* list = antiSound_list_new();

    if(list != NULL)
    {
        status = true;
    }

    printf("status[%d]\n", status);

    antiSound_list_message(0);

    return list;
}

void antiSound_list_testAdd(list_t* list)
{
    printf("< antiSound_list_testAdd >\n\n");

    bool status = false;

    void* data = "name=Dmitry";

    int id = antiSound_list_add(list, data);

    if(id != -1)
    {
        status = true;
    }

    printf("status[%d]\n", status);

    antiSound_list_message(0);
}

void antiSound_list_testUpdate(list_t* list)
{
    printf("< antiSound_list_testUpdate >\n\n");

    bool status = false;

    void* newData = "name=Roma";
    int id = 2;

    status = antiSound_list_update(list, id, newData);

    printf("status[%d]\n", status); 

    antiSound_list_message(0);
}

void antiSound_list_testGetItem(list_t* list)
{
    bool status = false;

    printf("< antiSound_list_testGetItem >\n\n");

    int id = 3;
    list_t* item = antiSound_list_getItem(list, id);

    if(item != NULL)
    {
        status = true;
    }
    
    printf("status[%d]\n", status);

    antiSound_list_message(0);
}

void antiSound_list_testGetData(list_t* list)
{
    printf("< antiSound_list_testGetData >\n\n");

    bool status = false;

    int id = 3;
    void* data = antiSound_list_getData(list, id);

    if(data != NULL)
    {
        status = true;
    } 
    
    printf("status[%d]\n", status);
    antiSound_list_message(0);
}

void antiSound_list_testRemove(list_t* list)
{
    printf("< antiSound_list_testRemove >\n\n");

    bool status = false;

    int id = 1;

    status = antiSound_list_remove(list, id);

    printf("status[%d]\n", status);

    antiSound_list_message(0);
}

void antiSound_list_testLength(list_t* list)
{
    printf("< antiSound_list_testLength >\n\n");

    bool status = false;

    int lengthOfList = antiSound_list_length(list);

    if(lengthOfList != -1)
    {
        status = true;
    }

    printf("status[%d]\n", status);

    antiSound_list_message(0);

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

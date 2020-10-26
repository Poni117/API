#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AntiSound_List.h"

int main()
{
    printf("choose test:\ntestNew/testAdd/testGetItem/testGetData/testUpdate/testRemove/testShowList\n");

    list_t* list = NULL;

    while(true)
    {
        char start[256] = "\0";
        scanf("%s", start);

        if(strcmp(start, "exit") == 0)
        {
            return - 1;
        }

        if (strcmp(start, "testNew") == 0)
        {
            if(antiSound_list_testNew() == false)
            {
                return - 1;
            }

            list =  antiSound_list_new();
            break;
        }

        if (strcmp(start, "testNew") != 0)
        {
            printf("------------------------------\n");
            printf("a list is`t create\nrun testNew\n");
            printf("------------------------------\n");

        }
        
    }

    while(true)
    {
        char test[256] = "\0";
        scanf("%s", test);

        if (strcmp(test, "testAdd") == 0)
        {
            antiSound_list_testAdd(list);
        }

        if (strcmp(test, "testUpdate") == 0)
        {
            antiSound_list_testUpdate(list); 
        }

        if (strcmp(test, "testGetItem") == 0)
        {
            antiSound_list_testGetItem(list);
        }

        if (strcmp(test, "testGetData") == 0)
        {
            antiSound_list_testGetData(list);
        }

        if (strcmp(test, "testRemove") == 0)
        {
            antiSound_list_testRemove(list);
        }

        if(strcmp(test, "testLength") == 0)
        {
            antiSound_list_testLength(list);
        }

        if(strcmp(test, "testShowList") == 0)
        {
            antiSound_list_testShowList(list);
        }

        if(strcmp(test, "exit") == 0)
        {
            break;
        }
    }
}

bool antiSound_list_testNew()
{
    printf("------------------------------\n");
    printf("< antiSound_list_testNew >\n\n");

    bool isListCreated = false;

    list_t* list = antiSound_list_new();

    if(list != NULL)
    {
        isListCreated = true;
    }

    printf("isListCreated[%d]\n", isListCreated); 
    printf("------------------------------\n");


    return isListCreated;
}

void antiSound_list_testAdd(list_t* list)
{
    printf("< antiSound_list_testAdd >\n\n");

    printf("Insert Data\n");

    char data[256] = "\0";
    scanf("%s", data);

    antiSound_list_add(list, data);

    printf("------------------------------\n");
}

void antiSound_list_testUpdate(list_t* list)
{
    printf("< antiSound_list_testUpdate >\n\n");

    printf("Insert Id:\n");
    char id[256] = "\0";
    scanf("%s", id);
    
    printf("Insert newData\n");
    char newData[256] = "\0";
    scanf("%s", newData);

    printf("\n");

    list_t* updatedItem = antiSound_list_getItem(list, atoi(id));
    
    printf("updateItem:\n[%d] - [%s] to [%s]\n\n", updatedItem->id, (char*)updatedItem->data, (char*)newData);

    bool isUpdateSuccess = antiSound_list_update(list, atoi(id), newData);
    printf("isUpdateSuccess[%d]\n\n", isUpdateSuccess); 

    printf("------------------------------\n");
}

void antiSound_list_testGetItem(list_t* list)
{
    printf("< antiSound_list_testGetItem >\n\n");

    printf("Insert Id:\n");

    char id[256] = "\0";
    scanf("%s", id);

    list_t* item  =  antiSound_list_getItem(list, atoi(id));
    printf("item - [%p]\n", item);
    
    printf("------------------------------\n");
}

void antiSound_list_testGetData(list_t* list)
{
    printf("< antiSound_list_testGetData >\n\n");

    printf("Insert Id:\n");

    char id[256] = "\0";
    scanf("%s", id);

    void* data = antiSound_list_getData(list, atoi(id));
    printf("id - [%d]\ndata - [%s]\n", atoi(id), (char*)data);

    printf("------------------------------\n");

}

void antiSound_list_testRemove(list_t* list)
{
    printf("< antiSound_list_testRemove >\n\n");

    printf("Insert Id:\n");

    char id[256] = "\0";
    scanf("%s", id);

    list_t* deletedItem = antiSound_list_getItem(list, atoi(id));
    printf("removedItem:\nid[%d] - [%s]\n\n", deletedItem->id, (char*)deletedItem->data);

    bool isRemoveSuccess = antiSound_list_remove(list, atoi(id));
    printf("isRemoveSuccess[%d]\n\n", isRemoveSuccess);

    printf("------------------------------\n");
}

void antiSound_list_testLength(list_t* list)
{
    printf("< antiSound_list_testLength >\n\n");

    if(list == NULL)
    {
        printf("list is epmty\n");
        printf("------------------------------\n");
        return;
    }

    int lengthOfList = antiSound_list_length(list);

    printf("lengthOfList[%d]\n", lengthOfList);
    printf("------------------------------\n");
}

void antiSound_list_testShowList(list_t* list)
{
    list_t* pointer = list->next;
    if(list == NULL)
    {
        printf("list is epmty\n");
        printf("------------------------------\n");
        return;
    }

    while(pointer != NULL)
    {
        printf("[%d] - ", pointer->id);
        printf("%s\n", (char* )pointer->data);
        pointer = pointer->next;
    }
    
    printf("------------------------------\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AntiSound_List.h"

void antiSound_list_message(int id);

int main()
{
    antiSound_list_message(0);

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
            antiSound_list_message(1);
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
    antiSound_list_message(2);
    printf("< antiSound_list_testNew >\n\n");

    bool isListCreated = false;

    list_t* list = antiSound_list_new();

    if(list != NULL)
    {
        isListCreated = true;
    }

    printf("isListCreated[%d]\n", isListCreated); 
    antiSound_list_message(2);


    return isListCreated;
}

void antiSound_list_testAdd(list_t* list)
{
    printf("< antiSound_list_testAdd >\n\n");

    antiSound_list_message(4);
    char data[256] = "\0";
    scanf("%s", data);

    antiSound_list_add(list, data);

    antiSound_list_message(2);
}

void antiSound_list_testUpdate(list_t* list)
{
    printf("< antiSound_list_testUpdate >\n\n");

    antiSound_list_message(3);
    char id[256] = "\0";
    scanf("%s", id);
    
    antiSound_list_message(4);
    char newData[256] = "\0";
    scanf("%s", newData);

    printf("\n");

    list_t* updatedItem = antiSound_list_getItem(list, atoi(id));
    
    printf("updateItem:\n[%d] - [%s] to [%s]\n\n", updatedItem->id, (char*)updatedItem->data, (char*)newData);

    bool isUpdateSuccess = antiSound_list_update(list, atoi(id), newData);
    printf("isUpdateSuccess[%d]\n\n", isUpdateSuccess); 

    antiSound_list_message(2);
}

void antiSound_list_testGetItem(list_t* list)
{
    printf("< antiSound_list_testGetItem >\n\n");

    antiSound_list_message(3);
    char id[256] = "\0";
    scanf("%s", id);

    list_t* item  =  antiSound_list_getItem(list, atoi(id));
    printf("item - [%p]\n", item);
    
    antiSound_list_message(2);
}

void antiSound_list_testGetData(list_t* list)
{
    printf("< antiSound_list_testGetData >\n\n");

    antiSound_list_message(3);

    char id[256] = "\0";
    scanf("%s", id);

    void* data = antiSound_list_getData(list, atoi(id));
    printf("id - [%d]\ndata - [%s]\n", atoi(id), (char*)data);

    antiSound_list_message(2);

}

void antiSound_list_testRemove(list_t* list)
{
    printf("< antiSound_list_testRemove >\n\n");

    antiSound_list_message(3);

    char id[256] = "\0";
    scanf("%s", id);

    list_t* deletedItem = antiSound_list_getItem(list, atoi(id));
    printf("removedItem:\nid[%d] - [%s]\n\n", deletedItem->id, (char*)deletedItem->data);

    bool isRemoveSuccess = antiSound_list_remove(list, atoi(id));
    printf("isRemoveSuccess[%d]\n\n", isRemoveSuccess);

    antiSound_list_message(2);
}

void antiSound_list_testLength(list_t* list)
{
    printf("< antiSound_list_testLength >\n\n");

    if(list == NULL)
    {
        antiSound_list_message(5);
        return;
    }

    int lengthOfList = antiSound_list_length(list);

    printf("lengthOfList[%d]\n", lengthOfList);
    antiSound_list_message(2);

}

void antiSound_list_testShowList(list_t* list)
{
    printf("< antiSound_list_testShowList >\n\n");

    list_t* pointer = list->next;
    if(list == NULL)
    {
        antiSound_list_message(5);
        return;
    }

    while(pointer != NULL)
    {
        printf("[%d] - ", pointer->id);
        printf("%s\n", (char* )pointer->data);
        pointer = pointer->next;
    }
    
    antiSound_list_message(2);
}

void antiSound_list_message(int id)
{
        switch (id)
        {
        case 0:
            printf("choose test:\ntestNew/testAdd/testGetItem/testGetData/testUpdate/testRemove/testShowList\n");
            break;
        
        case 1:
            antiSound_list_message(2);
            printf("a list is`t create\nrun testNew\n");
            antiSound_list_message(2);
            break;
        case 2:
            printf("------------------------------\n");
            break;
        case 3:
            printf("Insert Id:\n");
            break;
        case 4:
            printf("Insert Data\n");
            break;
        case 5:
            printf("list is epmty\n");
            antiSound_list_message(2);
            break;
        }
}

#include "AntiSound_List.h"
#include "Task.h"

list_t* antiSound_list_new()
{
    list_t* list = NULL;
    antiSound_list_add(list);

    return list;
}

int antiSound_list_add(list_t* list, int data)
{
    if(list == NULL)
    {
        list = malloc(sizeof(list_t));
        list->data = data;
        list->task->id = 0;
        list->next = NULL;

        return  pointer->task->id;
    }

    list_t* pointer = list;

    while(pointer->next != NULL)
    {
        pointer = pointer->next;
    }
    
    pointer->next = malloc(sizeof(list_t));

    pointer->next->task = malloc(sizeof(task_t));
    
    pointer->next->data = data;
    pointer->next->task->id = pointer->task->id + 1;
    pointer->next->next = NULL;
    
    return pointer->next->task->id;
}

bool antiSound_list_update(list_t* list, int id, void* newData)
{
    bool isUpdateSuccess = false;
    bool isIdExist = false;

    list_t* pointer = list;

    while(pointer->next != NULL)
    {
        if(pointer->next->task->id == id)
        {
            isIdExist = true;
            break;
        }
        pointer = pointer->next;
    }

    if(isIdExist != false || newData != NULL)
    {
        pointer->next->data = newData;
        isUpdateSuccess = true;
    }

    return isUpdateSuccess;
}

void* antiSound_list_get(list_t* list, int id)
{
    bool isUpdateSuccess = false;
    bool isIdExist = false;

    list_t* pointer = list;

    while(pointer->next != NULL)
    {
        if(pointer->next->task->id == id)
        {
            isIdExist = true;
            break;
        }
        pointer = pointer->next;
    }

    if(isIdExist == false)
    {
        return isUpdateSuccess;
    }

    return pointer->next->data;
}

bool antiSound_list_remove(list_t* list, int id)
{
    list_t* pointer = list;

    bool isIdExist = false;

    while(pointer->next != NULL)
    {
        if(pointer->next->task->id == id)
        {
            isIdExist = true;
            break;
        }
        
        pointer = pointer->next;
    }

    if(isIdExist == false)
    {
        return isIdExist;
    }

    list_t* deleteList = pointer->next;
    pointer->next = deleteList->next;
    free(deleteList);

    int i = 0;
    while(pointer != NULL)
    {
        pointer->task->id = i;
        i++;

        pointer = pointer->next;
    }

    return isIdExist;
}

int antiSound_list_length(list_t* list)
{   
    list_t* pointer = list;

    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }
    
    return pointer->task->id;
}
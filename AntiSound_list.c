#include "AntiSound_List.h"
#include "Task.h"

list_t* antiSound_list_new()
{
    list_t* list = malloc(sizeof(list_t));
    list->data = NULL;
    list->next = NULL;
    list->task = NULL;

    return list;
}

int antiSound_list_add(list_t* list, void* data)
{
    if(list->task == NULL)
    {
        list->data = data;
        list->task = malloc(sizeof(task_t));
        list->task->id = 0;

        return list->task->id;
    }

    list_t* pointer = list;

    while(pointer->next != NULL)
    {
        pointer = pointer->next;
    }
    
    pointer->next = malloc(sizeof(list_t));
    pointer->next->data = data;
    pointer->next->next = NULL;
    
    pointer->next->task = malloc(sizeof(task_t));
    pointer->next->task->id = pointer->task->id + 1;
    
    return pointer->next->task->id;
}

bool antiSound_list_update(list_t* list, int id, void* newData)
{
    bool isUpdateSuccess = false;

    if(newData == NULL)
    {
        return isUpdateSuccess;
    }

    void* updateData = antiSound_list_get(list, id);
    updateData = newData;

    return isUpdateSuccess = true;
}

void* antiSound_list_get(list_t* list, int id)
{
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
        //exception
    }

    return pointer->next->data;
}

bool antiSound_list_remove(list_t* list, int id)
{
    bool isIdExist = false;

    list_t* pointer = list;

    if(id == 0)
    {
        pointer = pointer->next;
        free(list);
        while(pointer->next != NULL)
        {
            pointer->task->id = pointer->task->id - 1;
            pointer = pointer->next;
        }

        return isIdExist = true;
    }

    list_t* lastList = list;

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

    if(pointer->next != NULL)
    {
        list_t* deleteList = pointer->next;
        pointer->next = deleteList->next;
        free(deleteList);
    }

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
    
    return pointer->task->id + 1;
}
#include  <stdlib.h>
#include  <stdbool.h>
#include  <stdio.h>
#include  <pthread.h>

#include "../AntiSound_FIFO/AntiSound_FIFO.h"



fifo_t* antiSound_fifo_initializeFifo()
{
    fifo_t* head = malloc(sizeof(fifo_t));
    head->id = -1;
    head->data = NULL;
    head->next = NULL;
    head->tale = head;

    return head;
}

bool antiSound_fifo_push(fifo_t* head, void* data)
{
    head->tale->next = antiSound_fifo_initializeFifo();

    head->tale->next->id = head->tale->id + 1;
    head->tale->next->data = data;
    head->tale = head->tale->next;

    return true;
}

bool antiSound_fifo_pop(fifo_t* head)
{
    fifo_t* newHead = head->next->next;
    free(head->next);
    head->next = newHead;

    if(head->next == NULL)
    {
        head->tale = head;
    }
    
    return true;
}

bool antiSound_fifo_isEmpty(fifo_t* head)
{
    bool isNextItemExist = true;

    if(head->next != NULL)
    {
        isNextItemExist = false; 
    }

    return isNextItemExist;
}

int antiSound_fifo_size(fifo_t* head)
{
    fifo_t* pointer = head->next;

    int size = 0;

    while(pointer != NULL)
    {
        size++;
        pointer = pointer->next;
    }

    return size;
}


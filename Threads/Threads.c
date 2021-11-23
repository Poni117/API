#include "Threads.h"
#include "../FIFO/FIFO.h"
#include "../HTTP/HTTP.h"
#include "../Item/Item.h"
#include "../API/API.h"

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include <unistd.h>

void* threads_checkFifo(void* data)
{
    fifo_t* fifo = data;
    
    while(true)
    {
        if(fifo_isEmpty(fifo) == false)
        {
            fifo_pop(fifo);

            datas_t* task = fifo->next->data;

            printf("exe[%d]\n", threads_exeRequest(task));

            http_freeRequest(fifo->next->data);
        }
    }

    return NULL;
}

bool threads_exeRequest(datas_t* datas)
{
    bool isExeRequestSuccess = false;

    if(http_checkParameters(datas->request, datas->response, datas->root) == false)
    {
        return isExeRequestSuccess;
    }

    if(strcmp(datas->request->method, "GET") == 0)
    {   
        isExeRequestSuccess = item_read(datas->request, datas->response, datas->root);
    }
    
    if(strcmp(datas->request->method, "POST") == 0)
    {
        isExeRequestSuccess = item_create(datas->request, datas->root);
    }

    if(strcmp(datas->request->method, "PUT") == 0)
    {
        isExeRequestSuccess = item_update(datas->request, datas->root);
    }

    if(strcmp(datas->request->method, "DELETE") == 0)
    {
        isExeRequestSuccess = item_remove(datas->request, datas->root);
    }

    printf("isExeRequestSuccess[%d]\n", isExeRequestSuccess);

    return isExeRequestSuccess;
}
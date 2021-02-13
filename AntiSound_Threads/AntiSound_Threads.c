#include "AntiSound_Threads.h"
#include "../AntiSound_FIFO/AntiSound_FIFO.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_API/AntiSound_API.h"

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include <unistd.h>

void* antiSound_threads_checkFifo(void* data)
{
    fifo_t* fifo = data;
    
    while(true)
    {
        if(antiSound_fifo_isEmpty(fifo) == false)
        {
            antiSound_fifo_pop(fifo);
            datas_t* task = fifo->next->data;
            printf("exe[%d]\n", antiSound_threads_exeRequest(task));
            antiSound_http_freeRequest(fifo->next->data);
        }
    }

    return NULL;
}

bool antiSound_threads_exeRequest(datas_t* datas)
{
    bool isExeRequestSuccess = false;

    if(antiSound_http_checkParameters(datas->request, datas->response, datas->root) == false)
    {
        return isExeRequestSuccess;
    }

    if(strcmp(datas->request->method, "GET") == 0)
    {   
        isExeRequestSuccess = antiSound_item_read(datas->request, datas->response, datas->root);
    }
    
    if(strcmp(datas->request->method, "POST") == 0)
    {
        isExeRequestSuccess = antiSound_item_create(datas->request, datas->root);
    }

    if(strcmp(datas->request->method, "PUT") == 0)
    {
        isExeRequestSuccess = antiSound_item_update(datas->request, datas->root);
    }

    if(strcmp(datas->request->method, "DELETE") == 0)
    {
        isExeRequestSuccess = antiSound_item_remove(datas->request, datas->root);
    }

    printf("isExeRequestSuccess[%d]\n", isExeRequestSuccess);

    return isExeRequestSuccess;
}
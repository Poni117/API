#include "AntiSound_HTTP.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool antiSound_http_testInitializeItem()
{
    bool isInitializeItemSuccess = false;

    bool isIdInitialized = false;
    bool isDataInitialized = false;

    item_t* item = antiSound_http_initializeItem();

    if(item->id == -1)
    {
        isIdInitialized = true;
    }

    if(item->data == NULL)
    {
        isDataInitialized = true;
    }

    if(isIdInitialized == true && isDataInitialized == true)
    {
        isInitializeItemSuccess = true;
    }

    if(isInitializeItemSuccess == false)
    {
        printf("---------------------------------\n");
        printf("antiSound_http_testInitializeItem\n");
        printf("isInitializeItemSuccess[%d]\n", isInitializeItemSuccess);
    }

    return isInitializeItemSuccess;
}

bool antiSound_http_testGetQueryParamter(request_t* request, char* soughtItem)
{
    bool isGetQueryParamterSuccess = false;

    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, soughtItem);

    if(queryParameter != NULL)
    {
        isGetQueryParamterSuccess = true;
    }

    if(isGetQueryParamterSuccess == false)
    {
        printf("---------------------------------\n");
        printf("antiSound_http_testGetQueryParamter\n");
        printf("isGetQueryParamterSuccess[%d]\n", isGetQueryParamterSuccess);
    }

    return isGetQueryParamterSuccess;
}

bool antiSound_http_testGetBodyParamter(request_t* request, char* soughtItem)
{
    bool isGetBodyParamterSuccess = false;

    body_t* body = antiSound_http_getBodyParamter(request, soughtItem);

    if(body != NULL)
    {
        isGetBodyParamterSuccess = true;
    }

    if(isGetBodyParamterSuccess == false)
    {
        printf("---------------------------------\n");
        printf("antiSound_http_testGetBodyParamter\n");
        printf("isGetbodyParamterSuccess[%d]\n", isGetBodyParamterSuccess);
    }

    return isGetBodyParamterSuccess;
}

bool antiSound_http_testGetItem(list_t* list, int id)
{
    bool isGetItemSuccess = false;

    item_t* item = antiSound_http_getItem(list, id);

    if(item != NULL)
    {
        isGetItemSuccess = true;
    }

    if(isGetItemSuccess == false)
    {
        printf("---------------------------------\n");
        printf("antiSound_http_testGetItem\n");
        printf("isGetItemSuccess[%d]\n", isGetItemSuccess);
    }

    return isGetItemSuccess;
}
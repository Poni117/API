#include "AntiSound_HTTP.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



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

    bodyParameter_t* body = antiSound_http_getBodyParamter(request, soughtItem);

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


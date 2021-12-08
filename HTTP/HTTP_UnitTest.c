#include "./HTTP.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



bool http_testGetQueryParamter(request_t* request, char* soughtItem)
{
    bool isGetQueryParamterSuccess = false;

    queryParameter_t* queryParameter = http_getQueryParamter(request, soughtItem);

    if(queryParameter != NULL)
    {
        isGetQueryParamterSuccess = true;
    }

    if(isGetQueryParamterSuccess == false)
    {
        printf("---------------------------------\n");
        printf("http_testGetQueryParamter\n");
        printf("isGetQueryParamterSuccess[%d]\n", isGetQueryParamterSuccess);
    }

    return isGetQueryParamterSuccess;
}

bool http_testGetBodyParamter(request_t* request, char* soughtItem)
{
    bool isGetBodyParamterSuccess = false;

    body_t* body = http_getBodyParamter(request, soughtItem);

    if(body != NULL)
    {
        isGetBodyParamterSuccess = true;
    }

    if(isGetBodyParamterSuccess == false)
    {
        printf("---------------------------------\n");
        printf("http_testGetBodyParamter\n");
        printf("isGetbodyParamterSuccess[%d]\n", isGetBodyParamterSuccess);
    }

    return isGetBodyParamterSuccess;
}


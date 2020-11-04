#include "AntiSound_HTTP_Isolate.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* antiSound_http_isolateUrl(char* requestData)
{
    size_t sizeOfRequestData = strlen(requestData);

    int i = 0;

    while (i < sizeOfRequestData)
    {
        if(requestData[i] == '\n')
        {
            break;
        }
        i++;
    }
    i++;

    int j = 0;

    char* isolatedUrl = calloc(j, sizeof(char));

    while (i < sizeOfRequestData)
    {
        if(requestData[i] == '\n')
        {
            break;
        }
        isolatedUrl = realloc(isolatedUrl, j + 1);
        isolatedUrl[j] = requestData[i];

        j++;
        i++;
    }
    
    return isolatedUrl;
}
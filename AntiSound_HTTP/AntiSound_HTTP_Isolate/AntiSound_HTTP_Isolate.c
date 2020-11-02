#include "AntiSound_HTTP_Isolate.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* antiSound_http_isolateHttp(char* requestData)
{
    size_t sizeOfRequestData = strlen(requestData);

    int i = 0;

    while (i < sizeOfRequestData)
    {
        if(requestData[i] == '/')
        {
            break;
        }
        i++;
    }
    
    i = i + 2;

    char bufferOfIsolateHttp[256] = "\0";

    int j = 0;
    while (i < sizeOfRequestData)
    {
        if(requestData[i] == '\n')
        {
            break;
        }
        bufferOfIsolateHttp[j] = requestData[i];
        j++;
        i++;
    }

    size_t sizeOfBufferOfIsolateHttp = strlen(bufferOfIsolateHttp);

    char* isolatedHttp = calloc(sizeOfBufferOfIsolateHttp + 1, sizeof(char));
    strncpy(isolatedHttp, bufferOfIsolateHttp, sizeOfBufferOfIsolateHttp); 

    return isolatedHttp;
}

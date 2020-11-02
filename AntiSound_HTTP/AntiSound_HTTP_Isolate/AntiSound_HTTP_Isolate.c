#include "AntiSound_HTTP_Isolate.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* antiSound_http_isolateHttp(request_t* request, char* requestData)
{
    size_t sizeOfRequestData = strlen(requestData);

    char* method = request->method;
    
    int i = 0;

    while (i < sizeOfRequestData)
    {
        if(requestData[i] == '/')
        {
            break;
        }
        i++;
    }
    
    if(strcmp(method, "POST") == 0 || strcmp(method, "GET") == 0)
    {
        i = i + 2;
    }

    if(strcmp(method, "PUT") == 0 || strcmp(method, "DELETE") == 0)
    {
        while (i < sizeOfRequestData)
        {
            if(requestData[i] == ' ')
            {
                break;
            }
            i++;
        }
        
        i++;
    }

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

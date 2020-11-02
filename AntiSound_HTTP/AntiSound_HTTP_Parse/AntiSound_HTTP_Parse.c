#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP_Isolate/AntiSound_HTTP_Isolate.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool antiSound_http_parseMethod(request_t* request, char* requestData)
{
    bool isParseMethodSuccess = false;

    size_t sizeOfRequesData = strlen(requestData);

    char bufferOfMethod[256] = "\0";
    
    int i = 0;

    while(i < sizeOfRequesData)
    {
        if(requestData[i] == ' ')
        {
            break;
        }

        bufferOfMethod[i] = requestData[i];
        i++;
    }

    size_t sizeOfBufferOfMethod = strlen(bufferOfMethod);

    request->method = calloc(sizeOfBufferOfMethod + 1, sizeof(char));
    strncpy(request->method, bufferOfMethod, sizeOfBufferOfMethod);

    if(request->method[0] != '\0')
    {
        isParseMethodSuccess = true;
    }

    return isParseMethodSuccess;
}

bool antiSound_http_parseHttpVersion(request_t* request, char* requestData)
{
    bool isParseHttpVersionSuccess = false;

    char* isolatedHttp = antiSound_http_isolateHttp(request, requestData);

    request->http = malloc(sizeof(httpVersion_t));


    if(isolatedHttp[0] == '\0')
    {
        return isParseHttpVersionSuccess;
    }

    size_t sizeOfIsolatedHttp = strlen(isolatedHttp);

    int i = 0;
    while(i < sizeOfIsolatedHttp)
    {
        if(isolatedHttp[i] == '/')
        {
            break;
        }
        i++;
    }

    i++;

    char bufferOfMinor[256] = "\0";


    int j = 0;

    while (i < sizeOfIsolatedHttp)
    {
        if(isolatedHttp[i] == '.')
        {
            break;
        }
        bufferOfMinor[j] = isolatedHttp[i];

        j++;
        i++;
    }
    

    size_t sizeOfBufferMinor = strlen(bufferOfMinor);

    char* charMinor = calloc(sizeOfBufferMinor + 1, sizeof(char));
    strncpy(charMinor, bufferOfMinor, sizeOfBufferMinor);

    request->http->minor = atoi(charMinor);

    i++;

    char bufferOfMajor[256] = "\0";

    j = 0;

    while (i < sizeOfIsolatedHttp)
    {
        if(isolatedHttp[i] == '\0')
        {
            break;
        }

        bufferOfMajor[j] = isolatedHttp[i];
        j++;
        i++;
    }


    size_t sizeOfBufferMajor = strlen(bufferOfMajor);

    char* charMajor = calloc(sizeOfBufferMajor + 1, sizeof(char));
    strncpy(charMajor, bufferOfMajor, sizeOfBufferMajor);

    request->http->major = atoi(charMajor);

    if(charMinor[0] != '\0' && charMajor[0] != '\0')
    {
        isParseHttpVersionSuccess = true;
    }

    return isParseHttpVersionSuccess;
}
#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP_Isolate/AntiSound_HTTP_Isolate.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

request_t* antiSound_http_initializeRequest()
{
    request_t* request = malloc(sizeof(request_t));

    request->body = NULL;
    request->headers = NULL;
    request->http = malloc(sizeof(httpVersion_t));

    request->url = malloc(sizeof(url_t));
    request->method = NULL;
    request->headers = NULL;
    request->body = NULL;

    request->url->queryParameters = malloc(sizeof(list_t));
    request->url->queryParameters->data = NULL;
    request->url->queryParameters->id = -1;
    request->url->queryParameters->next = NULL;

    return request;
}

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

bool antiSound_http_parseQuaryParameters(request_t* request, char* requestData)
{
    bool isParseQuareParametersSuccess = false;

    if(requestData == NULL)
    {
        return isParseQuareParametersSuccess;
    }

    list_t* pointer = request->url->queryParameters;

    while (pointer->next != NULL)
    {
       pointer = pointer->next;
    }
    
    char* isolatedQuereParameters = NULL;

    if(pointer->data == NULL)
    {
        isolatedQuereParameters = antiSound_http_isolsteQuaryParameters(requestData);
    }
    else
    {
        isolatedQuereParameters = requestData;
    }
    
    size_t sizeOfIsolatedQueryParameters = strlen(isolatedQuereParameters);

    int i = 0;

    char* quaryParameter = calloc(1, sizeof(char));

    int j = 0;
    while(i < sizeOfIsolatedQueryParameters)
    {
        if(isolatedQuereParameters[i] == '&' || isolatedQuereParameters[i] == '\0')
        {
            break;
        }
        quaryParameter = (char*)realloc(quaryParameter, i + 1);
        quaryParameter[j] = isolatedQuereParameters[i];
        i++;
        j++;
    }

    if(quaryParameter[0] != '\0')
    {
        isParseQuareParametersSuccess = true;
    }

    size_t sizeOfQueryParameter = strlen(quaryParameter);
    
    while(pointer->next != NULL)
    {
        pointer = pointer->next;
    }

    pointer->next = malloc(sizeof(list_t));

    pointer->next->data = calloc(sizeOfQueryParameter + 1, sizeof(char));
    strncpy(pointer->next->data, quaryParameter, sizeOfQueryParameter);

    pointer->next->id = pointer->id + 1;

    pointer->next->next = NULL;

    char* alteradeIsolateQuareParameters = strchr(isolatedQuereParameters, '&');
    
    if(alteradeIsolateQuareParameters != NULL)
    {
        alteradeIsolateQuareParameters++;
        antiSound_http_parseQuaryParameters(request, alteradeIsolateQuareParameters);
    }

    return isParseQuareParametersSuccess;
}
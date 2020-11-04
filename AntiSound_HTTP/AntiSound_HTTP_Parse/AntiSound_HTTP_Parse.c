#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP_Isolate/AntiSound_HTTP_Isolate.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

request_t* antiSound_http_initializeRequest()
{
    request_t* request = malloc(sizeof(request_t));
    request->method = NULL;

    request->body = malloc(sizeof(list_t));
    request->body->data = NULL;
    request->body->id = -1;
    request->body->next = NULL;

    request->headers = malloc(sizeof(list_t));
    request->headers->data = NULL;
    request->headers->id = -1;
    request->headers->next = NULL;

    request->http = malloc(sizeof(httpVersion_t));
    request->http->major = -1;
    request->http->minor = -1;

    request->url = malloc(sizeof(url_t));
    request->url->host = NULL;
    request->url->port = NULL;
    request->url->path = NULL;
    request->url->anchor = NULL;

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

    pointer->next->data = realloc(quaryParameter, sizeOfQueryParameter);

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

bool antiSound_http_parseUrl(request_t* request, char* requestData)
{
    bool isParseUrlSuccess = false;
    bool isHostExist = false;
    bool isPortExist = false;

    char* isolatedUrl = antiSound_http_isolateUrl(requestData);

    size_t sizeOfIsolatedUrl = strlen(isolatedUrl);

    int i = 0;
    
    while(i < sizeOfIsolatedUrl)
    {
        if(isolatedUrl[i] == ' ')
        {
            break;
        }
        i++;
    }
    i++;

    int j = 0;

    char* host = calloc(j, sizeof(char));

    while (i < sizeOfIsolatedUrl)
    {
        if(isolatedUrl[i] == ':')
        {
            break;
        }
        host = realloc(host, j + 1);
        host[j] = isolatedUrl[i];
        j++;
        i++;
        /* code */
    }
    if(host[0] != '\0')
    {
        isHostExist = true;
    }

    size_t sizeOfHost = strlen(host);
    request->url->host = realloc(host, sizeOfHost);

    i++;

    j = 0;

    char* port = calloc(j, sizeof(char));

    while (i < sizeOfIsolatedUrl)
    {
        if(isolatedUrl[i] == '\n')
        {
            break;
        }
        port = realloc(port, j + 1);
        port[j] = isolatedUrl[i];
        j++;
        i++;
    }
    if(port[0] != '\0')
    {
        isPortExist = true;
    }

    size_t sizeOfPort = strlen(port);

    request->url->port = realloc(port, sizeOfPort);

    if(isHostExist == true && isPortExist == true)
    {
        isParseUrlSuccess = true;
    }
    
    return isParseUrlSuccess;
}
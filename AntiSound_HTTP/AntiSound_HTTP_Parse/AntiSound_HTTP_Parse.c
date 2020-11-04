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

    char* method = antiSound_http_isolateData(requestData, requestData[0], ' ');

    size_t sizeOfMethod = strlen(method);

    request->method = realloc(method, sizeOfMethod);

    if(request->method[0] != '\0')
    {
        isParseMethodSuccess = true;
    }

    return isParseMethodSuccess;
}

bool antiSound_http_parseHttpVersion(request_t* request, char* requestData)
{
    bool isParseHttpVersionSuccess = false;

    char* method = request->method;

    char* isolatedHttp = NULL;

    if(strcmp(method, "POST") == 0 || strcmp(method, "GET") == 0)
    {
        char* alteradeIsolatedHttp = strchr(requestData, '/');
        isolatedHttp = antiSound_http_isolateData(alteradeIsolatedHttp, ' ', '\n');
    }

    if(strcmp(method, "PUT") == 0 || strcmp(method, "DELETE") == 0)
    {
        isolatedHttp = antiSound_http_isolateData(requestData, '/', '\n');
    }
    

    if(isolatedHttp[0] == '\0')
    {
        return isParseHttpVersionSuccess;
    }

    char* minor = antiSound_http_isolateData(isolatedHttp, '/', '.');

    request->http->minor = atoi(minor);

    char* major = antiSound_http_isolateData(isolatedHttp, '.', '\0');

    request->http->major = atoi(major);

    if(minor[0] != '\0' && major[0] != '\0')
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
        isolatedQuereParameters = antiSound_http_isolateData(requestData, '?', ' ');
    }
    else
    {
        isolatedQuereParameters = requestData; //requestData = recurcive - char* alteradeIsolateQuareParameters (155)
    }
    
    char* quaryParameter = antiSound_http_isolateData(isolatedQuereParameters, isolatedQuereParameters[0], '&');
    
    size_t sizeOfQueryParameter = strlen(quaryParameter);

    if(quaryParameter[0] != '\0')
    {
        isParseQuareParametersSuccess = true;
    }
    
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

    char* isolatedUrl = antiSound_http_isolateData(requestData, '\n', '\r');

    char* host = antiSound_http_isolateData(isolatedUrl, ' ', ':');

    if(host[0] != '\0')
    {
        isHostExist = true;
    }

    char* alteradeIsolatedUrl = strchr(isolatedUrl, ':');
    alteradeIsolatedUrl++;

    size_t sizeOfHost = strlen(host);
    request->url->host = realloc(host, sizeOfHost);

    char* port = antiSound_http_isolateData(alteradeIsolatedUrl, ':', '\n');

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

char* antiSound_http_isolateData(char* isolatedData, int start, int end)
{
    size_t sizeOfRequestData = strlen(isolatedData);

    int i = 0;

    if(isolatedData[0] != start)
    {
        while (i < sizeOfRequestData)
        {
            if(isolatedData[i] == start)
            {
                break;
            }
            i++;
        }
        i++;
    }
    
    int j = 0;

    char* parsedData = calloc(j, sizeof(char));

    while (i < sizeOfRequestData)
    {
        if(isolatedData[i] == end)
        {
            break;
        }

        parsedData = realloc(parsedData, j + 1);
        parsedData[j] = isolatedData[i];
        j++;
        i++;
    }
    
    return parsedData;
}
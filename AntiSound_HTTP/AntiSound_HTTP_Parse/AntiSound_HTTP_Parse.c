#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"
#include "../../AntiSound_List/AntiSound_List.c"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

request_t* antiSound_http_initializeRequest()
{
    request_t* request = malloc(sizeof(request_t));
    request->method = NULL;

    request->body = antiSound_list_new();

    request->headers = antiSound_list_new();

    request->http = malloc(sizeof(httpVersion_t));
    request->http->major = -1;
    request->http->minor = -1;

    request->url = malloc(sizeof(url_t));
    request->url->host = NULL;
    request->url->port = NULL;
    request->url->path = NULL;
    request->url->anchor = NULL;

    request->url->queryParameters = antiSound_list_new();

    return request;
}

bool antiSound_http_parseMethod(request_t* request, char* requestData)
{
    bool isParsedMethodExist = false;

    char* method = antiSound_http_isolateData(requestData, requestData[0], ' ');

    size_t sizeOfMethod = strlen(method);

    request->method = realloc(method, sizeOfMethod);

    if(request->method[0] != '\0')
    {
        isParsedMethodExist = true;
    }

    return isParsedMethodExist;
}

bool antiSound_http_parseHttpVersion(request_t* request, char* requestData)
{
    bool isParsedHttpVersionExist = false;
    
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
    
    char* minor = antiSound_http_isolateData(isolatedHttp, '/', '.');

    request->http->minor = atoi(minor);

    char* major = antiSound_http_isolateData(isolatedHttp, '.', '\0');

    request->http->major = atoi(major);

    if(minor[0] != '\0' && major[0] != '\0')
    {
        isParsedHttpVersionExist = true;
    }

    return isParsedHttpVersionExist;
}

bool antiSound_http_parseQuaryParameters(request_t* request, char* requestData)
{
    bool isParseQuareParametersExist = false;

    char* isolatedQueryParameters = antiSound_http_isolateData(requestData, '?', ' ');

    isParseQuareParametersExist = antiSound_http_parseData(request->url->queryParameters, isolatedQueryParameters, '&');

    return isParseQuareParametersExist;
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

bool antiSound_http_parseHeaders(request_t* request, char* requestData)
{
    bool isParseHeadersExist = false;

    char* alteratedRequestData = NULL;

    alteratedRequestData = strchr(requestData, '\n');
    alteratedRequestData++;
    
    char* isolatedHeaders = antiSound_http_isolateData(alteratedRequestData, '\n', '\n');
    
    isParseHeadersExist = antiSound_http_parseData(request->headers, isolatedHeaders, '\n');
    
    return isParseHeadersExist;
}

bool antiSound_http_parseBody(request_t* request, char* requestData)
{
    bool isParseBodyExist = false;
    if(requestData == NULL)
    {
        return isParseBodyExist;
    }

    char* isolatedBodyParameters = antiSound_http_isolateData(requestData, '{', '}');

    isParseBodyExist = antiSound_http_parseData(request->body, isolatedBodyParameters, ',');
    
    return isParseBodyExist;
}

bool antiSound_http_parseData(list_t* list, char* isolatedData, char delimiter)
{
    bool isParseExist = false;

    if(isolatedData == NULL)
    {
        return isParseExist;
    }

    char* quaryParameter = antiSound_http_isolateData(isolatedData, isolatedData[0], delimiter);

    antiSound_list_add(list, quaryParameter);

    if(quaryParameter[0] != '\0')
    {
        isParseExist = true;
    }
    
    char* alterateIsolatedData = strchr(isolatedData, delimiter);

    if(alterateIsolatedData != NULL)
    {
        alterateIsolatedData++;
        antiSound_http_parseData(list, alterateIsolatedData, delimiter);
    }

    return isParseExist;
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

    if(start == end)
    {
        while (i < sizeOfRequestData)
        {
            if(isolatedData[i] == end && isolatedData[i + 1] == end)
            {
                break;
            }

            parsedData = realloc(parsedData, j + 1);
            parsedData[j] = isolatedData[i];
            j++;
            i++;
        }
    }
    return parsedData;
}


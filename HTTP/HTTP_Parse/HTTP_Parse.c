#include "HTTP_Parse.h"
#include "../HTTP.h"
#include "../../List/List.h"
#include "../../Item/Item.h"


#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

request_t* http_initializeRequest()
{
    request_t* request = malloc(sizeof(request_t));

    request->method = "\0";

    request->body = antiSound_list_new();

    request->headers = antiSound_list_new();

    request->http = malloc(sizeof(httpVersion_t));

    request->http->major = -1;

    request->http->minor = -1;

    request->url = malloc(sizeof(url_t));

    request->url->host = "\0";

    request->url->port = "\0";

    request->url->path = "\0";

    request->url->anchor = "\0";

    request->url->queryParameters = antiSound_list_new();

    return request;
}

bool http_parseMethod(request_t* request, char* requestData)
{
    bool isParsedMethodExist = false;

    request->method = http_isolateData(requestData, requestData[0], ' ');

    if(request->method[0] != '\0')
    {
        isParsedMethodExist = true;
    }

    return isParsedMethodExist;
}

bool http_parseHttpVersion(request_t* request, char* requestData)
{
    bool isParsedHttpVersionExist = false;
    
    char* isolatedHttp = NULL;

    char* alteradeIsolatedHttp = strchr(requestData, '/');

    isolatedHttp = http_isolateData(alteradeIsolatedHttp, ' ', '\n');
    
    char* minor = http_isolateData(isolatedHttp, '/', '.');

    request->http->minor = atoi(minor);

    char* major = http_isolateData(isolatedHttp, '.', '\0');

    request->http->major = atoi(major);

    if(minor[0] != '\0' && major[0] != '\0')
    {
        isParsedHttpVersionExist = true;
    }

    free(minor);

    free(major);

    free(isolatedHttp);

    return isParsedHttpVersionExist;
}

bool http_parseQuaryParameters(request_t* request, char* requestData)
{
    bool isParseQuareParametersExist = false;

    char* isolatedQueryParameters = http_isolateData(requestData, '?', ' ');
    
    if(isolatedQueryParameters == NULL)
    {
        isolatedQueryParameters = "id=/";
    }

    isParseQuareParametersExist = http_parseData(request->url->queryParameters, isolatedQueryParameters, '&');
    
    return isParseQuareParametersExist;
}

bool http_parseUrl(request_t* request, char* requestData)
{
    bool isParseUrlSuccess = false;

    bool isHostExist = false;

    bool isPortExist = false;

    headerParameter_t* headerParameter = http_getHeaderParamter(request, "Host");

    char* host = http_isolateData(headerParameter->name, headerParameter->name[0], ':');

    if(host[0] != '\0')
    {
        isHostExist = true;
    }

    request->url->host = host;

    char* port = http_isolateData(headerParameter->name, ':', '\n');

    if(port[0] != '\0')
    {
        isPortExist = true;
    }

    request->url->port = port;

    if(isHostExist == true && isPortExist == true)
    {
        isParseUrlSuccess = true;
    }

    return isParseUrlSuccess;
}

bool antiSound_http_parsePath(request_t* request, char* requestData)
{
    bool isParsePathExist = false;

    char start = '/';

    char* alteratedRequest = strchr(requestData, start);

    int i = 0;
    
    while(i < strlen(requestData))
    {
        if(alteratedRequest[i] == ' ' || alteratedRequest[i] == '?')
        {
            break;
        }
        i++;
    }

    char end = alteratedRequest[i];

    request->path = http_isolateData(requestData, start, end);;

    return isParsePathExist;
}


bool http_parseHeaders(request_t* request, char* requestData)
{
    bool isParseHeadersExist = false;

    char* isolatedHeaders = http_isolateData(requestData, '\n', '\n');
    
    isParseHeadersExist = http_parseData(request->headers, isolatedHeaders, '\n');
    
    free(isolatedHeaders);

    return isParseHeadersExist;
}

bool http_parseBody(request_t* request, char* requestData)
{
    bool isParseBodyExist = false;

    if(requestData == NULL)
    {
        return isParseBodyExist;
    }
    
    char* isolatedBodyParameters = http_isolateData(requestData, '{', '\0');
    
    if(isolatedBodyParameters == NULL)
    {
        return isParseBodyExist;
    }
    
    int i = 0;

    int j = 0;

    char buffer[1000] = "\0";

    while (i < strlen(isolatedBodyParameters))
    {
        if(isolatedBodyParameters[i] != '\"' && isolatedBodyParameters[i] != '{' && isolatedBodyParameters[i] != '}' && isolatedBodyParameters[i] != ' ')
        {
            buffer[j] = isolatedBodyParameters[i];
            j++;
        }
        i++;
    }

    char* alteratedBodyParameter = calloc(strlen(buffer) + 1, sizeof(char));

    strncpy(alteratedBodyParameter, buffer, strlen(buffer));

    isParseBodyExist = http_parseData(request->body, alteratedBodyParameter, ',');
    
    free(alteratedBodyParameter);

    free(isolatedBodyParameters);

    return isParseBodyExist;
}

bool http_parseData(list_t* list, char* isolatedData, char delimiter)
{
    bool isParseExist = false;

    if(isolatedData == NULL || isolatedData[0] == '\0')
    {
        return isParseExist;
    }

    void* structure = NULL;

    char* parameter = http_isolateData(isolatedData, isolatedData[0], delimiter);

    if(delimiter == '&')
    {
        queryParameter_t* queryParameter = http_initializeQueryParameter();

        queryParameter->id = http_isolateData(parameter, parameter[0], '=');

        queryParameter->name = http_isolateData(parameter, '=', '\0');
        
        structure = queryParameter;
    }

    if(delimiter == '\n')
    {
        headerParameter_t* headerParameter = http_initializeHeaderParameter();
   
        headerParameter->id = http_isolateData(parameter, parameter[0], ':');

        headerParameter->name = http_isolateData(parameter, ' ', '\0');

        structure = headerParameter;
    }

    if(delimiter == ',')
    {
        body_t* body = http_initializeBody();

        body->id = http_isolateData(parameter, parameter[0], ':');

        body->name = http_isolateData(parameter, ':', '\0');

        structure = body;
    }

    antiSound_list_add(list, structure);

    if(parameter[0] != '\0')
    {
        isParseExist = true;
    }
    
    char* alterateIsolatedData = strchr(isolatedData, delimiter);

    if(alterateIsolatedData != NULL)
    {
        alterateIsolatedData++;

        http_parseData(list, alterateIsolatedData, delimiter);
    }

    free(parameter);

    return isParseExist;
}

char* http_isolateData(char* isolatedData, char start, char end)
{
    size_t sizeOfIsolatedData = strlen(isolatedData);

    int i = 0;

    if(isolatedData[0] != start)
    {
        while (i < sizeOfIsolatedData)
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

    char buffer[1000] = "\0";

    while (i < sizeOfIsolatedData)
    {
        if(isolatedData[i] == end)
        {
            break;
        }

        buffer[j] = isolatedData[i];

        j++;

        i++;
    }

    if(start == end)
    {
        while (i < sizeOfIsolatedData)
        {
            if(isolatedData[i] == '\n' && isolatedData[i + 1] == '\n')
            {
                break;
            }

            buffer[j] = isolatedData[i];
            j++;
            i++;
        }
    }

    char* data = calloc(strlen(buffer) + 10, sizeof(char));
    
    strncpy(data, buffer, strlen(buffer));

    if(data[0] == '\0')
    {
        return NULL;
    }

    return data;
}


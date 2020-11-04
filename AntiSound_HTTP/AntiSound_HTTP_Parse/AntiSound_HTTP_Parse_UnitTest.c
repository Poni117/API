#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    antiSound_http_testInitializeRequest();

    char* requestData = 
    "PUT /?id=0&name=Slava HTTP/1.1\n"
    "Host: 127.0.0.1:8090\n"
    "User-Agent: curl/7.68.0\n"
    "Accept: */*\n"
    "Content-Type: application/json\n"
    "\n";

    request_t* request = antiSound_http_initializeRequest();
    
    antiSound_http_testParseMethod(request, requestData);
    antiSound_http_testParseHttpVersion(request, requestData);
    antiSound_http_testParseQueryParameters(request, requestData);
    antiSound_http_testParseUrl(request, requestData);
    antiSound_http_testParseHeaders(request, requestData);
}

//===============================================================================================================================
void antiSound_http_testInitializeRequest()
{
    bool status = false;
//--------------------------------------------------------------------------------------------------------------------------------
    request_t* request = antiSound_http_initializeRequest();
    
    if(request->method == NULL && request->url->host == NULL && request->url->queryParameters->data == NULL && request->headers->data == NULL)
    {
        status = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(status == false)
    {
        printf("< antiSound_http_testInitializeRequest >\n");
        printf("status[%d]\n", status);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseMethod(request_t* request, char* requestData)
{
    bool isParseMethodSuccess = false;

    bool isMethodExist = false;
//--------------------------------------------------------------------------------------------------------------------------------
    isParseMethodSuccess = antiSound_http_parseMethod(request, requestData);
    
    char* method = request->method;

    if(strcmp(method, "POST") == 0 || strcmp(method, "GET") == 0 || strcmp(method, "PUT") == 0 || strcmp(method, "DELETE") == 0)
    {
        isMethodExist = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseMethodSuccess == false || isMethodExist == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseMethod >\n\n");
        printf("isParseMethodSuccess[%d]\n", isParseMethodSuccess);
        printf("isMethodExist[%d]\n", isMethodExist);
        printf("-------------------------\n");
    }
}

void antiSound_http_testParseHttpVersion(request_t* request, char* requestData)
{
    bool isParseHttpVersionSuccess = false;

    bool isMethodGetHttpParsed = false;
//--------------------------------------------------------------------------------------------------------------------------------
    isMethodGetHttpParsed = antiSound_http_parseHttpVersion(request, requestData);

    if(isMethodGetHttpParsed == true)
    {
        isParseHttpVersionSuccess = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseHttpVersionSuccess != true)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHttpVersion >\n\n");
        printf("isParseHttpVersionSuccess[%d]\n", isParseHttpVersionSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseQueryParameters(request_t* request, char* requestData)
{
    bool isParseQueryParametersSuccess = false;

    bool isPrarametersCorrect = true;
    bool isParseQueryParametersExist = false;

//--------------------------------------------------------------------------------------------------------------------------------
    char* arrayOfQueryParameters[] = 
    {
    "id=0",
    "name=Dmitry",
    "lastname=Ivanov",
    "nickname=Poni117"
    };

//--------------------------------------------------------------------------------------------------------------------------------
    list_t* pointer = request->url->queryParameters->next;

    while (pointer != NULL)
    {
        if(strcmp(pointer->data, arrayOfQueryParameters[pointer->id]) != 0)
        {
            isPrarametersCorrect = false;
        }
        pointer = pointer->next;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    isParseQueryParametersExist = antiSound_http_parseQuaryParameters(request, requestData);
    
    if(isParseQueryParametersExist == true && isPrarametersCorrect == true)
    {
        isParseQueryParametersSuccess = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseQueryParametersSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseQueryParameters >\n\n");
        printf("isParseQueryParametersSuccess[%d]\n", isParseQueryParametersSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseUrl(request_t* request, char* requestData)
{
    bool isParseUrlSuccess = false;

    bool isParseUrlExist = false;
    bool isHostCorrect = false;
    bool isPortCorrect = false;
//--------------------------------------------------------------------------------------------------------------------------------
    char* host = "127.0.0.1";
    char* port = "8090";
//--------------------------------------------------------------------------------------------------------------------------------
    isParseUrlExist = antiSound_http_parseUrl(request, requestData);

    if(strcmp(request->url->host, host) == 0)
    {
        isHostCorrect = true;
    }


    if(strcmp(request->url->port, port) == 0)
    {
        isPortCorrect = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseUrlExist == true && isHostCorrect == true && isPortCorrect == true)
    {
        isParseUrlSuccess = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if (isParseUrlSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseUrl >\n\n");
        printf("isParseUrlSuccess[%d]\n", isParseUrlSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================

void antiSound_http_testIsolateData(char* requestData)
{
    bool isIsolatesSuccess = false;

    bool isMethodIsolated = false;
    bool isHttpIsolated = false;
    bool isUrlIsolated = false;
    bool isQueryParametersIsolated = false;
//--------------------------------------------------------------------------------------------------------------------------------
    char* method = "PUT";
    char* http = "HTTP/1.1";
    char* queryParameters = "id=0&name=Slava";
    char* url = "Host: 127.0.0.1:8090";
    
//--------------------------------------------------------------------------------------------------------------------------------
    char* isoltedMethod = antiSound_http_isolateData(requestData, requestData[0], ' ');

    if(strcmp(method, isoltedMethod) == 0)
    {
        isMethodIsolated = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    char* isolatedQueryParameters = antiSound_http_isolateData(requestData, '?', ' ');

    if(strcmp(queryParameters, isolatedQueryParameters) == 0)
    {
        isQueryParametersIsolated = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
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

    if(strcmp(http, isolatedHttp) == 0)
    {
        isHttpIsolated = true;
    }

//--------------------------------------------------------------------------------------------------------------------------------
    char* isolatedUrl = antiSound_http_isolateData(requestData, '\n', '\r');

    if(strcmp(url, isolatedUrl) == 0)
    {
        isUrlIsolated = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if (isMethodIsolated == true && isHttpIsolated == true && isUrlIsolated == true && isQueryParametersIsolated == true)
    {
        isIsolatesSuccess = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if (isIsolatesSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testIsolateData >\n\n");
        printf("isIsolatesSuccess[%d]\n", isIsolatesSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================

void antiSound_http_testParseHeaders(request_t* request, char* requestData)
{
    bool isParseHeadersSuccess = false;

    bool isParseHeadersExist = false;
    bool isHeadersListCorrect = true;

//--------------------------------------------------------------------------------------------------------------------------------
    char* arrayOfHeaders[] = 
    {
    "User-Agent: curl/7.68.0",
    "Accept: */*",
    "Content-Type: application/json",
    };
//--------------------------------------------------------------------------------------------------------------------------------
    isParseHeadersExist = antiSound_http_parseHeaders(request, requestData);

    list_t* pointer = request->headers->next;

    while (pointer != NULL)
    {
        if(strcmp(pointer->data, arrayOfHeaders[pointer->id]) != 0)
        {
            isHeadersListCorrect = false;
        }
        pointer = pointer->next;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseHeadersExist == true && isHeadersListCorrect == true)
    {
        isParseHeadersSuccess = true;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    if(isParseHeadersSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHeaders >\n\n");
        printf("isParseHeadersSuccess[%d]\n", isParseHeadersSuccess);
        printf("-------------------------\n");
    }
}
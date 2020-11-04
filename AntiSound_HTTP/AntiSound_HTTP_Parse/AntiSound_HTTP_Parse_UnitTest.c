#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    antiSound_http_testInitializeRequest();

    request_t* request = antiSound_http_initializeRequest();
    
    antiSound_http_testParseMethod(request);
    antiSound_http_testParseHttpVersion(request);
    antiSound_http_testParseQueryParameters(request);
    antiSound_http_testParseUrl(request);
}

void antiSound_http_testInitializeRequest()
{
    bool status = false;

    request_t* request = antiSound_http_initializeRequest();
    
    if(request->method == NULL && request->url->host == NULL && request->url->queryParameters->data == NULL && request->headers->data == NULL)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_http_testInitializeRequest >\n");
        printf("status[%d]\n", status);
        printf("-------------------------\n");
    }
}
void antiSound_http_testParseMethod(request_t* request)
{
    bool isParseMethodSuccess = false;

    bool isMethodExist = false;
    
    char* getRequestData = "GET /";

    isParseMethodSuccess = antiSound_http_parseMethod(request, getRequestData);;

    char* method = request->method;

    if(strcmp(method, "POST") == 0 || strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0 || strcmp(method, "DELETE") == 0)
    {
        isMethodExist = true;
    }

    if(isParseMethodSuccess == false || isMethodExist == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseMethod >\n\n");
        printf("isParseMethodSuccess[%d]\n", isParseMethodSuccess);
        printf("isMethodExist[%d]\n", isMethodExist);
        printf("-------------------------\n");
    }
}

void antiSound_http_testParseHttpVersion(request_t* request)
{
    bool isParseHttpVersionSuccess = false;

    bool isMethodGetHttpParsed = false;

    char* httpRequestData = 
    "/ HTTP/1.1\n";

    isMethodGetHttpParsed = antiSound_http_parseHttpVersion(request, httpRequestData);

    if(isMethodGetHttpParsed == true)
    {
        isParseHttpVersionSuccess = true;
    }

    if(isParseHttpVersionSuccess != true)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHttpVersion >\n\n");
        printf("isParseHttpVersionSuccess[%d]\n", isParseHttpVersionSuccess);
        printf("-------------------------\n");
    }
}

void antiSound_http_testParseQueryParameters(request_t* request)
{
    bool isPrarametersCorrect = true;
    bool isParseQueryParametersExist = false;
    bool isParseQueryParametersSuccess = false;

    char* arrayOfQueryParameters[] = 
    {
    "id=0",
    "name=Dmitry",
    "lastname=Ivanov",
    "nickname=Poni117"
    };

    char* queryParameters = "/?id=0&name=Dmitry&lastname=Ivanov&nickname=Poni117 ";

    isParseQueryParametersExist = antiSound_http_parseQuaryParameters(request, queryParameters);


    list_t* pointer = request->url->queryParameters->next;

    while (pointer != NULL)
    {
        if(strcmp(pointer->data, arrayOfQueryParameters[pointer->id]) != 0)
        {
            isPrarametersCorrect = false;
        }
        pointer = pointer->next;
    }

    
    if(isParseQueryParametersExist == true && isPrarametersCorrect == true)
    {
        isParseQueryParametersSuccess = true;
    }

    if(isParseQueryParametersSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseQueryParameters >\n\n");
        printf("isParseQueryParametersSuccess[%d]\n", isParseQueryParametersSuccess);
        printf("-------------------------\n");
    }
}

void antiSound_http_testParseUrl(request_t* request)
{
    bool isParseUrlSuccess = false;
    bool isParseUrlExist = false;
    bool isHostCorrect = false;
    bool isPortCorrect = false;
    
    char* host = "127.0.0.1";
    char* port = "8090";

    char* url = "\nHost: 127.0.0.1:8090\n";

    isParseUrlExist = antiSound_http_parseUrl(request, url);

    if(strcmp(request->url->host, host) == 0)
    {
        isHostCorrect = true;
    }

    if(strcmp(request->url->port, port) == 0)
    {
        isPortCorrect = true;
    }

    if(isParseUrlExist == true && isHostCorrect == true && isPortCorrect == true)
    {
        isParseUrlSuccess = true;
    }

    if (isParseUrlSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseUrl >\n\n");
        printf("isParseUrlSuccess[%d]\n", isParseUrlSuccess);
        printf("-------------------------\n");
    }
}

void antiSound_http_testParseData()
{
}
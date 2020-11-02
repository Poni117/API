#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    request_t* request = malloc(sizeof(request_t));

    antiSound_http_testParseMethod(request);
    antiSound_http_testParseHttpVersion(request);
}

void antiSound_http_testParseMethod(request_t* request)
{
    bool isParseMethodSuccess = false;

    bool isMethodExist = false;
    
    bool isMethodGetParsed = false;
    bool isMethodPutParsed = false;
    bool isMethodPostParsed = false;
    bool isMethodDeleteParsed = false;

    char* getRequestData = 
    "GET /\n";

    isMethodGetParsed = antiSound_http_parseMethod(request, getRequestData);

    if(isMethodGetParsed == true && isMethodPutParsed == true && isMethodPostParsed == true && isMethodDeleteParsed == true)
    {
        isParseMethodSuccess = true;
    }

    char* method = request->method;

    if(strcmp(method, "POST") == 0)
    {
        isMethodExist = true;
    }

    if(strcmp(method, "GET") == 0)
    {
        isMethodExist = true;
    }

    if(strcmp(method, "POST") == 0)
    {
        isMethodExist = true;
    }

    if(strcmp(method, "DELETE") == 0)
    {
        isMethodExist = true;
    }

    if(isParseMethodSuccess != true && isMethodExist != true)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseMethod >\n\n");
        printf("isParseMethodSuccess[%d]\n", isParseMethodSuccess);
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
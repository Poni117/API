#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    antiSound_http_testParseMethod();
    antiSound_http_testParseHttpVersion();
}

void antiSound_http_testParseMethod()
{
    bool isParseMethodSuccess = false;
    bool isMethodExist = false;

    char* requestData = "NULL / HTTP/1.1\n";

    request_t* request = malloc(sizeof(request_t));

    isParseMethodSuccess = antiSound_http_parseMethod(request, requestData);

    if(isParseMethodSuccess == false)
    {
        return;
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

void antiSound_http_testParseHttpVersion()
{
    bool isParseHttpVersionSuccess = false;

    char* requestData = "NULL / HTTP/1.1\n";

    request_t* request = malloc(sizeof(request_t));

    isParseHttpVersionSuccess = antiSound_http_parseHttpVersion(request, requestData);

    if(isParseHttpVersionSuccess != true)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHttpVersion >\n\n");
        printf("isParseHttpVersionSuccess[%d]\n", isParseHttpVersionSuccess);
        printf("-------------------------\n");
    }
}
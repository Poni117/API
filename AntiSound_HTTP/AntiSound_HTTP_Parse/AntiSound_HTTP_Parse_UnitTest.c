#include "AntiSound_HTTP_Parse.h"
#include "../AntiSound_HTTP.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    request_t* request = antiSound_http_initializeRequest();

    antiSound_http_testParseMethod(request);
    antiSound_http_testParseHttpVersion(request);
    antiSound_http_testParseQueryParameters(request);
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

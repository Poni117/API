#ifndef ANTISOUND_HTTP_H
#define ANTISOUND_HTTP_H

#include "../AntiSound_List/AntiSound_List.h"
#include <stdbool.h>


typedef struct HttpVersion
{
    int minor;
    int major;
}httpVersion_t;

typedef struct Url
{
    char* host;
    char* port;
    char* path;
    list_t* queryParameters;
    char* anchor;
}url_t;

typedef struct Request
{
    char* method;
    char* path;
    httpVersion_t* http;
    url_t* url;
    list_t* headers;
    list_t* body;
}request_t;

typedef struct QueryParameter
{
    char* id;
    char* name;
}queryParameter_t;

typedef struct BodyParameter
{
    char* id;
    char* name;
}body_t;

typedef struct HeaderParameter
{
    char* id;
    char* name; 
}headerParameter_t;

typedef struct Response
{
    char* httpVersion;
    char* status;
    char* contentType;
    char* contentLength;
    char* body;
    char* response;
}response_t;


request_t* antiSound_http_parseRuqest(char* request);

headerParameter_t* antiSound_http_getHeaderParamter(request_t* request, char* soughtItem);

body_t* antiSound_http_getBodyParamter(request_t* request, char* soughtItem);

queryParameter_t* antiSound_http_getQueryParamter(request_t* request, char* soughtItem);

bool antiSound_http_checkExistingId(request_t* request, list_t* taskList);

bool antiSound_http_checkParameters(request_t* request,  list_t* taskList, response_t* response);
//==============================================================================================

bool antiSound_http_testGetQueryParamter(request_t* request, char* soughtItem);

bool antiSound_http_testGetHeaderParamter(request_t* request, char* id);

bool antiSound_http_testGetBodyParamter(request_t* request, char* soughtItem);


#endif // ANTISOUND_HTTP_H
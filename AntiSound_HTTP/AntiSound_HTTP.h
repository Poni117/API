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
    char* name;
    char* value; 
}headerParameter_t;

typedef struct Task
{
    char* id;
    char* name;
}task_t;

typedef struct Response
{
   char* status; 
}response_t;

request_t* antiSound_http_parseRuqest(char* request);

#endif // ANTISOUND_HTTP_H
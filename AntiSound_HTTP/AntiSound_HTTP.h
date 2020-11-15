#ifndef ANTISOUND_HTTP_H
#define ANTISOUND_HTTP_H

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
    httpVersion_t* http;
    url_t* url;
    list_t* headers;
    list_t* body;
}request_t;

typedef struct QueryParameter
{
    char* name;
    char* value;
}queryParameter_t;

typedef struct BodyParameter
{
    char* name;
    char* value;
}body_t;

typedef struct HeaderParameter
{
    char* name;
    char* value; 
}headerParameter_t;

typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);

#endif // ANTISOUND_HTTP_H
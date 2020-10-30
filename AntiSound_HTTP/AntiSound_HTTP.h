#include <stdbool.h>

typedef struct Request
{
    char* method;
    http_t* http;
    url_t* url;
}request_t;

typedef struct HttpVersion
{
    int minor;
    int major;
}httpVersion_t;

typedef Url
{
    char* host;
    char* port;
    char* path;
    char* queryParametrs;
    char* anchor;
}url_t;

typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);



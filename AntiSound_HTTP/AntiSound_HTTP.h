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
    list_t* list;
    char* anchor;

}url_t;

typedef struct Request
{
    char* method;
    httpVersion_t* http;
    url_t* url;
}request_t;

typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);



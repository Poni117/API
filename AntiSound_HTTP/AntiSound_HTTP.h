#include <stdbool.h>

typedef struct Request
{
    char* method;
    http_t* http;
}request_t;

typedef struct HTTP
{
    int minor;
    int major;
}http_t;

typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);



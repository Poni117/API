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
    char* queryParameters;
    char* anchor;
}url_t;

typedef struct Parameters
{
    char* parametr;
    struct Parameters* next;
}parameters_t;

typedef struct Request
{
    char* method;
    httpVersion_t* http;
    url_t* url;
    parameters_t parameters;
}request_t;



typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);



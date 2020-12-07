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
}bodyParameter_t;

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

/*
 * parses request to struct and returns pointer to request_t
 */
request_t* antiSound_http_parseRuqest(char* request);

/*
 * finds header parameter from request and returns pointer to headerParameter_t
 */
headerParameter_t* antiSound_http_getHeaderParamter(request_t* request, char* soughtItem);

/*
 * finds body parameter from request and returns pointer to bodyParameter_t
 */
bodyParameter_t* antiSound_http_getBodyParamter(request_t* request, char* soughtItem);

/*
 * finds query parameter from request and returns pointer to queryParameter_t
 */
queryParameter_t* antiSound_http_getQueryParamter(request_t* request, char* soughtItem);

/*
 * check exisiting id in taskList from request
 * returns true in case if id exist, otherwise false
 */
bool antiSound_http_checkExistingId(request_t* request, list_t* taskList);

/*
 * check parameters for correctness
 * returns true in case parameters correct, otherwise false
 */
bool antiSound_http_checkParameters(request_t* request,  list_t* taskList, response_t* response);

//==============================================================================================

/*
 * test of antiSound_http_getQueryParamter
 * returns true in case test true, otherwise false
 */
bool antiSound_http_testGetQueryParamter(request_t* request, char* soughtItem);

/*
 * test of antiSound_http_getHeaderParamter
 * returns true in case test true, otherwise false
 */
bool antiSound_http_testGetHeaderParamter(request_t* request, char* id);

/*
 * test of antiSound_http_getBodyParamter
 * returns true in case test true, otherwise false
 */
bool antiSound_http_testGetBodyParamter(request_t* request, char* soughtItem);


#endif // ANTISOUND_HTTP_H
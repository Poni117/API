#ifndef ANTISOUND_HTTP_H
#define ANTISOUND_HTTP_H

#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
#include "../AntiSound_FIFO/AntiSound_FIFO.h"

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

typedef struct Task
{
    void* id;
    void* name;
    void* lastname;
}task_t;

typedef struct Response
{
    char* httpVersion;
    char* status;
    char* contentType;
    char* contentLength;
    char* body;
    char* response;
}response_t;

typedef struct Messeges
{
    int key;
    char* message;
}messege_t;

typedef struct Datas
{
    request_t* request;
    binaryTree_t* root;
    response_t* response;
}datas_t;

/*
 * initializes struct of task
 * returns pointer to task_t
 */
task_t* antiSound_http_initializeTask();

/*
 * initializes struct of Datas
 * returns pointer to datas_t
 */
datas_t* antiSound_http_initializeDatas();

/*
 * initializes struct of Message
 * returns pointer to messege_t
 */
messege_t* antiSound_http_initializeMesseges();

/*
 * initializes struct of QueryParameter
 * returns pointer to queryParameter_t
 */
queryParameter_t* antiSound_http_initializeQueryParameter();

/*
 * initializes struct of HeaderParameter
 * returns pointer to headerParameter_t
 */
headerParameter_t* antiSound_http_initializeHeaderParameter();

/*
 * initializes struct of body
 * returns pointer to body_t
 */
body_t* antiSound_http_initializeBody();

/*
 * parses request to struct and returns pointer to request_t
 */
request_t* antiSound_http_parseRuqest(char* request);

/*
 * finds header parameter from request and returns pointer to headerParameter_t
 */
headerParameter_t* antiSound_http_getHeaderParamter(request_t* request, char* soughtItem);

/*
 * finds body parameter from request and returns pointer to body_t
 */
body_t* antiSound_http_getBodyParamter(request_t* request, char* soughtItem);

/*
 * finds query parameter from request and returns pointer to queryParameter_t
 */
queryParameter_t* antiSound_http_getQueryParamter(request_t* request, char* soughtItem);

/*
 * check exisiting id in taskList from request
 * returns true in case if id exist, otherwise false
 */
bool antiSound_http_checkExistingItem(request_t* request, binaryTree_t* root);

/*
 * check parameters for correctness
 * returns true in case parameters correct, otherwise false
 */
bool antiSound_http_checkParameters(request_t* request, response_t* response, binaryTree_t* root);

/*
 * frees struct request_t
 */
void antiSound_http_freeRequest(void* data);

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


/*
 * test of antiSound_http_getBodyParamters
 * returns true in case test true, otherwise false
 */
bool antiSound_http_isBodyParametersExist(request_t* request);

#endif // ANTISOUND_HTTP_H
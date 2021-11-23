#ifndef ANTISOUND_HTTP_PARSE_H
#define ANTISOUND_HTTP_PARSE_H

#include "../HTTP.h"

#include <stdbool.h>

/*
 *  initializes struct Request and returns pointer to request_t
 */
request_t* http_initializeRequest();

/*
 *  parses method from requestData and returns true if parse success, otherwise return false
 */
bool http_parseMethod(request_t* request, char* requestData);

/*
 *  parses tasks from requestData and returns true if parse success, otherwise return false
 */
bool antiSound_http_parsePath(request_t* request, char* requestData);

/*
 *  parses http from requestData and returns true if parse success, otherwise returns false
 */
bool http_parseHttpVersion(request_t* request, char* requestData);

/*
 * parses query parameters from requestData and returns true if parse success, otherwise returns false
 */
bool http_parseQuaryParameters(request_t* request, char* requestData);

/*
 * parses url from requestData and returns true if parse success, otherwise returns false
 */
bool http_parseUrl(request_t* request, char* requestData);

/*
 * parses headers from requestData and returns true if parse success, otherwise return false
 */
bool http_parseHeaders(request_t* request, char* requestData);

/*
 * parses body from requestData and returns true if parse success, otherwise returns false
 */
bool http_parseBody(request_t* request, char* requestData);

/*
 * parses Parameters from isolatedData and returns true if parse success, otherwise returns false
 */
bool http_parseData(list_t* list, char* isolatedData, char delimiter);

/*
 * isolates data from isolatedData and returns isolated data
 */
char* http_isolateData(char* isolatedData, char start, char end);


//======================================================================================================================================

/*
 *  tests of antiSound_http_initializeRequest
 */
void http_testInitializeRequest();

/*
 *  tests of antiSound_http_parseMethod
 */
void http_testParseMethod(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parsePath
 */
void http_testParsePath(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseHttpVersion
 */
void http_testParseHttpVersion(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseQuaryParameters
 */
void http_testParseQueryParameters(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseUrl
 */
void http_testParseUrl(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseHeaders
 */
void http_testParseHeaders(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseBody
 */
void http_testParseBody(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_isolatedData
 */
void http_testIsolateData(char* requestData);



#endif // ANTISOUND_HTTP_PARSE_H

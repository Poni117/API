#ifndef ANTISOUND_HTTP_PARSE_H
#define ANTISOUND_HTTP_PARSE_H

#include "../AntiSound_HTTP.h"
#include "../../AntiSound_List/AntiSound_List.h"

#include <stdbool.h>


/*
 *  initializes struct Request and returns pointer to request_t
 */
request_t* antiSound_http_initializeRequest();

/*
 *  parses method from requestData and returns true if parse success, otherwise return false
 */
bool antiSound_http_parseMethod(request_t* request, char* requestData);

/*
 *  parses http from requestData and returns true if parse success, otherwise returns false
 */
bool antiSound_http_parseHttpVersion(request_t* request, char* requestData);

/*
 * parses query parameters from requestData and returns true if parse success, otherwise returns false
 */
bool antiSound_http_parseQuaryParameters(request_t* request, char* requestData);

/*
 * parses url from requestData and returns true if parse success, otherwise returns false
 */
bool antiSound_http_parseUrl(request_t* request, char* requestData);

/*
 * parses headers from requestData and returns true if parse success, otherwise return false
 */
bool antiSound_http_parseHeaders(request_t* request, char* requestData);

/*
 * parses body from requestData and returns true if parse success, otherwise returns false
 */
bool antiSound_http_parseBody(request_t* request, char* requestData);

/*
 * parses Parameters from isolatedData and returns true if parse success, otherwise returns false
 */
bool antiSound_http_parseData(list_t* list, char* isolatedData, char delimiter);

/*
 * isolates data from isolatedData and returns isolated data
 */
char* antiSound_http_isolateData(char* isolatedData, int start, int end);


//======================================================================================================================================

/*
 *  tests of antiSound_http_initializeRequest
 */
void antiSound_http_testInitializeRequest();

/*
 *  tests of antiSound_http_parseMethod
 */
void antiSound_http_testParseMethod(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseHttpVersion
 */
void antiSound_http_testParseHttpVersion(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseQuaryParameters
 */
void antiSound_http_testParseQueryParameters(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseUrl
 */
void antiSound_http_testParseUrl(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseHeaders
 */
void antiSound_http_testParseHeaders(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_parseBody
 */
void antiSound_http_testParseBody(request_t* request, char* requestData);

/*
 *  tests of antiSound_http_isolatedData
 */
void antiSound_http_testIsolatedData(char* requestData);



#endif // ANTISOUND_HTTP_PARSE_H
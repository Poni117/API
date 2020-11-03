#ifndef ANTISOUND_HTTP_PARSE_H
#define ANTISOUND_HTTP_PARSE_H

#include "../AntiSound_HTTP.h"
#include <stdbool.h>


/*
 *  initialize struct Request and return pointer to request_t
 */
request_t* antiSound_http_initializeRequest();

/*
 *  parse method from requestData and return true if parse success, otherwise return false
 */
bool antiSound_http_parseMethod(request_t* request, char* requestData);

/*
 *  parse http from requestData and return true if parse success, otherwise return false
 */
bool antiSound_http_parseHttpVersion(request_t* request, char* requestData);

/*
 * parse query parameters from requestData and return true if parse success, otherwise return false
 */
bool antiSound_http_parseQuaryParameters(request_t* request, char* requestData);


void antiSound_http_testInitializeRequest();
/*
 *  test of antiSound_http_parseHttpVersion
 */
void antiSound_http_testParseMethod(request_t* request);

/*
 *  testParseHttpVersion
 */
void antiSound_http_testParseHttpVersion(request_t* request);

void antiSound_http_testParseQueryParameters(request_t* request);

#endif // ANTISOUND_HTTP_PARSE_H
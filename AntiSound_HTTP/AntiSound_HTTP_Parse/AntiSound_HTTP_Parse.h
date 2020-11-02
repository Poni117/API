#ifndef ANTISOUND_HTTP_PARSE_H
#define ANTISOUND_HTTP_PARSE_H

#include "../AntiSound_HTTP.h"
#include <stdbool.h>

/*
 *  parse method from requestData and return true if parse success, otherwise return false;
 */
bool antiSound_http_parseMethod(request_t* request, char* requestData);

bool antiSound_http_parseHttpVersion(request_t* request, char* requestData);

void antiSound_http_testParseMethod();

void antiSound_http_testParseHttpVersion();



#endif // ANTISOUND_HTTP_PARSE_H
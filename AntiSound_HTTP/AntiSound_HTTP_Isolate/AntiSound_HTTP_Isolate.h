#ifndef ANTISOUND_HTTP_ISOLATE_H
#define ANTISOUND_HTTP_ISOLATE_H

#include "../AntiSound_HTTP.h"

/*
 * Isolate http reqest from requestData and return isolated http
 */
char* antiSound_http_isolateHttp(request_t* request, char* requestData);

/*
 * Isolate quary parameters from requestData and return isolated quary parameters
 */
char* antiSound_http_isolsteQuaryParameters(char* requestData);

#endif // ANTISOUND_HTTP_ISOLATE_H
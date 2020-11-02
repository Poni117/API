#ifndef ANTISOUND_HTTP_ISOLATE_H
#define ANTISOUND_HTTP_ISOLATE_H

#include "../AntiSound_HTTP.h"
/*
 * Isolate http reqest from requestData and return isolated http
 */
char* antiSound_http_isolateHttp(request_t* request, char* requestData);

#endif // ANTISOUND_HTTP_ISOLATE_H
#include "AntiSound_HTTP.h"

request_t* antiSound_http_parseRuqest(char* request)
{
    request_t* structOfrequest = malloc(sizeof(structOfrequest));
    structOfrequest->_parametrs->request = request;

    _antiSound_http_isolateParametrs(structOfrequest);
    _antiSound_http_isolateParametrId(structOfrequest);
    _antiSound_http_isolateParametrName(structOfrequest);

    _antiSound_http_parseMethod(structOfrequest);
    _antiSound_http_parseId(structOfrequest);
    _antiSound_http_parseName(structOfrequest);

    return structOfrequest;
    
}
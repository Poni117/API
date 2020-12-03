#include "AntiSound_HTTP.h"
#include "AntiSound_HTTP_Parse/AntiSound_HTTP_Parse.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

request_t* antiSound_http_parseRuqest(char* requestData)
{
   request_t* request = antiSound_http_initializeRequest();

   antiSound_http_testParseMethod(request, requestData);
   antiSound_http_testParseHttpVersion(request, requestData);
   antiSound_http_testParseUrl(request, requestData);
   antiSound_http_testParseHeaders(request, requestData);
   antiSound_http_parsePath(request, requestData);
   antiSound_http_testParseQueryParameters(request, requestData);

   if(strcmp(request->method, "POST") == 0)
   {
      antiSound_http_testParseBody(request, requestData);
   }
   
   if(strcmp(request->method, "PUT") == 0)
   {
      antiSound_http_testParseBody(request, requestData);
   }
   
   if(strcmp(request->method, "DELETE") == 0)
   {
      antiSound_http_testParseQueryParameters(request, requestData);
   }

   return request;
}


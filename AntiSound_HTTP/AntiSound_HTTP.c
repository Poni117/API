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

item_t* antiSound_http_initializeItem()
{
   item_t* item = malloc(sizeof(item_t));
   item->id = -1;
   item->data = NULL;

   return item;
}

queryParameter_t* antiSound_http_getQueryParamter(request_t* request, char* soughtItem)
{
   list_t* pointer = request->url->queryParameters;

   if(pointer->id == -1)
   {
      pointer = pointer->next;
   }

   while (pointer != NULL)
   {
      queryParameter_t* queryParameter = pointer->data;

      if(strcmp(queryParameter->id, soughtItem) == 0)
      {
         return queryParameter;
      }

      pointer = pointer->next;
   }
   
   return NULL;
}
item_t* antiSound_http_getItem(list_t* list, int id)
{
   list_t* pointer = list;

   if(pointer->id == -1)
   {
      pointer = pointer->next;
   }

   while(pointer != NULL)
   {
      item_t* item = pointer->data;

      if(item->id == id)
      {
         break;
      }
      pointer = pointer->next;
   }
   
   return pointer->data;
}

headerParameter_t* antiSound_http_getHeaderParamter(request_t* request, char* id)
{
   list_t* pointer = request->headers;

   if(pointer->id == -1)
   {
      pointer = pointer->next;
   }

   while (pointer != NULL)
   {
      headerParameter_t* headerParameter = pointer->data;

      if(strcmp(headerParameter->id, id) == 0)
      {
         return headerParameter;
      }

      pointer = pointer->next;
   }
   
   return NULL;
}

body_t* antiSound_http_getBodyParamter(request_t* request, char* soughtItem)
{
   list_t* pointer = request->body;

   if(pointer->id == -1)
   {
      pointer = pointer->next;
   }

   while (pointer != NULL)
   {
      body_t* body = pointer->data;

      if(strcmp(body->id, soughtItem) == 0)
      {
         return body;
      }

      pointer = pointer->next;
   }
   
   return NULL;
}
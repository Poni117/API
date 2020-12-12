#include "AntiSound_HTTP.h"
#include "AntiSound_HTTP_Parse/AntiSound_HTTP_Parse.h"
#include "../AntiSound_Item/AntiSound_Item.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

request_t* antiSound_http_parseRuqest(char* requestData)
{
   request_t* request = antiSound_http_initializeRequest();

   antiSound_http_testParseMethod(request, requestData);
   antiSound_http_testParseHttpVersion(request, requestData);
   antiSound_http_testParseHeaders(request, requestData);
   antiSound_http_testParseUrl(request, requestData);
   antiSound_http_parsePath(request, requestData);
   antiSound_http_testParseQueryParameters(request, requestData);

   if(strcmp(request->method, "POST") == 0 || strcmp(request->method, "PUT") == 0)
   {
      antiSound_http_testParseBody(request, requestData);
   }

   return request;
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

bool antiSound_http_checkParameters(request_t* request, list_t* taskList, response_t* response)
{
   bool isParameterExist = false;

   char* ok = "HTTP/1.1 200 OK\n";
   char* noContent = "HTTP/1.1 204 No Content\n";

   char* conflict = "HTTP/1.1 409 Conflict\n";
   char* badRequest = "HTTP/1.1 400 Bad Request\n";
   char* notFound =  "HTTP/1.1 404 Not Found\n";

   char* internalServerError = "HTTP/1.1 500 Internal Server Error\n";

   if(strcmp(request->method, "GET") == 0)
   {
      response->contentType = "Content-Type: application/json\n";

      int length = antiSound_list_length(taskList);


      if(length == 0)
      {
         response->status = noContent;
         return isParameterExist;
      }

      queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

      if(antiSound_item_getItem(taskList, atoi(queryParameter->name)) == NULL)
      {
         response->status = badRequest;
         return isParameterExist;
      }

      if(antiSound_item_testRead(request, taskList, response) == false)
      {
         response->status = internalServerError;
         return isParameterExist;
      }
   }

   if(strcmp(request->method, "POST") == 0)
   {
      if(antiSound_http_checkExistingItem(request, taskList))
      {
         response->status = conflict;
         return isParameterExist;
      }
   }

   if(strcmp(request->method, "PUT") == 0)
   {
      if(taskList->next == NULL)
      {
         response->status = noContent;
         return isParameterExist;
      }

      if(antiSound_http_testGetQueryParamter(request, "id") == false)
      {
         response->status = badRequest;
         return isParameterExist;
      }

      queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

      if(antiSound_item_testGetItem(taskList, atoi(queryParameter->name)) == false)
      {
         response->status = notFound;
         return isParameterExist;
      }

      if(antiSound_http_testGetBodyParamter(request, "id") == false)
      {
         response->status = notFound;
         return isParameterExist;
      }
   }

   if(strcmp(request->method, "DELETE") == 0)
   {
      if(taskList->next == NULL)
      {
         response->status = noContent;
         return isParameterExist;
      }

      if(antiSound_http_testGetQueryParamter(request, "id") == false)
      {
         response->status = badRequest;
         return isParameterExist;
      }

      queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

      if(antiSound_item_getItem(taskList, atoi(queryParameter->name)) == false)
      {
         response->status = notFound;
         return isParameterExist;
      }
   }

   response->status = ok;
   return isParameterExist = true;
}

bool antiSound_http_checkExistingItem(request_t* request, list_t* taskList)
{
   bool isTaskExist = false;

   body_t* body = antiSound_http_getBodyParamter(request, "id");

   item_t* item = antiSound_item_getItem(taskList, atoi(body->name));

   if(item != NULL)
   {
      isTaskExist = true;
   }

   return isTaskExist;
}
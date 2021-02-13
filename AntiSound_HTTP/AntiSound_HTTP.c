#include "AntiSound_HTTP.h"
#include "AntiSound_HTTP_Parse/AntiSound_HTTP_Parse.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

task_t* antiSound_http_initializeTask()
{
   task_t* task = malloc(sizeof(task_t));

   task->id = NULL;
   task->name = NULL;
   task->lastname = NULL;

   return task;
}

request_t* antiSound_http_parseRuqest(char* requestData)
{
   request_t* request = antiSound_http_initializeRequest();

   antiSound_http_testParseMethod(request, requestData);
   antiSound_http_testParseHttpVersion(request, requestData);
   antiSound_http_testParseHeaders(request, requestData);
   antiSound_http_testParseUrl(request, requestData);
   antiSound_http_parsePath(request, requestData);
   antiSound_http_testParseQueryParameters(request, requestData);
   antiSound_http_testParseBody(request, requestData);

   free(requestData);
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
   
   printf("end\n");
   return NULL;
}

bool antiSound_http_checkParameters(request_t* request, response_t* response, binaryTree_t* root)
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

      if(root->data == NULL)
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

      if(antiSound_item_testGetItem(atoi(queryParameter->name), root) == false && strcmp(queryParameter->name, "/") != 0)
      {
         response->status = notFound;
         return isParameterExist;
      }

      if(antiSound_item_testRead(request, response, root) == false)
      {
         response->status = internalServerError;
         return isParameterExist;
      }
   }
   
   if(strcmp(request->method, "POST") == 0)
   {
      if(antiSound_http_checkExistingItem(request, root))
      {
         response->status = conflict;
         return isParameterExist;
      }

      if(antiSound_item_testCreate(request, root) == false)
      {
         response->status = badRequest;
         return isParameterExist;
      }
   }

   if(strcmp(request->method, "PUT") == 0)
   {
      if(root->data == NULL)
      {
         response->status = noContent;
         return isParameterExist;
      }

      if(antiSound_http_testGetQueryParamter(request, "id") == false)
      {
         response->status = badRequest;
         return isParameterExist;
      }

      if(antiSound_http_isBodyParametersExist(request))
      {
         response->status = badRequest;
         return isParameterExist;
      }
      
      queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

      if(antiSound_item_testGetItem(atoi(queryParameter->name), root) == false)
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
     
      if(root->data == NULL)
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

      if(antiSound_item_testGetItem(atoi(queryParameter->name), root) == false)
      {
         response->status = notFound;
         return isParameterExist;
      }
   }

   response->status = ok;


   return isParameterExist = true;
}

bool antiSound_http_checkExistingItem(request_t* request, binaryTree_t* root)
{
   bool isTaskExist = false;

   body_t* body = antiSound_http_getBodyParamter(request, "id");

   item_t* item = antiSound_item_getItem(atoi(body->name), root);
   
   if(item != NULL && item->id == atoi(body->name))
   {
      isTaskExist = true;
   }

   return isTaskExist;
}

datas_t* antiSound_http_initializeDatas()
{
   datas_t* datas = malloc(sizeof(datas_t));
   datas->request = NULL;
   datas->root = NULL;
   datas->response = NULL;

   return datas;
}

messege_t* antiSound_http_initializeMesseges()
{
   messege_t* messege = malloc(sizeof(messege_t));
   messege->key = -1;
   messege->message = "\0";

   return messege;
}

queryParameter_t* antiSound_http_initializeQueryParameter()
{
   queryParameter_t* queryParameter = malloc(sizeof(queryParameter_t));
   queryParameter->id = "\0";
   queryParameter->name = "\0";

   return queryParameter;
}

headerParameter_t* antiSound_http_initializeHeaderParameter()
{
   headerParameter_t* headerParameter = malloc(sizeof(headerParameter_t));
   headerParameter->id = "\0";
   headerParameter->name = "\0";

   return headerParameter;
}

body_t* antiSound_http_initializeBody()
{
   body_t* body = malloc(sizeof(body_t));
   body->id = "\0";
   body->name = "\0";

   return body;
}

void antiSound_http_freeRequest(void* data)
{
   datas_t* datas = data;
   free(datas->request->method);

   list_t* pointer = datas->request->body;

   while(pointer != NULL)
   {
      list_t* remove = pointer;
      body_t* body = remove->data;

      pointer = pointer->next;

      free(body);
      free(remove);
   }

   pointer = datas->request->url->queryParameters;

   while(pointer != NULL)
   {
      list_t* remove = pointer;
      queryParameter_t* queryPatameter = remove->data;

      pointer = pointer->next;
      
      free(queryPatameter);
      free(remove); 
   }

   pointer = datas->request->headers;

   while(pointer != NULL)
   {
      list_t* remove = pointer;
      headerParameter_t* headerParameter = remove->data;

      pointer = pointer->next;

      free(headerParameter);
      free(remove); 
   }
   
   free(datas->request->http);
   free(datas->request->path);
   free(datas->request->url->host);
   free(datas->request->url->port);
}

#include "AntiSound_Handler.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

response_t* antiSound_handler_initializeResponse()
{
    response_t* response = malloc(sizeof(response_t));

    response->status = NULL;
    response->httpVersion = NULL;
    response->contentType = NULL;
    response->contentLength = NULL;
    response->body = NULL;

    return response;
}

response_t* antiSound_handler_handler(request_t* request, binaryTree_t* root)
{
    response_t* response = antiSound_handler_initializeResponse();
    
    if(antiSound_http_checkParameters(request, response, root) == false)
    {
        return response;
    }

    if(strcmp(request->method, "GET") == 0)
    {   
        antiSound_item_read(request, response, root);
    }
    
    if(strcmp(request->method, "POST") == 0)
    {
        antiSound_item_create(request, root);
    }

    if(strcmp(request->method, "PUT") == 0)
    {
        antiSound_item_update(request, root);
    }

    if(strcmp(request->method, "DELETE") == 0)
    {
        antiSound_item_remove(request, root);
    }

    return response;
}

char* antiSound_handler_collectResponse(response_t* response)
{
    char* contentLength = "Content-Length: ";

    char* lineBreak = "\n";

    char* collectedResponse = "\0";
    collectedResponse = antiSound_constructor_collector(collectedResponse, response->status);

    if(response->contentType != NULL)
    {
        collectedResponse = antiSound_constructor_collector(collectedResponse, response->contentType);
    }
    else
    {
        collectedResponse =  antiSound_constructor_collector(collectedResponse, "Content-Type: application/json\n");
        collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
    }

    if(response->body != NULL)
    {
        char* charLength = calloc(strlen(response->body) + 1, sizeof(char));
        sprintf(charLength, "%ld", strlen(response->body));

        char* fullContentLength = antiSound_constructor_collector(contentLength, charLength);
        
        collectedResponse = antiSound_constructor_collector(collectedResponse, fullContentLength);
        collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
        collectedResponse = antiSound_constructor_collector(collectedResponse, lineBreak);
        collectedResponse = antiSound_constructor_collector(collectedResponse, response->body);
    }

    printf("%s\n", collectedResponse);

    return collectedResponse;
}
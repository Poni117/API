#include "Handler.h"
#include "../HTTP/HTTP.h"
#include "../List/List.h"
#include "../Constructor/Constructor.h"
#include "../Item/Item.h"
#include "../BinaryTree/BinaryTree.h"
#include "../FIFO/FIFO.h"


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

response_t* handler_initializeResponse()
{
    response_t* response = malloc(sizeof(response_t));

    response->status = NULL;

    response->httpVersion = NULL;

    response->contentType = NULL;

    response->contentLength = NULL;

    response->body = NULL;

    return response;
}

void handler_tasksHandler(request_t* request, response_t* response, binaryTree_t* root)
{
    
    
}

char* handler_collectResponse(response_t* response)
{
    char* contentLength = "Content-Length: ";

    char* lineBreak = "\n";

    char* collectedResponse = "\0";

    collectedResponse = constructor_collector(collectedResponse, response->status);

    if(response->contentType != NULL)
    {
        collectedResponse = constructor_collector(collectedResponse, response->contentType);
    }
    else
    {
        collectedResponse = constructor_collector(collectedResponse, "Content-Type: application/json\n");

        collectedResponse = constructor_collector(collectedResponse, lineBreak);
    }

    if(response->body != NULL)
    {
        char* charLength = calloc(strlen(response->body) + 1, sizeof(char));

        sprintf(charLength, "%ld", strlen(response->body));

        char* fullContentLength = constructor_collector(contentLength, charLength);
        
        collectedResponse = constructor_collector(collectedResponse, fullContentLength);

        collectedResponse = constructor_collector(collectedResponse, lineBreak);

        collectedResponse = constructor_collector(collectedResponse, lineBreak);
        
        collectedResponse = constructor_collector(collectedResponse, response->body);

        collectedResponse = constructor_collector(collectedResponse, lineBreak);
    }

    return collectedResponse;
}

#include "AntiSound_HTTP.h"

void _antiSound_http_parseMethod(request_t* structOfRequest)
{
    char* request = structOfRequest->_parametrs->request;
    size_t sizeOfRequest = strlen(request);

    char bufferOfMethod[256] = "\0";
    
    int i = 0;

    while(i < sizeOfRequest)
    {
        if(request[i] == ' ')
        {
            break;
        }

        bufferOfMethod[i] = request[i];
        i++;
    }

    structOfRequest->_parametrs->method = calloc(strlen(bufferOfMethod) + 1, sizeof(char));
    strcat(structOfRequest->_parametrs->method, bufferOfMethod);

    printf("method\n[%s]\n", structOfRequest->_parametrs->method);
}

//--------------------------------------------------------------------------------------------------------------------------------------

void _antiSound_http_parseId(request_t* structOfRequest)
{
    if(CheckParametrsIdExist(structOfRequest) == false)
    {   
        parametrs->dataId = NULL;
        return;
    }

    char* isolatedParametrId = structOfRequest->_parametrs->isolatedParametrId;
    size_t sizeOfIsolatedParametrId = strlen(isolatedParametrId);

    int i = 0;
    while (i < sizeOfIsolatedParametrId)
    {
        if(isolatedParametrId[i] == '=')
        {
            break;
        }
        i++;
    }

    i++;

    char bufferOfParseId[256] = "\0";

    int j = 0;
    while(i < sizeOfIsolatedParametrId)
    {
        bufferOfParseId[j] = isolatedParametrId[i];
        i++;
        j++;
    }

    structOfRequest->id = calloc(strlen(bufferOfParseId) + 1, sizeof(char));
    strcat(structOfRequest->id, bufferOfParseId);

    printf("dataId:\n[%s]\n", structOfRequest->id);
}

//--------------------------------------------------------------------------------------------------------------------------------------

void _antiSound_http_parseName(request_t* structOfRequest)
{
    char* method = structOfRequest->_parametrs->method;

    char* isolatedParametrsName = structOfRequest->_parametrs->isolatedParametrName;
    size_t sizeOfIsolatedParametrsName = strlen(isolatedParametrsName);

    if(CheckParametrsNameExist(structOfRequest) == false)
    {
        parametrs->dataName = NULL;
        return;
    }

    int i = 0;

    while (i < sizeOfIsolatedParametrsName)
    {
        if(strcmp(method, "POST") == 0 && isolatedParametrsName[i] == ':' )
        {
            break;
        }

        if(strcmp(method, "PUT") == 0 && isolatedParametrsName[i] == '=' )
        {
            break;
        }

        i++;
    }

    i++;

    char bufferOfParseName[256] = "\0";

    int j = 0;

    while (i < sizeOfIsolatedParametrsName)
    {
        bufferOfParseName[j] = isolatedParametrsName[i];
        i++;
        j++;
    }
    
    structOfRequest->name = calloc(strlen(bufferOfParseName) + 1, sizeof(char));
    strcat(structOfRequest->name, bufferOfParseName);

    printf("dataName:\n[%s]\n", structOfRequest->name);
}
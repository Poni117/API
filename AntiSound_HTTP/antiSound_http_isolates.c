#include "AntiSound_HTTP.h"

void _antiSound_http_isolateParametrs(request_t* structOfRequest)
{
    char* request = structOfRequest->_parametrs->request;
    size_t sizeOfRequest = strlen(request);

    char* method = structOfRequest->_parametrs->method;

    int i = 0;

    if(strcmp(method, "POST") == 0)
    {
        int j = 2;

        while (request[j] < sizeOfRequest - 1)
        {
            
            if(request[i] == '\n' && request[j] == '\n')
            {
                break;
            }
       
            i++;
            j++;
        }

        i = j + 1;
    }

    if(strcmp(method, "PUT") == 0 || strcmp(method, "DELETE") == 0)
    {
        while(i < sizeOfRequest)
        {
            if(request[i] == '?')
            {
                break;
            }
            i++;
        }

        i++;
    }

    char bufferOfIsolatedParametrs[1024] = "\0";

    int j = 0;
    while(i < sizeOfRequest)
    {
        if(request[i] == ' ')
        {
            break;
        }
    
        bufferOfIsolatedParametrs[j] = request[i];

        j++;
        i++;
    }

    structOfRequest->_parametrs->isloatedParametrs = calloc(strlen(bufferOfIsolatedParametrs) + 1, sizeof(char));
    strcat(structOfRequest->_parametrs->isloatedParametrs, bufferOfIsolatedParametrs);

    printf("isloatedParametrs\n[%s]\n", structOfRequest->_parametrs->isloatedParametrs);
}

//--------------------------------------------------------------------------------------------------------------------------------------

void _antiSound_http_isolateParametrId(request_t* structOfRequest)
{
    char* method = structOfRequest->_parametrs->method;
    
    if(strcmp(method, "PUT") == 0)
    {
        if(CheckSeparatorExist(structOfRequest->_parametrs) == false)
        {
            _parametrs->isolatedParametrId = NULL;
            return;
        }
    }

    char* isolatedParametrs = structOfRequest->_parametrs->isloatedParametrs;
    size_t sizeOfIsolatedParametrs = strlen(isolatedParametrs);

    char bufferOfIsolated[256] = "\0";


    int i = 0;


    while(i < sizeOfIsolatedParametrs)
    {
        if(isolatedParametrs[i] == '&')
        {
            break;
        }

        bufferOfIsolated[i] = isolatedParametrs[i];
        i++;
    }

    structOfRequest->_parametrs->isolatedParametrId = calloc(strlen(bufferOfIsolated) + 1, sizeof(char));
    strcat(structOfRequest->_parametrs->isolatedParametrId, bufferOfIsolated);

    printf("isolatedParametrId:\n[%s]\n", _parametrs->isolatedParametrId);
}

//--------------------------------------------------------------------------------------------------------------------------------------

void _antiSound_http_isolateParametrName(request_t* structOfRequest)
{
    char* method = structOfRequest->_parametrs->method;

    if(strcmp(method, "PUT") == 0)
    {
        if(CheckSeparatorExist(structOfRequest) == false)
        {
            structOfRequest->_parametrs->isolatedParametrName = NULL;
            return;
        }
    }


    char* isolatedParametrs = structOfRequest->_parametrs->isloatedParametrs;
    size_t sizeOfIsolatedParametrs = strlen(isolatedParametrs);

    int i = 0;

    if(strcmp(method, "PUT") == 0)
    {
        while (i < sizeOfIsolatedParametrs)
        {
            if(isolatedParametrs[i] == '&')
            {
                break;
            }
            i++;
        }
    }

    i++;

    char bufferOfIsolatedParametrName[256] = "\0";

    int j = 0;

    while (i < sizeOfIsolatedParametrs)
    {
        if(isolatedParametrs[i] != '\"' && isolatedParametrs[i] != '{' && isolatedParametrs[i] != '}')
        {
            bufferOfIsolatedParametrName[j] = isolatedParametrs[i];
            j++;
        }
        i++;
    }
    
    structOfRequest->_parametrs->isolatedParametrName = calloc(strlen(bufferOfIsolatedParametrName) + 1, sizeof(char));
    strcat(structOfRequest->_parametrs->isolatedParametrName, bufferOfIsolatedParametrName);

    printf("isolatedParametrName\n[%s]\n", structOfRequest->_parametrs->isolatedParametrName);
}
#include <stdbool.h>
#include "AntiSound_HTTP.h"

bool _antiSound_http_checkSeparatorExist(request_t* structOfRequest)
{
    bool isAmpersandExist = false;

    char* isolatedParametrs = structOfRequest->_parametrs->isloatedParametrs;
    size_t sizeOfIsolatedParametrs = strlen(isolatedParametrs);

    int i = 0;

    while(i < sizeOfIsolatedParametrs)
    {
        if(isolatedParametrs[i] == '&')
        {
            isAmpersandExist = true;
        }
        i++;
    }

    return isAmpersandExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkLabelIdExist(request_t* structOfRequest)
{
    bool isLabelIdExist = false;

    char* isolatedParametrId = structOfRequest->_parametrs->isolatedParametrId;
    size_t sizeOfIsolatedParametrId = strlen(isolatedParametrId);

    char bufferLabelId[256] = "\0";

    int i = 0;

    while(i < sizeOfIsolatedParametrId)
    {
        if(isolatedParametrId[i] == '=')
        {
            break;
        }
        bufferLabelId[i] = isolatedParametrId[i];
        i++;
    }
    
    if(strcmp(bufferLabelId, "id") == 0)
    {
        isLabelIdExist = true;
    }

    printf("isLabelIdExist [%d]\n", isLabelIdExist);
    return isLabelIdExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkParametrIdEqualesExist(request_t* structOfRequest)
{
    bool isParametrIdEqualesExist = false;

    char* isolatedParametrId = structOfRequest->_parametrs->isolatedParametrId;

    if(isolatedParametrId == NULL)
    {
        return false;
    }
    
    if(isolatedParametrId[2] == '=')
    {
        isParametrIdEqualesExist = true;
    }

    return isParametrIdEqualesExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkDataIdExist(parametrs_t* parametrs)
{
    bool isDataIdExist = false;

    char* isolatedParametrId = structOfRequest->_parametrs->isolatedParametrId;

    if(isolatedParametrId[3] != '\0')
    {
        isDataIdExist = true;
    }

    printf("isDataIdExist[%d]\n", isDataIdExist);
    return isDataIdExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkIdExist(request_t* structOfRequest)
{
    bool isIdExist = false;

    if(_antiSound_http_checkParametrsIdExist(structOfRequest) == false || head == NULL)
    {
        return isIdExist;
    }

    printf("isIdExist[%d]\n", isIdExist);
    return isIdExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkParametrsIdExist(request_t* structOfRequest)
{
    bool isParametrsIdExist = false;

    bool isLabelIdExist =  _antiSound_http_checkLabelIdExist(structOfRequest);
    bool isParametrIdEqualesExist =  _antiSound_http_checkParametrIdEqualesExist(structOfRequest);
    bool isDataIdExist =  _antiSound_http_checkDataIdExist(structOfRequest);

    if(isLabelIdExist == true && isParametrIdEqualesExist == true && isDataIdExist == true)
    {
        isParametrsIdExist = true;
    }

    printf("isParametrsIdExist [%d]\n", isParametrsIdExist);
    return isParametrsIdExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkParametrNameEqualesExist(request_t* structOfRequest)
{
    bool isParametrNameEqualesExist = false;

    char* isolatedParametrName = structOfRequest->_parametrs->isolatedParametrName;

    if(isolatedParametrName[4] == '=' || isolatedParametrName[4] == ':')
    {
        isParametrNameEqualesExist = true;
    }

    printf("isParametrNameEqualesExist[%d]\n", isParametrNameEqualesExist);

    return isParametrNameEqualesExist;
}


//--------------------------------------------------------------------------------------------------------------------------------------


bool _antiSound_http_checkLabelNameExist(request_t* structOfRequest)
{
    bool isLabelNameExist = false;

    char* isolatedParametrName = structOfRequest->_parametrs->isolatedParametrName;
    size_t sizeOfIsolatedParametrName = strlen(isolatedParametrName);

    char bufferOfLabelName[256] = "\0";

    int i = 0;
    while(i < sizeOfIsolatedParametrName)
    {
        if(isolatedParametrName[i] == '=' || isolatedParametrName[i] == ':')
        {
            break;
        }

        bufferOfLabelName[i] = isolatedParametrName[i];
        i++;
    }

    if(strcmp(bufferOfLabelName, "name") == 0)
    {
        isLabelNameExist = true; 
    }

    printf("isLabelNameExist[%d]\n", isLabelNameExist);
    return isLabelNameExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkDataNameExist(request_t* structOfRequest)
{
    bool isDataNameExist = false;

    char* isolatedParametrName = structOfRequest->_parametrs->isolatedParametrName;
    
    if(isolatedParametrName[5] != '\0' || isolatedParametrName[5] != ' ')
    {
        isDataNameExist = true;
    }


    return isDataNameExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkParametrsNameExist(request_t* structOfRequest)
{
    bool isParametrsNameExist = false;

    bool isLabelNameExist =  _antiSound_http_checkLabelNameExist(structOfRequest);
    bool isParametrNameParametrEqualseExist =  _antiSound_http_checkParametrNameEqualesExist(structOfRequest);
    bool isDataNameExist =  _antiSound_http_checkDataNameExist(structOfRequest);

    if(isLabelNameExist == true && isParametrNameParametrEqualseExist == true && isDataNameExist == true)
    {
       isParametrsNameExist = true;
    }

    printf("isParametrsNameExist[%d]\n", isParametrsNameExist);
    return isParametrsNameExist;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool _antiSound_http_checkNameExist(request_t* structOfRequest)
{
    bool isNameExist = false;

    if( _antiSound_http_checkParametrsNameExist(structOfRequest) == false)
    {
        return isNameExist;
    }

    char* name = structOfRequest->_parametrs->dataName;

    if(name[0] != '\0')
    {
        isNameExist = true;
    }

    printf("isNameExist:\n[%d]\n", isNameExist);

    return isNameExist;
}
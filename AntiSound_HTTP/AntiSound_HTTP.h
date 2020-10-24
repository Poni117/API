#include <stdbool.h>


typedef struct Parametrs
{
    char* request;
    char* method;
    char* isloatedParametrs;
    char* isolatedParametrId;
    char* isolatedParametrName;
}parametrs_t;

typedef struct Request
{
    char* id;
    char* name;
    parametrs_t* _parametrs;
}request_t;

typedef struct Response
{
    
}response_t;

request_t* antiSound_http_parseRuqest(char* request);

void _antiSound_http_isolateParametrs(request_t* structOfRequest);
void _antiSound_http_isolateParametrId(request_t* structOfRequest);
void _antiSound_http_isolateParametrName(request_t* structOfRequest);

void _antiSound_http_parseMethod(request_t* structOfRequest);
void _antiSound_http_parseId(request_t* structOfRequest);
void _antiSound_http_parseName(request_t* structOfRequest);

bool _antiSound_http_checkSeparatorExist(request_t* structOfRequest);
bool _antiSound_http_checkLabelIdExist(request_t* structOfRequest);
bool _antiSound_http_checkParametrIdEqualesExist(request_t* structOfRequest);
bool _antiSound_http_checkDataIdExist(parametrs_t* parametrs);
bool _antiSound_http_checkIdExist(request_t* structOfRequest);
bool _antiSound_http_checkParametrsIdExist(request_t* structOfRequest);
bool _antiSound_http_checkParametrNameEqualesExist(request_t* structOfRequest);
bool _antiSound_http_checkLabelNameExist(request_t* structOfRequest);
bool _antiSound_http_checkDataNameExist(request_t* structOfRequest);
bool _antiSound_http_checkParametrsNameExist(request_t* structOfRequest);
bool _antiSound_http_checkNameExist(request_t* structOfRequest);

char* antiSound_http_builResponse(response_t* response);

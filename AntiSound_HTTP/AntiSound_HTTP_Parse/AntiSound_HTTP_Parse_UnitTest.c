
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    antiSound_http_testInitializeRequest();

    char* requestData = 
    "PUT /?id=0&name=Dmitry&lastname=Ivanov&nickname=Poni117 HTTP/1.1\n"
    "Host: 127.0.0.1:8090\n"
    "User-Agent: curl/7.68.0\n"
    "Accept: */*\n"
    "Content-Type: application/json\n"
    "\n"
    "{\"id\":\"0\",\"name\":\"Dmitry\",\"lastname\":\"Ivanov\",\"nickname\":\"Poni117\"}";

    request_t* request = antiSound_http_initializeRequest();
    
    antiSound_http_testParseMethod(request, requestData);
    antiSound_http_testParseHttpVersion(request, requestData);
    antiSound_http_testParseUrl(request, requestData);
    antiSound_http_testParseQueryParameters(request, requestData);
    antiSound_http_testParseHeaders(request, requestData);
    antiSound_http_testParseBody(request, requestData);
    antiSound_http_testIsolateData(requestData);
}

//===============================================================================================================================
void antiSound_http_testInitializeRequest()
{
    bool status = false;
//--------------------------------------------------------------------------------------------------------------------------------
    request_t* request = antiSound_http_initializeRequest();
//--------------------------------------------------------------------------------------------------------------------------------
    if(request->method == NULL && request->url->host == NULL && request->url->queryParameters->data == NULL && request->headers->data == NULL)
    {
        status = true;
    }

    if(status == false)
    {
        printf("< antiSound_http_testInitializeRequest >\n");
        printf("status[%d]\n", status);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseMethod(request_t* request, char* requestData)
{
    bool isParseMethodSuccess = false;

    bool isMethodExist = false;
    
    char* methods[] = 
    {
    "POST",
    "GET",
    "PUT",
    "DELETE"
    };
//--------------------------------------------------------------------------------------------------------------------------------
    isParseMethodSuccess = antiSound_http_parseMethod(request, requestData);

    int i = 0;

    while(i < strlen(*methods))
    {
        if(strcmp(methods[i], request->method) == 0)
        {
            isMethodExist = true;
        }
        i++;
    }
//--------------------------------------------------------------------------------------------------------------------------------
    
    if(isParseMethodSuccess == false || isMethodExist == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseMethod >\n\n");
        printf("isParseMethodSuccess[%d]\n", isParseMethodSuccess);
        printf("isMethodExist[%d]\n", isMethodExist);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================

void antiSound_http_testParseHttpVersion(request_t* request, char* requestData)
{
    bool isParseHttpVersionExist = false;

    bool isMethodGetHttpParsed = false;

    bool isMajorCorrect = false;
    bool isMinorCorrect = false;
    bool isVersionProtocolCorrect = false;

    bool isParseHttpSuccess = false;
//--------------------------------------------------------------------------------------------------------------------------------
    isMethodGetHttpParsed = antiSound_http_parseHttpVersion(request, requestData);
//--------------------------------------------------------------------------------------------------------------------------------

    if(isMethodGetHttpParsed == true)
    {
        isParseHttpVersionExist = true;
    }

    if(request->http->major >= 0 && request->http->major <= 2)
    {
        isMajorCorrect = true;
    }

    if(request->http->minor >= 0 && request->http->minor <= 1)
    {
        isMinorCorrect = true;

    }

    if (isMajorCorrect == true &&  isMinorCorrect == true)
    {
        isVersionProtocolCorrect = true;
    }

    if(isParseHttpVersionExist ==  true && isVersionProtocolCorrect == true)
    {
        isParseHttpSuccess = true; 
    }

    if(isParseHttpSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHttpVersion >\n\n");
        printf("isParseHttpVersionSuccess[%d]\n", isParseHttpSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseQueryParameters(request_t* request, char* requestData)
{
    bool isParseQueryParametersSuccess = false;

    bool isListCorrect = true;
    bool isParseQueryParametersExist = false;

    bool isLengthCorrect = false;
    
    queryParameter_t* testListOfQueryParameter[4];

    testListOfQueryParameter[0] = malloc(sizeof(queryParameter_t));
    testListOfQueryParameter[0]->name = "id";
    testListOfQueryParameter[0]->value = "0";

    testListOfQueryParameter[1] = malloc(sizeof(queryParameter_t));
    testListOfQueryParameter[1]->name = "name";
    testListOfQueryParameter[1]->value = "Dmitry";

    testListOfQueryParameter[2] = malloc(sizeof(queryParameter_t));
    testListOfQueryParameter[2]->name = "lastname";
    testListOfQueryParameter[2]->value = "Ivanov";

    testListOfQueryParameter[3] = malloc(sizeof(queryParameter_t));
    testListOfQueryParameter[3]->name = "nickname";
    testListOfQueryParameter[3]->value = "Poni117";

//--------------------------------------------------------------------------------------------------------------------------------
    isParseQueryParametersExist = antiSound_http_parseQuaryParameters(request, requestData);

    list_t* pointer = request->url->queryParameters;

    if (pointer->id == -1)
    {
        pointer = pointer->next;
    }
    
    while (true)
    {
        queryParameter_t* listOfQueryParameter = pointer->data;

        char* actualName = listOfQueryParameter->name;
   
        char* expectedName = testListOfQueryParameter[pointer->id]->name;
        if(strcmp(actualName, expectedName) != 0)
        {
            isListCorrect = false;
            break;
        }

        char* actualValue = listOfQueryParameter->value;
      
        char* expectedValue = testListOfQueryParameter[pointer->id]->value;
        if(strcmp(actualValue, expectedValue) != 0)
        {
            isListCorrect = false;
            break;
        }

        if(pointer->next == NULL)
        {
            break;
        }
        pointer = pointer->next;
    }

    int length = antiSound_list_length(pointer);
//--------------------------------------------------------------------------------------------------------------------------------
    if(pointer->id + 1 == length)
    {
        isLengthCorrect = true;
    }

    if(isParseQueryParametersExist == true && isListCorrect == true && isLengthCorrect == true)
    {
        isParseQueryParametersSuccess = true;
    }

    if(isParseQueryParametersSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseQueryParameters >\n\n");
        printf("isParseQueryParametersSuccess[%d]\n", isParseQueryParametersSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseUrl(request_t* request, char* requestData)
{
    bool isParseUrlSuccess = false;

    bool isParseUrlExist = false;
    bool isHostCorrect = false;
    bool isPortCorrect = false;

    char* host = "127.0.0.1";
    char* port = "8090";
//--------------------------------------------------------------------------------------------------------------------------------
    isParseUrlExist = antiSound_http_parseUrl(request, requestData);
//--------------------------------------------------------------------------------------------------------------------------------
    if(strcmp(request->url->host, host) == 0)
    {
        isHostCorrect = true;
    }

    if(strcmp(request->url->port, port) == 0)
    {
        isPortCorrect = true;
    }

    if(isParseUrlExist == true && isHostCorrect == true && isPortCorrect == true)
    {
        isParseUrlSuccess = true;
    }

    if (isParseUrlSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseUrl >\n\n");
        printf("isParseUrlSuccess[%d]\n", isParseUrlSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================

void antiSound_http_testIsolateData(char* requestData)
{
    bool isIsolatesSuccess = false;

    bool isMethodIsolated = false;
    bool isHttpIsolated = false;
    bool isUrlIsolated = false;
    bool isQueryParametersIsolated = false;

    char* method = "PUT";
    char* http = "HTTP/1.1";
    char* queryParameters = "id=0&name=Dmitry&lastname=Ivanov&nickname=Poni117";
    char* url = "Host: 127.0.0.1:8090";
    
//--------------------------------------------------------------------------------------------------------------------------------
    char* isoltedMethod = antiSound_http_isolateData(requestData, requestData[0], ' ');

    char* isolatedQueryParameters = antiSound_http_isolateData(requestData, '?', ' ');
    
    char* alterateRequestData = strchr(requestData, '\n');
    alterateRequestData++;
    char* isolatedUrl = antiSound_http_isolateData(alterateRequestData, alterateRequestData[0], '\n');

    char* alteradeRequest = strchr(requestData, '/');
    char* isolatedHttp = antiSound_http_isolateData(alteradeRequest, ' ', '\n');
    
    
//--------------------------------------------------------------------------------------------------------------------------------
    if(strcmp(http, isolatedHttp) == 0)
    {
        isHttpIsolated = true;
    }

    if(strcmp(method, isoltedMethod) == 0)
    {
        isMethodIsolated = true;
    }

    if(strcmp(queryParameters, isolatedQueryParameters) == 0)
    {
        isQueryParametersIsolated = true;
    }
    if(strcmp(url, isolatedUrl) == 0)
    {
        isUrlIsolated = true;
    }

    if (isMethodIsolated == true && isHttpIsolated == true && isUrlIsolated == true && isQueryParametersIsolated == true)
    {
        isIsolatesSuccess = true;
    }

    if (isIsolatesSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testIsolateData >\n\n");
        printf("isIsolatesSuccess[%d]\n", isIsolatesSuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================
void antiSound_http_testParseBody(request_t* request, char* requestData)
{

    bool isParseBodySuccess = false;
    bool isParsedBodyExist = false;
    
    bool isLengthCorrect = false;
    bool isListCorrect = true;

    body_t* testListOfBodyParameter[4];
    
    testListOfBodyParameter[0] = malloc(sizeof(body_t));
    testListOfBodyParameter[0]->name = "id";
    testListOfBodyParameter[0]->value = "0";

    testListOfBodyParameter[1] = malloc(sizeof(body_t));
    testListOfBodyParameter[1]->name = "name";
    testListOfBodyParameter[1]->value = "Dmitry";

    testListOfBodyParameter[2] = malloc(sizeof(body_t));
    testListOfBodyParameter[2]->name = "lastname";
    testListOfBodyParameter[2]->value = "Ivanov";

    testListOfBodyParameter[3] = malloc(sizeof(body_t));
    testListOfBodyParameter[3]->name = "nickname";
    testListOfBodyParameter[3]->value = "Poni117";
//--------------------------------------------------------------------------------------------------------------------------------
    isParsedBodyExist = antiSound_http_parseBody(request, requestData);

    list_t* pointer = request->body;

    if (pointer->id == -1)
    {
        pointer = pointer->next;
    }

    while (true)
    {   
        body_t* listOfBodyParameter = pointer->data;
 
        if(strcmp(listOfBodyParameter->name, testListOfBodyParameter[pointer->id]->name) != 0)
        {
            isListCorrect = false;
            break;
        }

        if(strcmp(listOfBodyParameter->value, testListOfBodyParameter[pointer->id]->value) != 0)
        {
            isListCorrect = false;
            break;
        }

        if(pointer->next == NULL)
        {
            break;
        }
        pointer = pointer->next;
    }

    int length = antiSound_list_length(pointer);
//--------------------------------------------------------------------------------------------------------------------------------
    if(pointer->id + 1 == length)
    {
        isLengthCorrect = true;
    }

    if(isParsedBodyExist == true && isLengthCorrect == true && isListCorrect == true)
    {
        isParseBodySuccess = true;
    }

    if(isParseBodySuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseBody >\n\n");
        printf("isParseBodySuccess[%d]\n", isParseBodySuccess);
        printf("-------------------------\n");
    }
}

//===============================================================================================================================

void antiSound_http_testParseHeaders(request_t* request, char* requestData)
{
    bool isParseHeadersSuccess = false;
    bool isParseHeadersExist = false;

    bool isListCorrect = true;
    bool isLengthCorrect = false;

    headerParameter_t* testListOfHeadrerParameter[3];

    testListOfHeadrerParameter[0] = malloc(sizeof(headerParameter_t));
    testListOfHeadrerParameter[0]->name = "User-Agent";
    testListOfHeadrerParameter[0]->value = "curl/7.68.0";

    testListOfHeadrerParameter[1] = malloc(sizeof(headerParameter_t));
    testListOfHeadrerParameter[1]->name = "Accept";
    testListOfHeadrerParameter[1]->value = "*/*";

    testListOfHeadrerParameter[2] = malloc(sizeof(headerParameter_t));
    testListOfHeadrerParameter[2]->name = "Content-Type";
    testListOfHeadrerParameter[2]->value = "application/json";

//--------------------------------------------------------------------------------------------------------------------------------
    isParseHeadersExist = antiSound_http_parseHeaders(request, requestData);

    list_t* pointer = request->headers;
    

    if (pointer->id == -1)
    {
        pointer = pointer->next;
    }
    
    while(true)
    {
        headerParameter_t* listOfHeaderParameter = pointer->data;

        if(strcmp(listOfHeaderParameter->name, testListOfHeadrerParameter[pointer->id]->name) != 0)
        {
            isListCorrect = false;
            break;
        }

        if(strcmp(listOfHeaderParameter->value, testListOfHeadrerParameter[pointer->id]->value) != 0)
        {
            isListCorrect = false;
        }

        if(pointer->next == NULL)
        {
            break;
        }
        pointer = pointer->next;
    }

    int length = antiSound_list_length(pointer);
//--------------------------------------------------------------------------------------------------------------------------------
    if(pointer->id + 1 == length)
    {
        isLengthCorrect = true;
    }

    if(isParseHeadersExist == true && isListCorrect == true && isLengthCorrect == true)
    {
        isParseHeadersSuccess = true;
    }

    if(isParseHeadersSuccess == false)
    {
        printf("-------------------------\n");
        printf("< antiSound_http_testParseHeaders >\n\n");
        printf("isParseHeadersSuccess[%d]\n", isParseHeadersSuccess);
        printf("-------------------------\n");
    }
}
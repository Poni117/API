#include "Item.h"

#include "../HTTP/HTTP.h"
#include "../List/List.h"
#include "../BinaryTree/BinaryTree.h"

#include "stdbool.h"


bool item_testGetItem(int id, binaryTree_t* root)
{
    bool isGetItemSuccess = false;

    item_t* item = item_getItem(id, root);

    if(item != NULL && item->id == id)
    {
        isGetItemSuccess = true;
    }

    if(isGetItemSuccess == false)
    {
        printf("---------------------------------\n");

        printf("antiSound_item_testGetItem\n");

        printf("isGetItemSuccess[%d]\n", isGetItemSuccess);
    }

    return isGetItemSuccess;
}

bool item_testInitializeItem()
{
    bool isInitializeItemSuccess = false;

    bool isIdInitialized = false;

    bool isDataInitialized = false;

    item_t* item = item_initializeItem();

    if(item->id == -1)
    {
        isIdInitialized = true;
    }

    if(item->data == NULL)
    {
        isDataInitialized = true;
    }

    if(isIdInitialized == true && isDataInitialized == true)
    {
        isInitializeItemSuccess = true;
    }

    if(isInitializeItemSuccess == false)
    {
        printf("---------------------------------\n");

        printf("antiSound_item_testInitializeItem\n");

        printf("isInitializeItemSuccess[%d]\n", isInitializeItemSuccess);
    }

    return isInitializeItemSuccess;
}

bool item_testRead(request_t* request, response_t* response, binaryTree_t* root)
{
    bool isReadSuccess = false;

    isReadSuccess = item_read(request, response, root);

    if(isReadSuccess == false)
    {
        printf("---------------------------------\n");

        printf("antiSound_item_testRead\n");

        printf("isReadSuccess[%d]\n", isReadSuccess);
    }

    return isReadSuccess;
}

bool item_testCreate(request_t* request, binaryTree_t* root)
{
    bool isParametersExist = http_isBodyParametersExist(request);

    if(isParametersExist == false)
    {
        printf("---------------------------------\n");

        printf("antiSound_item_testCreate\n");

        printf("isParametersExist[%d]\n", isParametersExist);
    }

    return isParametersExist;
}

bool http_isBodyParametersExist(request_t* request)
{
    bool isBodyParametersExist = false;

    bool isIdExist = http_testGetBodyParamter(request, "id");
    
    bool isNameExist = http_testGetBodyParamter(request, "name");

    bool isLastNameExist = http_getBodyParamter(request, "lastname");

    if(isIdExist == true && isNameExist == true && isLastNameExist == true)
    {
        isBodyParametersExist = true;
    }

    if(isBodyParametersExist == false)
    {
        printf("---------------------------------\n");

        printf("antiSound_http_isBodyParametersExist\n");
        
        printf("isBodyParametersExist[%d]\n", isBodyParametersExist);
    }

    return isBodyParametersExist;
}
#include "AntiSound_Item.h"

#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"

#include "stdbool.h"


bool antiSound_item_testGetItem(int id, binaryTree_t* root)
{
    bool isGetItemSuccess = false;

    item_t* item = antiSound_item_getItem(id, root);

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

bool antiSound_item_testInitializeItem()
{
    bool isInitializeItemSuccess = false;

    bool isIdInitialized = false;
    bool isDataInitialized = false;

    item_t* item = antiSound_item_initializeItem();

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

bool antiSound_item_testRead(request_t* request, response_t* response, binaryTree_t* root)
{
    bool isReadSuccess = false;

    isReadSuccess = antiSound_item_read(request, response, root);

    if(isReadSuccess == false)
    {
        printf("---------------------------------\n");
        printf("antiSound_item_testRead\n");
        printf("isReadSuccess[%d]\n", isReadSuccess);
    }
    return isReadSuccess;
}

#include "Item.h"

#include "../HTTP/HTTP.h"
#include "../List/List.h"
#include "../Constructor/Constructor.h"
#include "../BinaryTree/BinaryTree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

item_t* item_initializeItem()
{
   item_t* item = malloc(sizeof(item_t));
   item->id = -1;
   item->data = NULL;

   return item;
}

bool item_read(request_t* request, response_t* response, binaryTree_t* root)
{
    bool isGetSuccess = false;


    response->body = constructor_decodeToJson(request, root);

    if(response->body != NULL)
    {
        isGetSuccess = true;
    }

    return isGetSuccess;
}

bool item_create(request_t* request, binaryTree_t* root)
{
    bool isPostTaskSuccess = false;

    if(item_testInitializeItem() == false)
    {
        return isPostTaskSuccess;
    }

    body_t* id = http_getBodyParamter(request, "id");

    body_t* name = http_getBodyParamter(request, "name");

    body_t* lastname = http_getBodyParamter(request, "lastname");

    task_t* task = http_initializeTask();

    task->id = id;

    task->name = name;

    task->lastname = lastname;

    item_t* item = item_initializeItem();

    item->id = atoi(id->name);

    item->data = task;

    isPostTaskSuccess = binaryTree_addNewNode(root, item);

    return isPostTaskSuccess;
}

bool item_update(request_t* request,binaryTree_t* root)
{
    bool isUpdateItemSuccess = false;

    queryParameter_t* queryParameter = http_getQueryParamter(request, "id");

    item_t* item = binaryTree_getData(root, atoi(queryParameter->name));

    task_t* task = item->data;

    task->name = http_getBodyParamter(request, "name");
    
    task->lastname =  http_getBodyParamter(request, "lastname");

    return isUpdateItemSuccess = true;
}

bool item_remove(request_t* request, binaryTree_t* root)
{
    bool isDeleteSuccess = false;

    queryParameter_t* queryParameter = http_getQueryParamter(request, "id");

    isDeleteSuccess = binaryTree_removeNode(root, atoi(queryParameter->name));

    return isDeleteSuccess;
}

item_t* item_getItem(int id, binaryTree_t* root)
{
    return binaryTree_getData(root, id);
}


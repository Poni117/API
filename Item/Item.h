#include "../HTTP/HTTP.h"
#include "../List/List.h"
#include "../BinaryTree/BinaryTree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Item
{
    int id;
    void* data;
}item_t;

/*
 *  initializes Item and returns pointer to item_t
 */
item_t* item_initializeItem();

/*
 *  updates existing item
 *  returns true in case of success, otherwise false
 */
bool item_update(request_t* request, binaryTree_t* root);

/*
 *  reads BynaryTree
 *  returns true in case of success, otherwise false 
 */
bool item_read(request_t* request, response_t* response, binaryTree_t* root);

/*
 *  adds new item to the list with specified data  
 *  returns id of newly created item
 */
bool item_create(request_t* request, binaryTree_t* root);

/*
 *  removes item by id
 *  returns true in case of success, otherwise false
 */
bool item_remove(request_t* request, binaryTree_t* root);


/*
 *  find item by BynaryTree
 *  returns item_t
 */
item_t* item_getItem(int id, binaryTree_t* root);

/*
 *  set id of item from request
 *  returns true in case of success, otherwise false
 */
bool antiSound_item_setItemId(item_t* item);

/*
 *  test of  antiSound_item_initializeItem
 */
bool item_testInitializeItem();

/*
 *  test of antiSound_item_getItem
 */
bool item_testGetItem(int id, binaryTree_t* root);

/*
 *  test of antiSound_item_read
 */
bool item_testRead(request_t* request, response_t* response, binaryTree_t* root);

/*
 *  test of antiSound_item_create
 */
bool item_testCreate(request_t* request, binaryTree_t* root);
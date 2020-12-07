#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_List/AntiSound_List.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Item
{
    int id;
    void* data;
}item_t;

item_t* antiSound_item_initializeItem();

list_t* antiSound_item_findItem(list_t* list, int id);

item_t* antiSound_item_getItem(list_t* list, int id);

bool antiSound_item_setItemId(item_t* item);

bool antiSound_item_update(request_t* request, list_t* taskList);

bool antiSound_item_read(request_t* request, list_t* taskList, response_t* response);

bool antiSound_item_create(request_t* request, list_t* taskList);

bool antiSound_item_remove(request_t* request, list_t* taskList);

//=====================================================================================================

bool antiSound_item_testInitializeItem();

bool antiSound_item_testGetItem(list_t* list, int id);




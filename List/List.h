#ifndef ANTISOUND_LIST_H
#define ANTISOUND_LIST_H

#include <stdbool.h>


typedef struct List
{
    int id;
    void* data;
    struct List* next;
    struct List* lastItem;
}list_t;

/* 
 * initializes List and returns pointer to list
 */ 
list_t* list_new();

/*
 * adds new item to the list with specified data  
 * returns id of newly created item
 */
int list_add(list_t* list, void* data);

/*
 * updates existing item
 * returns true in case of success, otherwise false
 */
bool list_update(list_t* list, int id, void* newData); 

/*
 * returns data of item by id  
 */
void* list_getData(list_t* list, int id);

/*
 *  find request id and return item
 */
list_t* list_getItem(list_t* list, int id);

/*
 *  removes item by id
 *  returns true in case of success, otherwise false
 */
bool list_remove(list_t* list, int id);

/*
 * returns length of the list
 */
int list_length(list_t* list);

/*
 * redifine id of the lists
 */
void list_redefineId(list_t* pointer);

/*
 * test of list_new
 */
list_t* antiSound_list_testNew();

/*
 * test of list_add
 */
void list_testAdd(list_t* list);

/*
 * test of antiSound_list_update
 */
void list_testUpdate(list_t* list, int id, void* newData);

/*
 * test of antiSound_list_getItem
 */
bool list_testGetItem(list_t* list, int id);

/*
 * test of antiSound_list_getData
 */
bool list_testGetData(list_t* list, int id);

/*
 * test of antiSound_list_remove
 */
void list_testRemove(list_t* list);

/*
 * test of antiSound_list_length
 */
void list_testLength(list_t* list);

#endif // ANTISOUND_LIST_H
#ifndef ANTISOUND_LIST_H
#define ANTISOUND_LIST_H

#include <stdbool.h>


typedef struct List
{
    int id;
    void* data;
    struct List* next;
}list_t;

/* 
 * initializes List and returns pointer to list
 */ 
list_t* antiSound_list_new();

/*
 * adds new item to the list with specified data  
 * returns id of newly created item
 */
int antiSound_list_add(list_t* list, void* data);

/*
 * updates existing item
 * returns true in case of success, otherwise false
 */
bool antiSound_list_update(list_t* list, int id, void* newData); 

/*
 * returns data of item by id  
 */
void* antiSound_list_getData(list_t* list, int id);

/*
 *  find request id and return item
 */
list_t* antiSound_list_getItem(list_t* list, int id);

/*
 *  removes item by id
 *  returns true in case of success, otherwise false
 */
bool antiSound_list_remove(list_t* list, int id);

/*
 * returns length of the list
 */
int antiSound_list_length(list_t* list);

/*
 * redifine id of the lists
 */
void antiSound_list_redefineId(list_t* pointer);

/*
 * test of antiSound_list_new
 */
list_t* antiSound_list_testNew();

/*
 * test of antiSound_list_add
 */
void antiSound_list_testAdd(list_t* list);

/*
 * test of antiSound_list_update
 */
void antiSound_list_testUpdate(list_t* list);

/*
 * test of antiSound_list_getItem
 */
bool antiSound_list_testGetItem(list_t* list);

/*
 * test of antiSound_list_getData
 */
void antiSound_list_testGetData(list_t* list);

/*
 * test of antiSound_list_remove
 */
void antiSound_list_testRemove(list_t* list);

/*
 * test of antiSound_list_length
 */
void antiSound_list_testLength(list_t* list);

#endif // ANTISOUND_LIST_H
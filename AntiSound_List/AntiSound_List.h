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

void antiSound_list_redefineId(list_t* pointer);
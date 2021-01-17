#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"

#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"


#include <stdio.h>
#include <stdlib.h>

/*
 *  adds layout for body by response, returns collected body
 */
char* antiSound_constructor_addLayout(char* data, char* layout);

/*
 *  collects dataA and dataB, returns collected data
 */
char* antiSound_constructor_collector(char* dataA, char* dataB);

/*
 *  decodes data from list to json format, returns json data
 */
char* antiSound_constructor_decodeListToJson(binaryTree_t* root);

/*
 *  decodes item to json format, returns json item
 */
char* antiSound_constructor_decodeItemToJson(char* id, char* name);

/*
 *  decodes task to json format, returns json task
 */
char* antiSound_constructor_decodeTaskToJson(task_t* item);

/*
 *  decodes task to json format, returns json task
 */
char* antiSound_constructor_decodeToJson(request_t* request, binaryTree_t* root);

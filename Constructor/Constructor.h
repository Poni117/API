#include "../BinaryTree/BinaryTree.h"

#include "../List/List.h"
#include "../HTTP/HTTP.h"


#include <stdio.h>
#include <stdlib.h>

/*
 *  adds layout for body by response, returns collected body
 */
char* constructor_addLayout(char* data, char* layout);

/*
 *  collects dataA and dataB, returns collected data
 */
char* constructor_collector(char* dataA, char* dataB);

/*
 *  decodes data from list to json format, returns json data
 */
char* constructor_decodeListToJson(binaryTree_t* root);

/*
 *  decodes item to json format, returns json item
 */
char* constructor_decodeItemToJson(char* id, char* name);

/*
 *  decodes task to json format, returns json task
 */
char* constructor_decodeTaskToJson(task_t* item);

/*
 *  decodes task to json format, returns json task
 */
char* constructor_decodeToJson(request_t* request, binaryTree_t* root);

/*
 *  generates random key
 */
char* constructor_generateKey();

#include "Constructor.h"

#include "../List/List.h"
#include "../HTTP/HTTP.h"
#include "../Item/Item.h"
#include "../BinaryTree/BinaryTree.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* constructor_addLayout(char* data, char* layout)
{
    char* buildedValue = calloc(0, sizeof(char));

    buildedValue = realloc(buildedValue, strlen(layout) + strlen(data));
    
    sprintf(buildedValue, layout, data);

    return buildedValue;
}

char* constructor_collector(char* dataA, char* dataB)
{
    if(dataA == NULL)
    {
        return dataB;
    }

    if(dataB == NULL)
    {
        return dataA;
    }
    
    char* collectedData = calloc(strlen(dataA) + strlen(dataB) + 1, sizeof(char));

    strncat(collectedData, dataA, strlen(dataA));

    strncat(collectedData, dataB, strlen(dataB));

    return collectedData;
}

char* constructor_decodeListToJson(binaryTree_t* root)
{
    if(root == NULL)
    {
        return NULL;
    }

    char* jsonTasks = "\0";

    char* commaLayout = "%s, ";
    
    item_t* item = root->data;
    
    jsonTasks = constructor_collector(constructor_decodeListToJson(root->right),constructor_collector(constructor_decodeListToJson(root->left), constructor_decodeTaskToJson(item->data)));

    if(root->parent != NULL)
    {
        jsonTasks = constructor_addLayout(jsonTasks, commaLayout);
    }

    return jsonTasks;
}

char* constructor_decodeItemToJson(char* id, char* name)
{   
    char* formatJson = "\"%s\":\"%s\"";

    char* collectJson = calloc(strlen(formatJson) + strlen(id) + strlen(name), sizeof(char));

    sprintf(collectJson, formatJson, id, name);

    return collectJson;
}

char* constructor_decodeTaskToJson(task_t* task)
{
    char* commaLayout = "%s, ";

    char* bracketLayout = "{%s}";

    char* buffer = "\0";
    
    body_t* id = task->id;

    body_t* name = task->name;

    body_t* lastName = task->lastname;

    buffer = constructor_collector(buffer, constructor_decodeItemToJson(id->id, id->name));

    buffer = constructor_addLayout(buffer, commaLayout);

    buffer = constructor_collector(buffer, constructor_decodeItemToJson(name->id, name->name));

    buffer = constructor_addLayout(buffer, commaLayout);
    
    buffer = constructor_collector(buffer, constructor_decodeItemToJson(lastName->id, lastName->name));
    
    return constructor_addLayout(buffer, bracketLayout);
}

char* constructor_decodeToJson(request_t* request, binaryTree_t* root)
{
    queryParameter_t* queryParameter = http_getQueryParamter(request, "id");

    char* body = NULL;

    if(strcmp(queryParameter->name, "/") == 0)
    {
        body = constructor_decodeListToJson(root);
    }
    else
    {
       item_t* item = item_getItem(atoi(queryParameter->name), root);
        
        body = constructor_decodeTaskToJson(item->data);   
    }
    
    return body;
}

char* constructor_generateKey()
{
    int keys[5] = {0, 0, 0, 0, 0};

    int i = 0;

    while (i != 5)
    {   
        srandom(clock());

        keys[i] = random();

        i++;
    }
    
    char* key = calloc(1, sizeof(char));
    i = 0;

    while (i != 5)
    {
        char* buffer = calloc(100, sizeof(char));

        sprintf(buffer, "%d", keys[i]);

        key = constructor_collector(key, buffer);

        if(i < 4)
        {
            key = constructor_collector(key, "-");
        }

        free(buffer);

        i++;
    }

    return key;
}
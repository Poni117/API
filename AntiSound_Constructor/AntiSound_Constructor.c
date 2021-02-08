#include "AntiSound_Constructor.h"

#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* antiSound_constructor_addLayout(char* data, char* layout)
{
    char* buildedValue = calloc(0, sizeof(char));

    buildedValue = realloc(buildedValue, strlen(layout) + strlen(data));
    sprintf(buildedValue, layout, data);

    return buildedValue;
}

char* antiSound_constructor_collector(char* dataA, char* dataB)
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

char* antiSound_constructor_decodeListToJson(binaryTree_t* root)
{
    if(root == NULL)
    {
        return NULL;
    }

    char* jsonTasks = "\0";
    char* commaLayout = "%s, ";
    
    item_t* item = root->data;
    
    jsonTasks = antiSound_constructor_collector(antiSound_constructor_decodeListToJson(root->right),antiSound_constructor_collector(antiSound_constructor_decodeListToJson(root->left), antiSound_constructor_decodeTaskToJson(item->data)));

    if(root->parent != NULL)
    {
        jsonTasks = antiSound_constructor_addLayout(jsonTasks, commaLayout);
    }

    return jsonTasks;
}

char* antiSound_constructor_decodeItemToJson(char* id, char* name)
{   
    char* formatJson = "\"%s\":\"%s\"";

    char* collectJson = calloc(strlen(formatJson) + strlen(id) + strlen(name), sizeof(char));

    sprintf(collectJson, formatJson, id, name);

    return collectJson;
}

char* antiSound_constructor_decodeTaskToJson(task_t* task)
{
    char* commaLayout = "%s, ";
    char* bracketLayout = "{%s}";

    char* buffer = "\0";
    
    body_t* id = task->id;
    body_t* name = task->name;
    body_t* lastName = task->lastname;

    buffer = antiSound_constructor_collector(buffer, antiSound_constructor_decodeItemToJson(id->id, id->name));
    buffer = antiSound_constructor_addLayout(buffer, commaLayout);

    buffer = antiSound_constructor_collector(buffer, antiSound_constructor_decodeItemToJson(name->id, name->name));
    buffer = antiSound_constructor_addLayout(buffer, commaLayout);
    
    buffer = antiSound_constructor_collector(buffer, antiSound_constructor_decodeItemToJson(lastName->id, lastName->name));
    
    return antiSound_constructor_addLayout(buffer, bracketLayout);
}

char* antiSound_constructor_decodeToJson(request_t* request, binaryTree_t* root)
{
    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    char* body = NULL;

    if(strcmp(queryParameter->name, "/") == 0)
    {
        body = antiSound_constructor_decodeListToJson(root);
    }
    else
    {
       item_t* item = antiSound_item_getItem(atoi(queryParameter->name), root);
        
        body = antiSound_constructor_decodeTaskToJson(item->data);   
    }
    
    return body;
}

char* antiSound_constructor_generateKey()
{
    int keys[5] = {0, 0, 0, 0, 0};

    int i = 0;

    while (i != 5)
    {   
        srandom(clock());
        keys[i] = random();
        i++;
    }
    
    char* key = calloc(0, sizeof(char));
    i = 0;

    while (i != 5)
    {
        char* buffer = calloc(100, sizeof(char));

        sprintf(buffer, "%d", keys[i]);
        key = antiSound_constructor_collector(key, buffer);

        if(i < 4)
        {
            key = antiSound_constructor_collector(key, "-");
        }
        free(buffer);
        i++;
    }

    return key;
}
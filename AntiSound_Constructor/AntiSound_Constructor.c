#include "AntiSound_Constructor.h"

#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Item/AntiSound_Item.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* antiSound_constructor_addLayout(char* data, char* layout)
{
    char* buildedValue = calloc(0, sizeof(char));

    buildedValue = realloc(buildedValue, strlen(layout) + strlen(data));
    sprintf(buildedValue, layout, data);

    return buildedValue;
}

char* antiSound_constructor_collector(char* dataA, char* dataB)
{
    char* collectedData = calloc(strlen(dataA) + strlen(dataB) + 1, sizeof(char));
    strncat(collectedData, dataA, strlen(dataA));
    strncat(collectedData, dataB, strlen(dataB));

    return collectedData;
}

char* antiSound_constructor_decodeListToJson(list_t* taskList)
{
    char* jsonTasks = "\0";

    char* commaLayout = "%s, ";

    list_t* pointer = taskList;
    
    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }
    
    while(pointer != NULL)
    {
        item_t* item = pointer->data;

        jsonTasks = antiSound_constructor_collector(jsonTasks, antiSound_constructor_decodeTaskToJson(item->data));

        if(pointer->next != NULL)
        {
            jsonTasks = antiSound_constructor_addLayout(jsonTasks, commaLayout);
        }

        pointer = pointer->next;
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

char* antiSound_constructor_decodeToJson(request_t* request, list_t* taskList)
{
    queryParameter_t* queryParameter = antiSound_http_getQueryParamter(request, "id");

    char* body = NULL;

    if(queryParameter == NULL)
    {
        body = antiSound_constructor_decodeListToJson(taskList);
    }

    if(queryParameter != NULL)
    {
        item_t* item = antiSound_item_getItem(taskList, atoi(queryParameter->name));
        
        body = antiSound_constructor_decodeTaskToJson(item->data);   
    }

    return body;
}



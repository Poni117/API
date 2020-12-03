#include "AntiSound_Constructor.h"

#include "../AntiSound_List/AntiSound_List.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
 
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

    list_t* pointer = taskList->next;
    
    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }
    
    while(pointer != NULL)
    {
        jsonTasks = antiSound_constructor_collector(jsonTasks, antiSound_constructor_decodeTaskToJson(pointer->data));

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

char* antiSound_constructor_decodeTaskToJson(list_t* list)
{
    char* commaLayout = "%s, ";
    char* bracketLayout = "{%s}";

    list_t* pointer = list;

    if(pointer->id == -1)
    {
        pointer = pointer->next;
    }

    char* buffer = "\0";
    
    while(pointer != NULL)
    {
        body_t* body = pointer->data;

        char* jsonValue = antiSound_constructor_decodeItemToJson(body->id, body->name);

        buffer = antiSound_constructor_collector(buffer, jsonValue);
        
        if(pointer->next != NULL)
        {
            buffer = antiSound_constructor_addLayout(buffer, commaLayout);
        }

        pointer = pointer->next;
    }

    return antiSound_constructor_addLayout(buffer, bracketLayout);;
}




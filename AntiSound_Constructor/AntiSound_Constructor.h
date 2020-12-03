#include "../AntiSound_List/AntiSound_List.h"

#include <stdio.h>
#include <stdlib.h>


char* antiSound_constructor_addLayout(char* data, char* layout);

char* antiSound_constructor_collector(char* dataA, char* dataB);

char* antiSound_constructor_decodeListToJson(list_t* list);

char* antiSound_constructor_decodeItemToJson(char* id, char* name);

char* antiSound_constructor_decodeTaskToJson(list_t* taskList);

#include <stdlib.h> 
#include <stdbool.h>

#include "../AntiSound_FIFO/AntiSound_FIFO.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"

void* antiSound_threads_checkFifo(void* data);

bool antiSound_threads_exeRequest(datas_t* datas);

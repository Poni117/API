#include <stdlib.h> 
#include <stdbool.h>

#include "../FIFO/FIFO.h"
#include "../HTTP/HTTP.h"

void* threads_checkFifo(void* data);

bool threads_exeRequest(datas_t* datas);

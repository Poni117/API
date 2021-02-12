#ifndef ANTISOUND_FIFO_H
#define ANTISOUND_FIFO_H

#include  <stdlib.h>
#include  <stdbool.h>

typedef struct FIFO
{
    int id;

    void* data;
    struct FIFO* next;
    struct FIFO* tale;
}fifo_t;

/*
 *  initializes struct FIFO and returns pointer to fifo_t
 */
fifo_t* antiSound_fifo_initializeFifo();

/*
 *  removes first item(head) and returns pointer to new head
 */
bool antiSound_fifo_pop(fifo_t* fifo);

/*
 *  add data to last item(tail)
 *  returns true in case success, otherwise fasle
 */
bool antiSound_fifo_push(fifo_t* fifo, void* data);

/*
 *  checking the queue for the presence of elements in it,
 *  returns true in case success, otherwise fasle
 */
bool antiSound_fifo_isEmpty(fifo_t* fifo);

/*
 *  returns size of fifo;
 */
int antiSound_fifo_size(fifo_t* fifo);

fifo_t* antiSound_fifo_getHead(fifo_t* head);

#endif // ANTISOUND_FIFO_H

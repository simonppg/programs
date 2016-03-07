#ifndef _FIFO_H_
#define _FIFO_H_

struct Fifo_s;
typedef struct Fifo_s Fifo;

Fifo * fifo_create();
void fifo_destroy(Fifo *fifo);

#endif

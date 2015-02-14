#ifndef QUEUE_H
#define QUEUE_H

#include "ll.h"
#include <stdbool.h>

typedef struct {
    LinkedList* data;
    int count;
} Queue;

Queue* Q_create  (void);
void*  Q_dequeue (Queue* q);
void*  Q_peek    (Queue* q);
void   Q_enqueue (Queue* q, void* obj);
bool   Q_is_empty(Queue* q);
void   Q_free    (Queue* s, void(*item_freer)(void*));

#endif

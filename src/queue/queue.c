#include <stdlib.h>
#include <assert.h>

#include "queue.h"

void* ll_remove_head(LinkedList*);
void* ll_peek_tail(LinkedList*);

Queue* Q_create() {
    Queue* q = malloc(sizeof(Queue));
    q->data = ll_create();
    q->count = 0;
    return q;
}

void* Q_dequeue(Queue* q) {
    assert(!Q_is_empty(q)); // "Queue is empty"
    q->count--;
    return ll_remove_head(q->data);
}

void Q_enqueue(Queue* q, void* obj) {
    ll_prepend(q->data, obj);
    q->count++;
}

void* Q_peek(Queue* q) {
    assert(!Q_is_empty(q)); // "Queue is empty";

    return ll_peek_tail(q->data);
}

bool Q_is_empty(Queue* q) {
    return q->count <= 0;
}


void Q_free(Queue* s, void(*item_freer)(void*)) {
    LinkedListNode* next = s->data->start;

    while (next != NULL) {
        LinkedListNode* current = next;
        next = next->next;

        item_freer(current);
        // ll_free_node(current);
    }

    ll_free(s->data);
}

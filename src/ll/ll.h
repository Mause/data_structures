#ifndef LL_H
#define LL_H

typedef struct LinkedListNode_t {
    void *val;
    struct LinkedListNode_t* next;
} LinkedListNode;

typedef struct {
    LinkedListNode* start;
    LinkedListNode* end;
} LinkedList;

int ll_insert_at_index(LinkedList *list, void *e, int index);
int ll_length(LinkedList* list);
int ll_remove_at_index(LinkedList *list, int index);
LinkedList* ll_create(void);
LinkedListNode* ll_create_node(void* e);
LinkedListNode* ll_get_at_index(LinkedList* list, int index);
void ll_append(LinkedList* ll, void* new_node);
void ll_free(LinkedList* list);
void ll_free_node(LinkedListNode* node);

#endif

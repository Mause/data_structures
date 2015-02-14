#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#include "ll.h"


/*
allocates memory for and initalizes a new LinkedListNode
*/
LinkedListNode* ll_create_node(void* e) {
    LinkedListNode* new_node;

    assert(e);

    new_node = malloc(sizeof *new_node);
    new_node->val = e;
    new_node->next = NULL;
    return new_node;
}


/*
appends the given equation to the specified list
*/
void ll_append(LinkedList* list, void* new_val) {
    LinkedListNode* new_node = ll_create_node(new_val);

    if (list->start == NULL) {
        list->start = new_node;
    } else {

        LinkedListNode* end = list->end;
        end->next = new_node;
    }

    list->end = new_node;
}


/*
traverses the given list, counting the number of nodes
*/
int ll_length(LinkedList* list) {
    int len = 0;
    LinkedListNode* cur_equation = list->start;

    while (cur_equation != NULL) {
        len++;

        cur_equation = cur_equation->next;
    }

    return len;
}


/*
allocates and initalizes a new LinkedList
*/
LinkedList* ll_create(void) {
    LinkedList* list = malloc(sizeof *list);
    list->start = NULL;
    list->end = NULL;
    return list;
}


/*
frees the given node and contained equation
*/
void ll_free_node(LinkedListNode* node) {
    if (node == NULL) return;

    // free_equation(node->val);
    free(node);
}


/*
traverses the given list, freeing each contained node and equation,
before freeing the list itself
*/
void ll_free(LinkedList* list) {
    LinkedListNode* next = list->start;

    while (next != NULL) {
        LinkedListNode* current = next;
        next = next->next;

        ll_free_node(current);
    }

    free(list);
}

#ifndef SET_H
#define SET_H

#include "dict.h"

typedef char* (hasher_function)(void*);

typedef struct {
    hasher_function* hash_function;
    dict* data;
} Set;


Set* Set_create(hasher_function* func);
bool Set_contains(Set* s, void* thing);
void Set_add(Set* s, void* thing);
void Set_free(Set* s, void (*item_freer)(void*));
void Set_remove(Set*s, void* thing);

#endif

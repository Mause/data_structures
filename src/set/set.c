#include <stdlib.h>

#include "set.h"

Set* Set_create(hasher_function hash_function) {
    Set* s = malloc(sizeof(Set));

    s->data = dict_create(5);
    s->hash_function = hash_function;

    return s;
}

bool Set_contains(Set* s, void* thing) {
    char* key = s->hash_function(thing);

    return dict_contains_key(s->data, key);
}


void Set_add(Set* s, void* thing) {
    char* key = s->hash_function(thing);
    dict_set(s->data, key, thing);
}


void Set_free(Set* s, void (*item_freer)(void*)) {
    int i;

    for (i=0; i<s->data->max_size; i++) {
        if (dict_valid_entry(s->data, i)) {
            dict_entry* entry = s->data->entries[i];

            free(entry->key);
            item_freer(entry->value);
        }
    }
    dict_free(s->data);
    free(s);
}

void Set_remove(Set*s, void* thing) {
    char* key = s->hash_function(thing);

    dict_remove(
        s->data,
        key
    );
}

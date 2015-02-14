#include <stdlib.h>
#include <string.h>

#include "arr.h"

LengthedArray* arr_create(void) {
    LengthedArray* arr;

    arr = malloc(sizeof(LengthedArray));
    arr->array = calloc(ARR_INITIAL_SIZE, sizeof(char*));
    arr->size = ARR_INITIAL_SIZE;
    arr->len = 0;

    return arr;
}

void arr_free(LengthedArray* arr) {
    int i;

    for (i=0; i<arr->len; i++) {
        free(arr->array[i]);
    }
    free(arr->array);
    free(arr);
}


void arr_append(LengthedArray* arr, char* value) {
    if (arr->len == arr->size) {
        // is full, we reallocate
        arr->size *= GROWTH_FACTOR;
        arr->array = realloc(
            arr->array,
            arr->size *  sizeof(char*)
        );
    }
    arr->array[arr->len++] = value;
}


LengthedArray* arr_merge(LengthedArray* arr1, LengthedArray* arr2) {
    int i;
    LengthedArray* arr;

    arr = arr_create();

    for (i=0; i<arr1->len; i++) {
        arr_append(arr, arr1->array[i]);
    }

    for (i=0; i<arr2->len; i++) {
        arr_append(arr, arr2->array[i]);
    }

    return arr;
}


char* arr_coalesce(LengthedArray* arr, int length) {
    int i;
    char *start_of_str = calloc((length + 1), sizeof(char)),
         *str = start_of_str;

    for (i=0; i<arr->len; i++) {
        if (i != 0) {
            str = strcat(str, " ");
        }
        str = strcat(str, arr->array[i]);
    }

    return start_of_str;
}


int arr_total_length(LengthedArray* arr) {
    int i, len = 0;

    for (i=0; i<arr->len; i++) {
        len += strlen(arr->array[i]);
    }

    return len;
}

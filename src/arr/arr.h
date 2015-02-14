#ifndef ARR_H
#define ARR_H

#define GROWTH_FACTOR 1.25
#define ARR_INITIAL_SIZE 25

typedef struct {
    char** array;
    int len;
    int size;
} LengthedArray;

LengthedArray* arr_create(void);
void arr_free(LengthedArray* arr);

/* may return pointer to new array if we had to resize */
void arr_append(LengthedArray* arr, char* value);

char* arr_coalesce(LengthedArray* arr, int length);
LengthedArray* arr_merge(LengthedArray* arr1, LengthedArray* arr2);

#endif

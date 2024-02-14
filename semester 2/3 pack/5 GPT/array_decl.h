#ifndef ARRAY_DECL_H
#define ARRAY_DECL_H

#include <stdlib.h>

#define ARRAY_DEFAULT_CAPACITY 4

#define ARRAY_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define ARRAY_MAX(a, b) (((a) > (b)) ? (a) : (b))

#define ARRAY_RESERVE_FACTOR 2

typedef struct NAME {
    int n;      
    TYPE* arr;  
    int capacity; 
} NAME;

void NAME##_init(NAME* vec);

void NAME##_destroy(NAME* vec);

int NAME##_push(NAME* vec, TYPE value);

TYPE NAME##_pop(NAME* vec);

void NAME##_reserve(NAME* vec, int capacity);

void NAME##_resize(NAME* vec, int newCnt, TYPE fill);

void NAME##_insert(NAME* vec, int where, TYPE* arr, int num);

void NAME##_erase(NAME* vec, int where, int num);

#endif

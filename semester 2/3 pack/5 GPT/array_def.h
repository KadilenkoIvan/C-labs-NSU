#include <stdlib.h>
#include <string.h>

#include "array_decl.h"

void NAME##_init(NAME* vec) {
    vec->n = 0;
    vec->capacity = 1;
    vec->arr = malloc(vec->capacity * sizeof(TYPE));
}

void NAME##_destroy(NAME* vec) {
    free(vec->arr);
    vec->n = 0;
    vec->capacity = 0;
    vec->arr = NULL;
}

int NAME##_push(NAME* vec, TYPE value) {
    if (vec->n == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr, vec->capacity * sizeof(TYPE));
    }
    vec->arr[vec->n] = value;
    vec->n++;
    return vec->n - 1;
}

TYPE NAME##_pop(NAME* vec) {
    vec->n--;
    return vec->arr[vec->n];
}

void NAME##_reserve(NAME* vec, int capacity) {
    if (vec->capacity < capacity) {
        vec->capacity = capacity;
        vec->arr = realloc(vec->arr, vec->capacity * sizeof(TYPE));
    }
}

void NAME##_resize(NAME* vec, int newCnt, TYPE fill) {
    if (vec->n < newCnt) {
        NAME##_reserve(vec, newCnt);
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
        vec->n = newCnt;
    }
    else {
        vec->n = newCnt;
        if (vec->capacity >= 2 * vec->n) {
            vec->capacity = vec->n;
            vec->arr = realloc(vec->arr, vec->capacity * sizeof(TYPE));
        }
    }
}

void NAME##_insert(NAME* vec, int where, TYPE* arr, int num) {
    if (num == 0) {
        return;
    }
    NAME##_reserve(vec, vec->n + num);
    memmove(vec->arr + where + num, vec->arr + where, (vec->n - where) * sizeof(TYPE));
    memcpy(vec->arr + where, arr, num * sizeof(TYPE));
    vec->n += num;
}
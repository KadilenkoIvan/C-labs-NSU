#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define MY_STRUCT NAME

//initializes members of [vec] structure for empty array
void DOTA(MY_STRUCT, init) (MY_STRUCT* vec) {
	vec->n = 0;
	vec->cap = 2;
	vec->arr = (TYPE*)calloc(sizeof(TYPE), vec->cap);
}

//makes array [vec] empty and frees its array buffer [vec->arr]
//note: this function can be called many times
void DOTA(MY_STRUCT, destroy) (MY_STRUCT* vec) {
	vec->n = 0;
	vec->cap = 0;
	if (vec->arr != NULL) {
		free(vec->arr);
		vec->arr = NULL;
	}
	else
		return;
}

//adds element [value] to the end of array [vec]
//returns index of the added element
int DOTA(MY_STRUCT, push) (MY_STRUCT* vec, TYPE value) {
	if (vec->arr == NULL)
		DOTA(MY_STRUCT, init)(vec);
	if (vec->n >= vec->cap)
		DOTA(MY_STRUCT, reserve)(vec, vec->cap * 2);
	vec->arr[vec->n] = value;
	++vec->n;
	return vec->n - 1;
}
//removes the last element from array [vec]
//returns removed element
TYPE DOTA(MY_STRUCT, pop) (MY_STRUCT* vec) {
	--vec->n;
	return vec->arr[vec->n];
}

//ensures that array [vec] has enough storage for [capacity] elements
//note: address of elements surely won t change before [vec->n] exceeds capacity
void DOTA(MY_STRUCT, reserve) (MY_STRUCT* vec, int capacity) {
	if (vec->arr == NULL)
		DOTA(MY_STRUCT, init)(vec);
	if (vec->n > capacity)
		capacity = vec->n;
	if (capacity == 0)
		capacity = 1;
	if (vec->cap < capacity) {
		vec->arr = realloc(vec->arr, capacity * sizeof(TYPE));
		vec->cap = capacity;
	}
}

//changes number of elements in array [vec] to [newCnt]
//if the number increases, new elements get value [fill]
//if the number decreases, some elements at the end are removed
void DOTA(MY_STRUCT, resize) (MY_STRUCT* vec, int newCnt, TYPE fill) {
	if (vec->arr == NULL)
		DOTA(MY_STRUCT, init) (vec);
	if (newCnt >= vec->n) {
		if (newCnt >= vec->cap) DOTA(MY_STRUCT, reserve) (vec, newCnt);
		for (int i = vec->n; i < newCnt; ++i)
			vec->arr[i] = fill;
	}
	else
		DOTA(MY_STRUCT, erase)(vec, newCnt, vec->n - newCnt);
	vec->n = newCnt;
}

//inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
//in-between elements [vec->arr[where-1]] and [vec->arr[where]]
//note: the whole array [arr] cannot be part of array [vec] // IGNORE
//[where] may vary from 0 to [vec->n], [num] can also be zero
void DOTA(MY_STRUCT, insert) (MY_STRUCT* vec, int where, TYPE* arr, int num) {
	int newCap = vec->cap + num;
	int dest = where + num;
	if (vec->arr == NULL)
		DOTA(MY_STRUCT, init) (vec);
	if (vec->cap < vec->n + num)
		DOTA(MY_STRUCT, reserve) (vec, newCap);
	memmove(vec->arr + dest, vec->arr + where, sizeof(TYPE) * (vec->n - where));
	memmove(vec->arr + where, arr, sizeof(TYPE) * num);
	vec->n += num;
}

//removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
//all the elements starting from [where+num]-th are shifted left by [num] positions
void DOTA(MY_STRUCT, erase) (MY_STRUCT* vec, int where, int num) {
	int newSize = vec->n - where - num + 1;
	if (vec->arr == NULL)
		DOTA(MY_STRUCT, init) (vec);
	if (where < 0 || num <= 0)
		return;
	memmove(vec->arr + where, vec->arr + where + num, sizeof(TYPE) * newSize);
	vec->n -= num;
}

#undef TYPE
#undef NAME
#undef MY_STRUCT
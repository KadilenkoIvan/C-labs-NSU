#ifndef DOTA
#define _DOTA(a, b) a##_##b
#define DOTA(a, b) _DOTA(a, b)
#endif

#define MY_STRUCT NAME

typedef struct MY_STRUCT {
	int n; //number of elements in array
	TYPE* arr; //points to the array of elements
	int cap; //any other members can be added here
} MY_STRUCT;


//initializes members of [vec] structure for empty array
void DOTA(MY_STRUCT, init) (MY_STRUCT* vec);
//makes array [vec] empty and frees its array buffer [vec->arr]
//note: this function can be called many times
void DOTA(MY_STRUCT, destroy) (MY_STRUCT* vec);
//adds element [value] to the end of array [vec]
//returns index of the added element
int DOTA(MY_STRUCT, push) (MY_STRUCT* vec, TYPE value);
//removes the last element from array [vec]
//returns removed element
TYPE DOTA(MY_STRUCT, pop) (MY_STRUCT* vec);
//ensures that array [vec] has enough storage for [capacity] elements
//note: address of elements surely won t change before [vec->n] exceeds capacity
void DOTA(MY_STRUCT, reserve) (MY_STRUCT* vec, int capacity);
//changes number of elements in array [vec] to [newCnt]
//if the number increases, new elements get value [fill]
//if the number decreases, some elements at the end are removed
void DOTA(MY_STRUCT, resize) (MY_STRUCT* vec, int newCnt, TYPE fill);
//inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
//in-between elements [vec->arr[where-1]] and [vec->arr[where]]
//note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void DOTA(MY_STRUCT, insert) (MY_STRUCT* vec, int where, TYPE* arr, int num);
//removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
//all the elements starting from [where+num]-th are shifted left by [num] positions
void DOTA(MY_STRUCT, erase) (MY_STRUCT* vec, int where, int num);

#undef TYPE
#undef NAME
#undef MY_STRUCT
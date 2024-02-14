#include <stdlib.h>
#include <string.h>



//initializes members of [vec] structure for empty array
void FUNC(NAME, init) (NAME* vec)
{
	vec->n = 0;
	vec->buffer = 10;
	vec->arr = (TYPE*)malloc(sizeof(TYPE) * vec->buffer);
	memset(vec->arr, 0, sizeof(TYPE) * vec->buffer);
}

//makes array [vec] empty and frees its array buffer [vec->arr]
//note: this function can be called many times
void FUNC(NAME, destroy) (NAME* vec)
{
	if (vec->arr != NULL)
	{
		//vec->arr = realloc(vec->arr, sizeof(TYPE));
		free(vec->arr);
		//free(vec->arr);
		vec->arr = NULL;
	}
	vec->n = 0;
	vec->buffer = 0;
}

//adds element [value] to the end of array [vec]
//returns index of the added element
int FUNC(NAME, push) (NAME* vec, TYPE value)
{
	if (vec->arr == NULL)
		FUNC(NAME, init)(vec);
	++vec->n;
	if (vec->buffer < vec->n)
		FUNC(NAME, reserve)(vec, vec->n);
	//vec->arr = (TYPE*)realloc(vec->arr, sizeof(TYPE) * vec->n);
	vec->arr[vec->n - 1] = value;
	int ind = vec->n - 1;
	return ind;
}

//removes the last element from array [vec]
//returns removed element
TYPE FUNC(NAME, pop) (NAME* vec)
{
	--vec->n;
	TYPE value = vec->arr[vec->n];
	return value;
}

//ensures that array [vec] has enough storage for [capacity] elements
//note: address of elements surely won�t change before [vec->n] exceeds capacity
void FUNC(NAME, reserve) (NAME* vec, int capacity)
{
	if (vec->arr == NULL)
		FUNC(NAME, init)(vec);
	if (vec->n > capacity)
		capacity = vec->n;
	//maybe if capasity == 0? = 1?
	if (capacity == 0)
		capacity = 1;
	if (vec->buffer < capacity)
	{
		vec->arr = (TYPE*)realloc(vec->arr, sizeof(TYPE) * capacity);
		vec->buffer = capacity;
	}
	//vec->arr = (TYPE*)realloc(vec->arr, sizeof(TYPE) * (vec->n + capacity));
}

//changes number of elements in array [vec] to [newCnt]
//if the number increases, new elements get value [fill]
//if the number decreases, some elements at the end are removed
void FUNC(NAME, resize) (NAME* vec, int newCnt, TYPE fill)
{
	if (vec->arr == NULL)
		FUNC(NAME, init)(vec);

	//if (vec->n == newCnt)
	//	return;

	if (vec->n > newCnt)
	{
		FUNC(NAME, erase)(vec, newCnt, vec->n - newCnt);
		vec->n = newCnt;
		return;
	}

	if (vec->n <= newCnt)
	{
		int my_n = vec->n;
		if (vec->buffer < newCnt)
			FUNC(NAME, reserve)(vec, newCnt);
		vec->n = newCnt;
		for (int i = my_n; i < vec->n; ++i)
			vec->arr[i] = fill;
		return;
	}
}

//inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
//in-between elements [vec->arr[where-1]] and [vec->arr[where]]
//note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void FUNC(NAME, insert) (NAME* vec, int where, TYPE* arr, int num)
{
	if (where < 0 || num <= 0)
		return;//maybe wrong

	if (vec->arr == NULL)
		FUNC(NAME, init)(vec);

	if (vec->buffer < vec->n + num)
		FUNC(NAME, reserve)(vec, vec->buffer + num); //maybe vec->n + num + 1?

	memmove(vec->arr + num + where, vec->arr + where, sizeof(TYPE) * (vec->n - where));
	memmove(vec->arr + where, arr, sizeof(TYPE) * num);
	vec->n += num;
}

//removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
//all the elements starting from [where+num]-th are shifted left by [num] positions
void FUNC(NAME, erase) (NAME* vec, int where, int num)
{
	if (where < 0 || num <= 0)
		return;//maybe wrong

	if (vec->arr == NULL)
		FUNC(NAME, init)(vec);

	memmove(vec->arr + where, vec->arr + where + num, sizeof(TYPE) * (vec->n - where - num + 1));
	vec->n -= num;
}
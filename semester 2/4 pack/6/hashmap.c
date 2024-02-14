#include <stdint.h>
#include "hashmap.h"

//pointer to key or value (untyped)
typedef const void* cpvoid;

//returns 1 if and only if two keys pointed by [a] and [b] are equal
//returns 0 otherwise
typedef int (*EqualFunc)(cpvoid a, cpvoid b);

//returns 32-bit hash of a key pointed by [key]
typedef uint32_t(*HashFunc)(cpvoid key);

//creates and returns new hash table with:
// [ef] –- function which compares keys for equality
// [hf] –- function which produces a hash for a key
// [size] –- prescribed size/capacity of the hash table (number of cells)
HashMap HM_Init(EqualFunc ef, HashFunc hf, int size)
{
	exit (0);
}

//frees memory of hash map [self]
//note: called exactly once for every hash map created by HM_Init
void HM_Destroy(HashMap* self)
{
	exit(0);
}

//returns value corresponding to the specified key [key] in hash map [self]
//if [key] is not present in the map, then returns NULL
cpvoid HM_Get(const HashMap* self, cpvoid key)
{
	exit(0);
}

//sets value [value] for the key [key] in hash map [self]
//if [self] already has some value for [key], it is overwritten
void HM_Set(HashMap* self, cpvoid key, cpvoid value)
{
	exit(0);
}
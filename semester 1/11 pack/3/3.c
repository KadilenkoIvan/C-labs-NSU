#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct hash_s
{
	uint64_t value;
	char check;
	int key;
}hash;

uint64_t hash_func(uint64_t k)
{
	const uint64_t A = 2654435769;     //округлённое до целого phi * 2^32
	uint64_t x = (A * k);              //умножаем по модулю 2^32 (за счёт переполнения)
	return (x >> 4);                   //берём старшие s битов --- получаем номер ячейки
}

uint64_t a = 0, b = 0, c = 0, m = 0;

uint64_t func(uint64_t s)
{
	return (s * s * a + s * b + c) % m;
}

int main()
{
	scanf("%llu%llu%llu%llu", &m, &a, &b, &c);
	uint64_t s = 1;
	/*for (int i = 0; i < 1191; ++i)
	{
		if(i > 1179)
			printf("%d) %llu\n",i, s);
		s = func(s);
	}
	s = 1;*/
	hash* hash_arr = malloc(sizeof(hash) * 4000001);
	memset(hash_arr, 0, sizeof(hash) * 4000001);
	uint64_t ind = 0, col_ind = 0;

	for(int i = 0; 1; ++i)
	{
		ind = hash_func(s) % 2000001;
		if (hash_arr[ind].check == 1)
		{
			col_ind = ind;
			while ((hash_arr[col_ind].check == 1) && (hash_arr[col_ind].value != s))
			{
				col_ind = col_ind + 1;
			}
			if (hash_arr[col_ind].value == s && hash_arr[col_ind].check == 1)
			{
				//printf("=> %d %d\n", hash_arr[col_ind].value, s);
				printf("%d %d", hash_arr[col_ind].key, i);
				exit(0);
			}
			hash_arr[col_ind].value = s;
			hash_arr[col_ind].check = 1;
			hash_arr[col_ind].key = i;
			s = func(s);
			continue;
		}

		hash_arr[ind].value = s;
		hash_arr[ind].check = 1;
		hash_arr[ind].key = i;
		s = func(s);
	}
}
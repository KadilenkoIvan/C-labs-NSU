#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct hash_s
{
    int value;
    int check;
}hash;

uint32_t hash_func(uint32_t k)
{
    const uint32_t A = 2654435769;     //округлённое до целого phi * 2^32
    uint32_t x = (A * k);              //умножаем по модулю 2^32 (за счёт переполнения)
    return (x >> 4);                   //берём старшие s битов --- получаем номер ячейки
}

uint32_t hash_func1(uint32_t k)
{
    uint32_t x = (98 * k + 4324) % 1305012097;
}

int main()
{
    FILE* in = fopen("input.bin", "rb");
    FILE* out = fopen("output.bin", "wb");

    int n = 0;
    fread(&n, sizeof(int), 1, in);

    int* arr = malloc(sizeof(int) * n);
    fread(arr, sizeof(int), n, in);

    hash* hash_arr = malloc(sizeof(hash) * (5 * n));
    memset(hash_arr, 0, sizeof(hash) * 5 * n);
    int* arr_ind = malloc(sizeof(int) * n);

    int ind = 0, j = 0, col_ind = 0;
    for (int i = 0; i < n; ++i)
    {
        ind = hash_func(arr[i]) % n;
        if (hash_arr[ind].check == 1)
        {
            col_ind = ind;
            while ((hash_arr[col_ind].check == 1) && (hash_arr[col_ind].value != arr[i]))
            {
                col_ind = col_ind + 1;
            }
            if (hash_arr[col_ind].value == arr[i] && hash_arr[col_ind].check == 1)
            {
                continue;
            }
            hash_arr[col_ind].value = arr[i];
            hash_arr[col_ind].check = 1;
            arr_ind[j] = col_ind;
            ++j;
            continue;
        }

        hash_arr[ind].value = arr[i];
        hash_arr[ind].check = 1;
        arr_ind[j] = ind;
        ++j;
    }

    fwrite(&j, sizeof(int), 1, out);
    for (int i = 0; i < j; ++i)
    {
        fwrite(&hash_arr[arr_ind[i]].value, sizeof(int), 1, out);
    }
}
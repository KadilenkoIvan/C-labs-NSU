#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

//структура, в которой хранится разложение на простые множители
typedef struct Factors
{
    int k; //сколько различных простых в разложении
    int primes[32]; //различные простые в порядке возрастания
    int powers[32]; //в какие степени надо эти простые возводить
} Factors;

void Factorize(int X, Factors* res);

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int m = 0;
    fscanf(in, "%d", &m);

    Factors res;
    int a = 0;

    for (int i = 0; i < m; ++i)
    {
        res.k = 0;
        memset(res.primes, 0, sizeof(int) * 32);
        memset(res.powers, 0, sizeof(int) * 32);
        fscanf(in, "%d", &a);
        Factorize(a, &res);
        if (res.k == 0)
        {
            fprintf(out, "%d = 1\n", a);
            continue;
        }
        fprintf(out, "%d = ", a);
        fprintf(out, "%d^%d", res.primes[0], res.powers[0]);
        for (int j = 1; j < res.k; ++j)
        {
            fprintf(out, " * %d^%d", res.primes[j], res.powers[j]);
        }
        fprintf(out, "\n");
    }
}

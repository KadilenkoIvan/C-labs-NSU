#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

long long operation(long long a, long long b, char* str)
{
    if (strcmp("add", str) == 0)
    {
        return a + b;
    }
    else if (strcmp("sub", str) == 0)
    {
        return a - b;
    }
    else if (strcmp("mul", str) == 0)
    {
        return a * b;
    }
}

int main(int argc, char** argv)
{
    if (argc == 1)// возможно не только 0 параметров
    {
        fprintf(stderr, "No parameters specified.");
        return 13;
    }

    long long a = 0, b = 0, res = 0;
    if (argv[1][0] == '-' && argv[1][1] == 'm')
    {
        long long m = 0;
        sscanf(argv[2], "%lld", &m);

        sscanf(argv[4], "%lld", &a);
        sscanf(argv[5], "%lld", &b);

        res = ((operation(a, b, argv[3]) % m) + m) % m;
        printf("%lld", res);
        return 0;
    }

    sscanf(argv[2], "%lld", &a);
    sscanf(argv[3], "%lld", &b);

    res = operation(a, b, argv[1]);

    if (argc == 6 && argv[4][0] == '-' && argv[4][1] == 'm')
    {
        long long m = 0;
        sscanf(argv[5], "%lld", &m);
        res = ((res % m) + m) % m;
    }

    printf("%lld", res);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 0, p = 0, q = 0, j = 0;
    double num1 = 0;
    unsigned long long num2 = 0;
    unsigned long long res;
    char str[100];
    char garbage[4];

    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", &str);
        sscanf(str, "%d%c%d", &p, &str[0], &q);

        num1 = (double)p / (double)q;

        scanf("%s", &str);
        scanf("%llx", &num2);

        res = (*((long long*)&num1)) ^ num2;
        printf("%0.15g\n", *(double*) &res);
    }
}
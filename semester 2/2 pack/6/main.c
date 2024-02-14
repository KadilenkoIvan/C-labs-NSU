#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

double Function(double x);

int main()//апроксимация
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    double d = 0.0000001;
    int n = 0;
    fscanf(in, "%d", &n);

    double num = 0, ans = 0;
    for (int i = 0; i < n; ++i)//func(x) / x + x
    {
        ans = 0;
        fscanf(in, "%lf", &num);
        if (num + d <= 1)
            ans = (Function(num + d) - Function(num)) / d;
        else
            ans = (Function(num) - Function(num-d)) / d;
        fprintf(out, "%.15lf\n", ans);
    }

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

double func(double c0, double c1, double c2, double c3, double t, double l)
{
    return c0 + c1 * (t - l) + pow(c2 * (t - l), 2) + pow(c3 * (t - l), 3);
}

double cord_calc(double c0, double c1, double c2, double c3, double l, double r)
{
    double ans = 0;
    double sdvig = (r - l) / 1000; //maybe need more than 1000
    for (double t = l + sdvig; t < r; t += sdvig)
    {

    }
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    fscanf(in, "%d", &n);
    double l = 0, r = 0, c0 = 0, c1 = 0, c2 = 0, c3 = 0, x = 0, y = 0, z = 0;
    for (int i = 0; i < n; ++i)
    {
        fscanf(in, "%lf %lf", &l, &r);
        fscanf(in, "%lf %lf %lf %lf", &c0, &c1, &c2, &c3);
        //x = func(c0, c1, c2, c3, r, l);

    }
}
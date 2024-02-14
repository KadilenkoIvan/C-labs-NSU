#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct evclid_s
{
    int ans;
    int x;
    int y;
}evclid;

evclid gcd(int a, int b, evclid num)
{
    if (b == 0)
    {
        num.ans = a;
        num.x = 1;
        num.y = 0;
        return num;
    }

    num = gcd(b, a % b, num);

    int buf = num.x;
    num.x = num.y;
    num.y = buf - num.y * (a / b);
    return num;
}

int main()
{
    int a = 0;//модуль
    int b = 0; //число
    int t = 0;
    scanf("%d", &t);

    evclid num;

    for (int i = 0; i < t; ++i)
    {
        scanf("%d%d", &a, &b);
        num.ans = 0;
        num.x = 0;
        num.y = 0;
        num = gcd(a, b, num);

        printf("%d\n", num.ans);
    }

    return 0;
}
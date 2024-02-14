#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct LongNum_s
{
    int len; //сколько цифр в числе
    int arr[10000]; //массив десятичных цифр числа
} LongNum;

int entry_in_longum_str(char* num, LongNum* Num)
{
    int n = strlen(num), count = 0;
    for (int i = 0; num[n - i - 1] == '0'; ++i)
    {
        ++count;
    }

    n -= count;

    for (int i = 0; i < n; ++i)
    {
        Num[0].arr[i] = (int)(num[n - i - 1] - '0');
    }
    Num[0].len = n;

    return count;
}

int take_from_longnum(LongNum Num)
{
    int num = 0;
    for (int i = 0; i <= Num.len; ++i)
    {
        num += Num.arr[i] * pow(10, i);
    }
    return num;
}

void entry_in_longum(int num, LongNum* Num)
{
    int i = 0, len = 0;
    do
    {
        Num[0].arr[i] = num % 10;
        num = num / 10;
        ++len;
        ++i;
    } while (num != 0);
    Num[0].len = len;
}

LongNum plus(LongNum Num_c, LongNum Num_p)
{
    int n = max(Num_p.len, Num_c.len);
    for (int i = 0; i < n; ++i)
    {
        Num_c.arr[i] += Num_p.arr[i];
        if (Num_c.arr[i] >= 10)
        {
            Num_c.arr[i + 1] += 1;
            Num_c.arr[i] -= 10;
        }
        if (Num_c.arr[Num_c.len] != 0)
            ++Num_c.len;
    }
    return Num_c;
}

int longnum_lenth(LongNum Num)
{
    int i;
    int n = sizeof(Num.arr) / sizeof(int) - 1;

    for (i = 0; Num.arr[n - i] == 0; ++i);

    return n - i + 1;
}

LongNum multiply_ten(int tens, LongNum Num)
{
    if (tens == 0)
        return Num;
    for (int i = 0; i < Num.len; ++i)
    {
        Num.arr[Num.len - 1 + tens - i] = Num.arr[Num.len - 1 - i];
        Num.arr[Num.len - 1 - i] = 0;
    }
    Num.len += tens;
    return Num;
}

LongNum multiply(char* num1, char* num2)
{
    if (strlen(num1) > strlen(num2))
        return multiply(num2, num1);

    LongNum Num_c;
    LongNum Num_p;

    if (num1[0] == '0' || num2[0] == '0')
    {
        Num_p.len = 0;
        return Num_p;
    }

    memset(Num_c.arr, 0, 10000);
    memset(Num_p.arr, 0, 10000);

    int ten1 = entry_in_longum_str(num1, &Num_c);
    int ten2 = entry_in_longum_str(num2, &Num_p);
    ten1 += ten2;
}

void print(LongNum Num)
{
    if (Num.len <= 0)
        printf("%d", 0);
    for (int i = 1; i <= Num.len; ++i)
    {
        printf("%d", Num.arr[Num.len - i]);
    }
    printf("\n");
}

int main()
{
    char n[2001];
    char m[2001];
    scanf("%s%s", &n, &m);
    LongNum Num1;
    LongNum Num2;

    memset(Num1.arr, 0, 10000);
    memset(Num2.arr, 0, 10000);

    int ten1 = entry_in_longum_str(n, &Num1);
    int ten2 = entry_in_longum_str(m, &Num2);
    ten1 *= ten2;

    print(multiply(n, m));
}
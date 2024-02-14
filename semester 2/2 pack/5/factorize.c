#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct Factors
{
    int k; //������� ��������� ������� � ����������
    int primes[32]; //��������� ������� � ������� �����������
    int powers[32]; //� ����� ������� ���� ��� ������� ���������
} Factors;

//�������, ������� ������� ���������� ����� X � ���������� ��� � ��������� res
void Factorize(int X, Factors* res){    int pr = 0;    int po = 0;    int x = X;    int i = 0, k = 0;    for (i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            res->primes[pr] = i;
            for (k = 0; x % i == 0; k++)
            {
                x = x / i;
            }
            res->powers[pr] = k;
            ++pr;
        }
    }

    if (x > 1)
    {
        res->primes[pr] = x;
        res->powers[pr] = 1;
        ++pr;
    }    res->k = pr;    return 0;}
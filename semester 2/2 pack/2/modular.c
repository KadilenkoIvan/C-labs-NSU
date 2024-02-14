#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "modular.h"

int MOD;

int gcd(int a, int b, int* x, int* y)//maybe long long
{
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int ans = gcd((b % a), a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return ans;
}

int pnorm(int a)
{
	return ((a % MOD) + MOD) % MOD;
}

int padd(int a, int b)
{
	return pnorm(pnorm(a) + pnorm(b));
}

int psub(int a, int b)
{
	return pnorm(pnorm(a) - pnorm(b));
}

int pmul(int a, int b)
{
	return (((long long)pnorm(a) * (long long)pnorm(b)) % MOD);
}

int pdiv(int a, int b)
{
	int x = 0, y = 0;
	gcd(pnorm(b), MOD, &x, &y);
	x = (((x % MOD) + MOD) % MOD);
	return (((long long)pnorm(a) * (long long)pnorm(x)) % MOD);
}
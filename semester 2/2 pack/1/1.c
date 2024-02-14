#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

long long inv(long long a, long long b, long long* x, long long* y, long long m) {
	if (b == 0) 
	{
		*x = 1; *y = 0;
		return;
	}
	inv(b, a % b, x, y, m);
	long long x1 = *x;
	*x = *y;
	*y = (x1)-(*y) * (a / b);
	return (*x) >= 0 ? (*x) : (*x) + m;
}
int main() 
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k;
	long long P = 1;
	scanf("%d", &k);
	
	int* M = (int*)malloc(sizeof(int) * k);
	int* A = (int*)malloc(sizeof(int) * k);
	
	for (int i = 0; i < k; i++) 
	{
		scanf("%d", &M[i]);
		P *= M[i];
	}
	for (int i = 0; i < k; i++) 
	{
		scanf("%d", &A[i]);
	}

	long long X = 0;
	for (int i = 0; i < k; i++) 
	{
		long long PdMi = P / M[i]; //M
		long long x, y;
		long long invP = inv(PdMi % M[i], M[i], &x, &y, M[i]);
		X += ((invP * A[i]) % M[i]) * PdMi;
	}
	X %= P;
	printf("%lld", X);
	return 0;
}
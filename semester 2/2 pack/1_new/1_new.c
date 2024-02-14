#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

long long gcd(long long a, long long b, long long* x, long long* y)
{
	if (a == 0) 
	{
		*x = 0;
		*y = 1;
		return b;
	}
	long long x1, y1;
	long long ans = gcd((b % a), a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return ans;
}

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	long long n = 0;
	fscanf(in, "%lld", &n);

	long long* m_arr = malloc(sizeof(long long) * (n + 1));
	long long* a_arr = malloc(sizeof(long long) * (n + 1));

	unsigned long long mod_pr = 1;
	unsigned long long ans = 0;
	for (int i = 0; i < n; ++i)
	{
		fscanf(in, "%lld", &m_arr[i]);
		mod_pr = mod_pr * m_arr[i];
	}

	for (int i = 0; i < n; ++i)
	{
		fscanf(in, "%lld", &a_arr[i]);
	}

	long long M = 0, M1 = 0, x = 0, y = 0, ch = 0;
	for (int i = 0; i < n; ++i)
	{
		M = mod_pr / m_arr[i];
		ch = gcd(M % m_arr[i], m_arr[i], &x, &y);
		M1 = (x + m_arr[i]) % m_arr[i];
		ans += ((M1 * a_arr[i]) % m_arr[i]) * M;
	}
	ans = ans % mod_pr;
	fprintf(out, "%lld", (ans + mod_pr) % mod_pr);
}

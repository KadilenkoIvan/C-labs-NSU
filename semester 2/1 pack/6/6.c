#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define m 1000000007

typedef struct evclid_s
{
	int ans;
	int x;
	int y;
}evclid;

evclid gcd(int a, int b, evclid num)
{
	if (b <= 0)
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
	int t = 0;
	scanf("%d", &t);

	unsigned long long* fact = malloc(sizeof(unsigned long long) * 1000001);
	memset(fact, 0, sizeof(unsigned long long) * 1000001);
	fact[0] = 1;
	fact[1] = 1;
	for (unsigned long long i = 2; i < 1000001; ++i)
	{
		fact[i] = (fact[i - 1] * i) % m;
	}

	evclid num;
	num.ans = 0;
	num.x = 0;
	num.y = 0;
	
	unsigned long long ans = 0, f = 0, s = 0, th = 0, pr = 0;
	int n = 0, k = 0;
	for (int i = 0; i < t; ++i)
	{
		scanf("%d%d", &n, &k);

		ans = (fact[n] * (gcd(m, ((fact[k] * fact[n - k]) % m), num).y + m) % m) % m;

		printf("%llu\n", ans);
	}
	return 0;
}

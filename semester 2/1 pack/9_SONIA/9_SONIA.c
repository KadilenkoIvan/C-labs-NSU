#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

long long bolmod = 2;

void swap(long long* a, long long* b, long long q) {
	long long k = *a;
	*a = *b;
	*b = k - *b * q;
}

int eva(long long* a, long long* m) {
	long long q = 0, a1 = *a, m1 = *m, x = 1, x1 = 0, y = 0, y1 = 1;
	while (m1 != 0) {
		q = a1 / m1;
		swap(&a1, &m1, q);
		swap(&x, &x1, q);
		swap(&y, &y1, q);
	}
	if (*a * x + *m * y == 1) {
		while (x < 0) {
			x = x + *m;
		}
		return x;
	}
	return -1;
}

long long padd(long long a, long long b, long long m)
{
	long long res = ((a % m) + (b % m)) % m;
	return (res >= 0 ? res : res + m);
}

long long psub(long long a, long long b, long long m)
{
	long long res = ((a % m) - (b % m)) % m;
	return (res >= 0 ? res : res + m);
}

long long pmul(long long a, long long b, long long m)
{
	long long res = ((a % m) * (b % m)) % m;
	return (res >= 0 ? res : res + m);
}

long long pstep(long long a, long long n, long long m)
{
	long long res = 1;
	for (long long i = 0; i < n; i++)
	{
		res = pmul(res, a, m);
	}
	return res;
}

long long pdiv(long long a, long long b, long long m)
{
	long long res = pmul(a, eva(&b, &m), m);
	return (res >= 0 ? res : res + m);
}

long long proverka(long long** arr, long long n, long long str) {
	for (long long i = 0; i < n + 1; i++) {
		if (arr[str][i] != 0) return i;
	}
	return n + 1;
}

void swapp(long long** arr, long long t, long long f, long long n) {
	long long assm;
	for (int i = 0; i < n + 1; i++) {
		assm = arr[t][i];
		arr[t][i] = arr[f][i];
		arr[f][i] = assm;
	}
}

void stepvid(long long** arr, long long k, long long n, long long mod) {
	long long h = 0;
	for (int i = 0; i < n + 1; i++) {
		for (int j = h; j < k; j++) {
			if (arr[j][i] == 0) continue;
			else {
				swapp(arr, h, j, n);
				h++;
				for (int y = h; y < k; y++) {
					long long q = proverka(arr, n, h - 1);
					long long qr = pdiv(arr[y][q], arr[h - 1][q], mod);

					for (long long m = 0; m < n + 1; m++)
						arr[y][m] = psub(arr[y][m], pmul(arr[h - 1][m], qr, mod), mod);
				}
				break;
			}
		}
	}
}

long long* reshenia(long long** arr, long long k, long long n, long long mod, long long* kost) {
	long long puststr = 0, flag = 0;

	/*for (long long i = k - 1; i >= 0; i--)
	{
		if (proverka(arr, n, i) == n + 1) puststr++;
		else
		{
			if (proverka(arr, n, i) == n)
			{
				flag = 1;
				break;
			}
		}
	}*/

	/*if (flag || pstep(mod, psub(n, psub(k, puststr, bolmod), bolmod), bolmod) > 1)
	{
		long long* res = (long long*)malloc(2 * sizeof(long long));
		res[0] = 0;
		if (flag == 1)
		{
			res[1] = 0;
			*kost = 0;
		}
		else
		{
			res[1] = pstep(mod, psub(n, psub(k, puststr, bolmod), bolmod), bolmod);
			*kost = 0;
		}
		return res;
	}*/
	 
	//long long *res = malloc((n + 1) * sizeof(long long));


	long long* res = (long long*)malloc((n + 2) * sizeof(long long));
	//res[0] = 1;
	for (long long i = k - 1 - puststr; i >= 0; i--)
	{
		long long sum = 0;
		long long first = proverka(arr, n, i);
		for (long long j = first + 1; j < n + 1; j++)
		{
			if (j != n)
				sum = psub(sum, pmul(arr[i][j], res[j + 1], mod), mod);
			else
				sum = padd(sum, pmul(arr[i][j], 1, mod), mod);
		}
		res[i] = pdiv(sum, arr[i][i], mod);
	}
	//res[0] = n;
	*kost = 1;
	return res;
}

long long pnorm(long long chislo) {
	chislo %= 2;
	while (chislo < 0) {
		chislo = chislo + 2;
	}
	return (chislo);
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	FILE* in = fopen("input.txt","r");
	FILE* out = fopen("output.txt","w");

	long long** arr;
	//long long* res;
	int n, nou;
	fscanf(in, "%d\n", &n);
	nou = n;
	arr = (long long**)malloc(sizeof(long long*) * (n*n + 1));
	//res = (long long*)malloc(sizeof(long long) * (n*n));
	//for (int i = 0; i < n*n; i++) res[i] = 0;
	for (int i = 0; i < n*n + 1; i++) {
		arr[i] = (long long*)malloc(sizeof(long long) * (n*n + 1));
		memset(arr[i], 0, sizeof(long long) * (n * n + 1));
	}
	int t = 0;
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			if (i == j || ((i % n + 1) < n && j == (i + 1)) || ((i + n) < (n * n) && (i + n) == j) || ((i % n - 1) >= 0 && (i - 1) == j) || ((i - n) >= 0 && (i - n) == j)) {
				t = 1;
			}
			arr[i][j] = t;
			t = 0;
		}
	}
	char p;
	for (int t = 0; t < n; t++) {
		for (int j = 0; j < n; j++) {
			fscanf(in, "%c", &p);
			if (p == '*')arr[t*n+j][n * n] = 1;
			else arr[t*n+j][n * n] = 0;
		}
		fscanf(in, "\n");
	}
	n*= n;
	for (int t = 0; t < n; t++) {
		for (int j = 0; j < n+1; j++) {
			fprintf(out, "%d ", arr[t][j]);
		}
		fprintf(out, "\n");
	}
	fprintf(out, "\n");
	long long kost = 0;
	stepvid(arr, n, n, 2);

	for (int i = 0; i < n ; ++i)
	{
		for (int j = 0; j < n + 1; ++j)
		{
			printf("%lld ", arr[i][j]);
		}
		printf("\n");
	}

	long long* res = reshenia(arr, n, n, 2, &kost);
	int sum = 0;
	
	for (int i = 0; i < n; ++i)
	{
		printf("%lld ", res[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
	}
	
	for (int i = 0; i < n; i++) 
		if (pnorm(res[i]) == 1) sum++;
			fprintf(out, "%d\n", sum);
	//for (int i = 0; i < nou; i++)
	//	for (int j = 0; j < nou; j++)
	//		if (pnorm(res[i * nou + j]) == 1)
	//			printf("%d %d\n", i + 1, j + 1);

	for (long long i = 0; i < n; i++)
	{
		fprintf(out, "%d %lld\n", i, res[i]);
	}
}


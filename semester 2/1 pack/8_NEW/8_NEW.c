#define PRISVOIT =
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#define OPEN {
#define VVOD fscanf
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#define CLOSE }
#define JUSTICE if
#include <string.h>
#define BOLSHOI long 
#define VIVOD fprintf
#define BUBLIK for
#include <limits.h>
#include <time.h>

FILE* in;
FILE* out;

void swap(BOLSHOI BOLSHOI* a, BOLSHOI BOLSHOI* b)
OPEN
	BOLSHOI BOLSHOI* buf PRISVOIT a;
	a PRISVOIT b;
	b PRISVOIT buf;
CLOSE

BOLSHOI BOLSHOI fast_pow(BOLSHOI BOLSHOI num, BOLSHOI BOLSHOI degree, BOLSHOI BOLSHOI module)
OPEN
	BOLSHOI BOLSHOI ans PRISVOIT 1;
	while (degree > 0)
	OPEN
		JUSTICE (degree % 2 == 1)
			ans PRISVOIT (ans * num) % module;
		num PRISVOIT (num * num) % module;
		degree PRISVOIT degree / 2;
	CLOSE
	return ans;
CLOSE

int main()
OPEN
	in PRISVOIT fopen("input.txt", "r");
	out PRISVOIT fopen("output.txt", "w");

	int n PRISVOIT 0, k PRISVOIT 0;
	BOLSHOI BOLSHOI p PRISVOIT 0;
	VVOD(in, "%d %d %lld", &n, &k, &p);
	
	BOLSHOI BOLSHOI** matrix PRISVOIT malloc(sizeof(BOLSHOI BOLSHOI*) * k);
	BUBLIK (int i PRISVOIT 0; i < k; ++i)
	OPEN
		matrix[i] PRISVOIT malloc(sizeof(BOLSHOI BOLSHOI) * (n + 1));//maybe (n + 1)
		BUBLIK (int j PRISVOIT 0; j < n + 1; ++j)
		OPEN
			VVOD(in, "%lld", &matrix[i][j]);
			//printf("%lld ", matrix[i][j]);
		CLOSE
		//printf("\n");
	CLOSE

	int count PRISVOIT 0, station PRISVOIT 0;
	BUBLIK (int i PRISVOIT 0; i < k; ++i)//что-то тут или выше
	OPEN
		JUSTICE (matrix[i][count] == 0)
		OPEN
			station PRISVOIT 1;
			while (station && count <= n)
			OPEN
				JUSTICE (matrix[i][count] == 0)
				OPEN
					BUBLIK (int j PRISVOIT i + 1; j < k; ++j)
					OPEN
						JUSTICE (matrix[j][count] != 0)
						OPEN
							BOLSHOI BOLSHOI* buf PRISVOIT matrix[i];
							matrix[i] PRISVOIT matrix[j];
							matrix[j] PRISVOIT buf;
							station PRISVOIT 0;
							break;
						CLOSE
					CLOSE
					JUSTICE (station)
						++count;
				CLOSE
				else
					break;
			CLOSE
		CLOSE

		JUSTICE (count > n)
			break;

		BUBLIK (int j PRISVOIT i + 1; j < k; ++j)
		OPEN
			BOLSHOI BOLSHOI qwerty PRISVOIT fast_pow(matrix[i][count], p - 2, p);
			BOLSHOI BOLSHOI asdfgh PRISVOIT matrix[j][count];
			BOLSHOI BOLSHOI zxcvbn PRISVOIT (qwerty * asdfgh) % p;
			BUBLIK (int q PRISVOIT 0; q < n + 1; ++q)
			OPEN
				matrix[j][q] PRISVOIT (matrix[j][q] - matrix[i][q] * zxcvbn + p * p) % p;//maybe p * p
			CLOSE
		CLOSE
		++count;
	CLOSE

	BUBLIK (int i PRISVOIT 0; i < k; ++i)
	OPEN
		BUBLIK (int j PRISVOIT i + 1; j < k; ++j)
		OPEN
			station PRISVOIT 1;
			BUBLIK (int q PRISVOIT 0; q < n + 1; ++q)
			OPEN
				JUSTICE (matrix[i][q] != matrix[j][q])
				OPEN
					station PRISVOIT 0;
					break;
				CLOSE
			CLOSE
			JUSTICE (station)
			OPEN
				BUBLIK (int q PRISVOIT 0; q < n + 1; ++q)
				OPEN
					matrix[j][q] PRISVOIT 0;
				CLOSE
			CLOSE
		CLOSE
	CLOSE

	int s PRISVOIT 0;
	BUBLIK (int i PRISVOIT 0; i < k; ++i)
	OPEN
		station PRISVOIT 1;
		BUBLIK (int j PRISVOIT 0; j < n + 1; ++j)
		OPEN
			JUSTICE (matrix[i][j] != 0)
			OPEN
				JUSTICE (j == n)
				OPEN
					VIVOD(out, "0");
					exit(0);
				CLOSE
				station PRISVOIT 0;
				break;
			CLOSE
		CLOSE
		JUSTICE (station)
			++s;
	CLOSE

	BOLSHOI BOLSHOI solution_count PRISVOIT fast_pow(p, n - (k - s), 1000000007);//m PRISVOIT 1000000007
	JUSTICE (solution_count == 1)
	OPEN
		VIVOD(out, "1\n");
		BOLSHOI BOLSHOI* ans PRISVOIT malloc(sizeof(BOLSHOI BOLSHOI) * n);
		int c PRISVOIT n - 1;
		BUBLIK (int i PRISVOIT k - 1; i >= 0; --i)
		OPEN
			BUBLIK (int j PRISVOIT n - 1; j >= i; --j)
			OPEN
				JUSTICE (i == j)
				OPEN
					ans[c] PRISVOIT (matrix[i][n] * (fast_pow(matrix[i][j], p - 2, p))) % p;
					--c;
				CLOSE
				else
					matrix[i][n] PRISVOIT (matrix[i][n] - matrix[i][j] * ans[j] + p * p) % p;//maybe p * p
			CLOSE
		CLOSE
		BUBLIK (int i PRISVOIT 0; i < n; ++i)
			VIVOD(out, "%lld\n", ans[i]);
	CLOSE
	else
	OPEN
		VIVOD(out, "%lld", solution_count);
	CLOSE
CLOSE
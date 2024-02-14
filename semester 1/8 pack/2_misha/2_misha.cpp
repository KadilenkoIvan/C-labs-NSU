#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
union name {
	int n;
	struct {
		int8_t u1;
		int8_t u2;
		int8_t u3;
		int8_t u4;
	};
};
int main() {
	FILE* f1 = fopen("input.txt", "rb");
	FILE* f2 = fopen("output.txt", "wb");
	int sum = 0;
	int col;
	int arr[10001];
	fread(&col, 4, 1, f1);
	//fread(arr, sizeof(int), col, f1);
	if (0 < col && col < 10001) {
		fread(arr, sizeof(int), col, f1);
		for (int j = 0; j < col; j++)
		{
			sum = sum + arr[j];
		}
		fwrite(&sum, sizeof(int), 1, f2);
	}
	else {
		union name cole;
		int k, h;
		cole.n = col;
		k = cole.u1;
		cole.u1 = cole.u4;
		cole.u4 = k;
		h = cole.u3;
		cole.u3 = cole.u2;
		cole.u2 = h;
		col = cole.n;

		fread(arr, sizeof(int), col, f1);

		for (int i = 0; i < col; i++)
		{

			int b;
			int c;
			union name a;
			a.n = arr[i];
			b = a.u1;
			a.u1 = a.u4;
			a.u4 = b;
			c = a.u3;
			a.u3 = a.u2;
			a.u2 = c;

			sum = sum + a.n;
		}
		union name co;
		int p, l;
		co.n = sum;
		p = co.u1;
		co.u1 = co.u4;
		co.u4 = p;
		l = co.u3;
		co.u3 = co.u2;
		co.u2 = l;
		sum = co.n;//!

		fwrite(&sum, sizeof(sum), 1, f2);
	}

}
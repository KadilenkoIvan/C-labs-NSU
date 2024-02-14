#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

#define M 1000000007

FILE* in;
FILE* out;

long long power(long long x, long long p, long long m) {
    long long result = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            result = (result * x) % m;
        }
        x = (x * x) % m;
        p /= 2;
    }
    return result;
}

int main() {
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n, k;
    long long p;
    fscanf(in, "%d%d%lld", &n, &k, &p);
    long long** matrix = (long long**)malloc(k * sizeof(long long*));
    for (int i = 0; i < k; i++) {
        matrix[i] = (long long*)malloc((n + 1) * sizeof(long long));
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= n; j++) {
            fscanf(in, "%lld", &matrix[i][j]);
        }
    }

    int cnt = 0;
    for (int j = 0; j < k; j++) {
        if (matrix[j][cnt] == 0) {
            int st = 1;
            while (st && cnt <= n) {
                if (matrix[j][cnt] == 0) {
                    for (int l = j + 1; l < k; l++) {
                        if (matrix[l][cnt] != 0) {
                            long long* tmp = matrix[l];
                            matrix[l] = matrix[j];
                            matrix[j] = tmp;
                            st = 0;
                            break;
                        }
                    }
                    if (st) {
                        cnt++;
                    }
                }
                else {
                    break;
                }
            }
        }
        if (cnt > n) {
            break;
        }
        for (int i = j + 1; i < k; i++) {
            long long inv_a = power(matrix[j][cnt], p - 2, p);
            long long b = matrix[i][cnt];
            long long c = (inv_a * b) % p;
            for (int f = 0; f <= n; f++) {
                matrix[i][f] = (matrix[i][f] - matrix[j][f] * c + p * p) % p;
            }
        }
        cnt++;
    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            printf("%lld ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int zero_s = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int st = 1;
            for (int l = 0; l <= n; l++) {
                if (matrix[i][l] != matrix[j][l]) {
                    st = 0;
                    break;
                }
            }
            if (st) {
                for (int l = 0; l <= n; l++) {
                    matrix[j][l] = 0;
                }
            }
        }
    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            printf("%lld ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int zero_sol = 0;
    for (int i = 0; i < k; i++) {
        int st = 1;
        for (int j = 0; j <= n; j++) {
            if (matrix[i][j] != 0) {
                if (j == n) {
                    zero_sol = 1;
                }
                st = 0;
                break;
            }
        }
        if (st) {
            zero_s++;
        }
    }

    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            printf("%lld ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    long long count_solutions = power(p, n - (k - zero_s), M);
    if (zero_sol) {
        fprintf(out, "0");
    }
    else {
        if (count_solutions == 1) {
            fprintf(out, "1\n");
            long long* solutions = (long long*)malloc(n * sizeof(long long));
            int count = n - 1;
            for (int i = k - 1; i >= 0; i--) {
                for (int j = n - 1; j >= i; j--) {
                    if (i == j) {
                        solutions[count] = (matrix[i][n] * (power(matrix[i][j], p - 2, p))) % p;
                        count--;
                    }
                    else {
                        matrix[i][n] = (matrix[i][n] - matrix[i][j] * solutions[j] + p * p) % p;
                    }
                    for (int q = 0; q < n; q++) {
                        printf("%lld\n", solutions[q]);
                    }
                }
                printf("\n");
            }
            for (int i = 0; i < n; i++) {
                fprintf(out, "%lld\n", solutions[i]);
            }
        }
        else {
            fprintf(out, "%lld\n", count_solutions);
        }
    }
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

long long bolmod = 1000000007;

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

    for (long long i = k - 1; i >= 0; i--)
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
    }

    if (flag || pstep(mod, psub(n, psub(k, puststr, bolmod), bolmod), bolmod) > 1)
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
    }

    long long* res = (long long*)malloc((n + 2) * sizeof(long long));
    res[0] = 1;
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
        res[i + 1] = pdiv(sum, arr[i][i], mod);
    }
    res[0] = n;
    *kost = 1;
    return res;
}

int main()
{
    long long k, n, mod;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%lld %lld %lld", &n, &k, &mod);

    long long** arr = (long long**)malloc(k * sizeof(long long));
    for (int i = 0; i < k; i++)
    {
        arr[i] = (long long*)malloc((n + 1) * sizeof(long long));
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            scanf("%lld", &arr[i][j]);
        }

    }
    long long kost = 0;
    stepvid(arr, k, n, mod);
    long long* res = reshenia(arr, k, n, mod, &kost);
    if (kost == 1) {
        printf("1\n");
        for (long long i = 1; i <= res[0]; i++)
        {
            printf("%lld\n", res[i]);
        }
    }
    else {
        printf("%lld\n", res[1]);
    }

}
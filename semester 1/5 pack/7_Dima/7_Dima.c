
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
typedef struct LongNum_s {
    int len; //сколько цифр в числе
    int arr[10000]; //массив десятичных цифр числа
} LongNum;
void longsum(LongNum* a, LongNum* b, int e) {
    for (int i = 1; i <= a->len - e + 1; i++) {
        for (int j = b->len + 1; j <= a->len + 1; j++)
            b->arr[j] = 0;
        a->arr[i + e - 1] = a->arr[i + e - 1] + b->arr[i];
        if (a->arr[i + e - 1] > 9) {
            if (a->len == i + e - 1) {
                a->arr[a->len + 1] = 0;
                b->arr[b->len + 1] = 0;
                a->len++;
            }
            a->arr[i + 1 + e - 1]++;
            a->arr[i + e - 1] %= 10;
        }
    }
}
void longprod(LongNum* a, int b) {
    for (int i = 1; i <= a->len; i++) {
        a->arr[i] *= b;
        if (a->arr[i - 1] > 9 || a->len == 1) {
            a->arr[i] += a->arr[i - 1] / 10;
            a->arr[i - 1] %= 10;
        }
        if (a->len == i && a->arr[i] > 9) {
            a->len++;
            a->arr[a->len] = 0;
        }
    }
}
void longlongprod(LongNum* a, LongNum* b) {
    LongNum res;
    for (int i = 0; i < 10000; i++)
        res.arr[i] = 0;

    for (int j = 1; j <= b->len; j++) {
        LongNum e = *a;
        longprod(&e, b->arr[j]);
        res.len = e.len + j - 1;
        longsum(&res, &e, j);
    }
    *a = res;
}
void longprint(LongNum num) {
    for (int i = num.len; i > 0; i--)
        printf("%d", num.arr[i]);
}
int main() {
    char A[1001];
    LongNum a, b;
    scanf("%s", A);
    a.len = 0;
    a.arr[0] = 0;
    for (int i = 0; A[i] != 0; i++) {
        a.len++;
    }
    for (int i = 0; i < a.len; i++) {
        a.arr[a.len - i] = A[i] - '0';
    }
    scanf("%s", A);
    b.len = 0;
    b.arr[0] = 0;
    for (int i = 0; A[i] != 0; i++) {
        b.len++;
    }
    for (int i = 0; i < b.len; i++) {
        b.arr[b.len - i] = A[i] - '0';
    }
    if (b.len > a.len) {
        LongNum t = a;
        a = b; b = t;
    }
    longlongprod(&a, &b);
    longprint(a);
}
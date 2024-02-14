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
int main()
{
    MOD = 13;

    assert(pnorm(-12) == 1);

    assert(pnorm(422) == 6);

    assert(pnorm(-422) == 7);

    int x = pnorm(-143);
    assert(x == 0);

    int y = 7;
    assert(pmul(x, y) == 0);

    MOD = 17;
    x = 45;
    assert(pnorm(x) == 11);

    y = 12;

    assert(psub(pnorm(x), pnorm(y)) == 16);

    assert(padd(pnorm(x), pnorm(y)) == 6);

    assert(pmul(pnorm(x), pnorm(y)) == 13);

    int z = pdiv(pnorm(x), pnorm(y));
    assert(z == 8);

    assert(pmul(pnorm(y), pnorm(z)) == pnorm(x));

    MOD = 13;

    int a = 45;
    a = pnorm(a);
    assert(a == 6);
    
    x = pmul(padd(7, psub(2, 3)), 5);
    assert(x == 4);

    y = pdiv(7, x);
    assert(pmul(x, y) == 7);

    MOD = 999999937;
    x = 432433094;
    y = 496042239;
    z = pmul(x, y);
    assert(pmul(x, y) == 679278325);

    z = pdiv(x, y);
    assert(pdiv(x, y) == 70545511);

    assert(pmul(y, z) == 432433094);
    return 0;
}
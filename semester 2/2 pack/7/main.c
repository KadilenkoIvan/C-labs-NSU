#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

#include "primes.h"

int main()
{
    assert(isPrime(11) == 1);
    assert(isPrime(10) == 0);
    assert(isPrime(9) == 0);
    assert(isPrime(0) == 0);
    assert(isPrime(1) == 0);
    assert(isPrime(2) == 1);
    assert(findNextPrime(10) == 11);
    assert(findNextPrime(25) == 29);
    assert(findNextPrime(111) == 113);
    assert(getPrimesCount(2, 11) == 4);
    assert(getPrimesCount(1, 11) == 4);
    assert(getPrimesCount(3, 11) == 3);
    assert(getPrimesCount(3, 12) == 4);
    assert(getPrimesCount(0, 2) == 0);
    assert(getPrimesCount(11, 12) == 1);
    assert(getPrimesCount(12, 12) == 0);
    assert(getPrimesCount(2, 12) == 5);
    assert(getPrimesCount(0, 100070) == 9598);
    assert(getPrimesCount(0, 100069) == 9597);
    assert(getPrimesCount(3, 100069) == 9596);
    assert(isPrime(9999991) == 1);
    assert(isPrime(9999990) == 0);
    assert(isPrime(9999992) == 0);
    assert(getPrimesCount(3, 100069) == 9596);
    assert(getPrimesCount(3, 1000069) == 78501);
    assert(getPrimesCount(3, 9999991) == 664577);
    assert(getPrimesCount(3, 9999992) == 664578);
    assert(getPrimesCount(97, 97) == 0);
    assert(getPrimesCount(97, 98) == 1);
    assert(getPrimesCount(96, 98) == 1);
    assert(isPrime(1423523) == 0);
    assert(isPrime(1423524) == 0);
    assert(findNextPrime(11) == 11);
    assert(findNextPrime(12) == 13);
    assert(findNextPrime(12) == 13);
    assert(getPrimesCount(0, 10000000) == 664579);
    assert(isPrime(10000000) == 0);
    assert(findNextPrime(10000000) == 10000019);
}
/*
просто массив из простых чисел по порядку (всего 664580 простых чисел)
ищем бинарным поиском
ищем ближайший левый и правый, вычитаем индексы, получаем кол-во между числами()
*/
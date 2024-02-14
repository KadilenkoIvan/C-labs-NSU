#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main(int argc, char** argv) {         //main может принимать эти параметры
    for (int i = 0; i < argc; i++) {        //argc --- количество параметров + 1
        printf("(%d): [%s]\n", i, argv[i]);     //argv[0] --- путь к испольняемому файлу
    }                                       //argv[>0] --- параметры командной строки в порядке задания
    return 7;                               //возвращаемое значение main = "код возврата"
}
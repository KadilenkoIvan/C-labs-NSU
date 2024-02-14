#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void print(int number, char** one_to_ninghteen, char** one_to_ninghteen_for_millions, char** tventy_to_ninghty, char** hundred_to_n, char** thousands, char** millions, char** lines, FILE* out)
{
    if (number >= 1000000)
    {
        fprintf(out,"%s", hundred_to_n[number / 100000000]);
        number %= 100000000;
        if (number / 1000000 <= 19)
        {
            fprintf(out,"%s", one_to_ninghteen_for_millions[number / 1000000]);
            if (number / 1000000 == 1)
                fprintf(out,"%s", millions[1]);
            else if (number / 1000000 >= 2 && number / 1000000 <= 4)
                fprintf(out,"%s", millions[2]);
            else
                fprintf(out,"%s", millions[3]);
        }
        else
        {
            fprintf(out,"%s", tventy_to_ninghty[number / 10000000]);
            number %= 10000000;
            fprintf(out,"%s", one_to_ninghteen_for_millions[number / 1000000]);
            if (number / 1000000 == 1)
                fprintf(out,"%s", millions[1]);
            else if (number / 1000000 >= 2 && number / 1000000 <= 4)
                fprintf(out,"%s", millions[2]);
            else
                fprintf(out,"%s", millions[3]);
        }
        number %= 1000000;
    }
    if (number >= 1000)
    {
        fprintf(out,"%s", hundred_to_n[number / 100000]);
        number %= 100000;
        if (number / 1000 <= 19)
        {
            fprintf(out,"%s", one_to_ninghteen[number / 1000]);
            if (number / 1000 == 1)
                fprintf(out,"%s", thousands[1]);
            else if (number / 1000 >= 2 && number / 1000 <= 4)
                fprintf(out,"%s", thousands[2]);
            else /* if (number / 1000 != 0)*/
                fprintf(out,"%s", thousands[3]);
        }
        else
        {
            fprintf(out,"%s", tventy_to_ninghty[number / 10000]);
            number %= 10000;
            fprintf(out,"%s", one_to_ninghteen[number / 1000]);
            if (number / 1000 == 1)
                fprintf(out,"%s", thousands[1]);
            else if (number / 1000 >= 2 && number / 1000 <= 4)
                fprintf(out,"%s", thousands[2]);
            else
                fprintf(out,"%s", thousands[3]);
        }
        number %= 1000;
    }
    fprintf(out,"%s", hundred_to_n[number / 100]);
    number %= 100;
    if (number <= 19)
    {
        fprintf(out,"%s", one_to_ninghteen[number]);
        if (number == 1)
            fprintf(out,"%s", lines[1]);
        else if (number >= 2 && number <= 4)
            fprintf(out,"%s", lines[2]);
        else
            fprintf(out,"%s", lines[3]);
    }
    else
    {
        fprintf(out,"%s", tventy_to_ninghty[number / 10]);
        number %= 10;
        fprintf(out,"%s", one_to_ninghteen[number]);
        if (number == 1)
            fprintf(out,"%s", lines[1]);
        else if (number >= 2 && number <= 4)
            fprintf(out,"%s", lines[2]);
        else
            fprintf(out,"%s", lines[3]);
    }
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    int number = 0;
    char* one_to_ninghteen[20] = {"","odna ","dve ","tri ","chetyre ","pyat' ","shest' ","sem' ","vosem' ","devyat' ","desyat' ","odinnadtsat' " ,"dvenadtsat' ","trinadtsat' ","chetyrnadtsat' ","pyatnadtsat' ","shestnadtsat' ","semnadtsat' ","vosemnadtsat' ","devyatnadtsat' " };
    char* one_to_ninghteen_for_millions[20] = {"","odin ","dva ","tri ","chetyre ","pyat' ","shest' ","sem' ","vosem' ","devyat' ","desyat' ","odinnadtsat' " ,"dvenadtsat' ","trinadtsat' ","chetyrnadtsat' ","pyatnadtsat' ","shestnadtsat' ","semnadtsat' ","vosemnadtsat' ","devyatnadtsat' " };
    char* tventy_to_ninghty[10] = {"","","dvadtsat' ","tridtsat' ","sorok ","pyat'desyat ","shest'desyat ","sem'desyat ","vosem'desyat ","devyanosto " };
    char* hundred_to_n[11] = {"","sto ","dvesti ","trista ","chetyresta ","pyat'sot ","shest'sot ","sem'sot ","vosem'sot ","devyat'sot " };
    char* thousands[4] = {"","tysyacha ","tysyachi ","tysyach " };
    char* millions[4] = {"","million ","milliona ","millionov " };
    char* lines[4] = {"","stroka\n","stroki\n","strok\n" };

    fscanf(in, "%d", &n);

    for (int i = 0; i < n; ++i)
    {
        fscanf(in,"%d", &number);
        print(number, &one_to_ninghteen, &one_to_ninghteen_for_millions, &tventy_to_ninghty, &hundred_to_n, &thousands, &millions, &lines, out);
    }

    fclose(in);
    fclose(out);
}

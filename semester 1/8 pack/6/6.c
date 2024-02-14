#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");
  
    int num = 0, buf = 0;
    unsigned char symbol = 0;
    unsigned char patterns[4];
    patterns[0] = 0;
    patterns[1] = 192;
    patterns[2] = 224;
    patterns[3] = 240;
    while (fread(&symbol, 1, 1, in) != 0)
    {
        num = 0;
        if (symbol >= 248) return;
        if ((symbol & patterns[3]) == patterns[3])
        {
            symbol = (symbol & 7);
            num += symbol;
            for (int i = 0; i < 3; ++i)
            {
                if (fread(&symbol, 1, 1, in) == 0)
                {
                    return;
                }
                if (symbol >= 192 || symbol < 128)
                    return;
                symbol = (symbol & 63);
                num = num << 6;
                num += symbol;
            }
            if (num > 1114111 || (num >= 55296 && num <= 57343) || num < 32768)
                num = 65533;
            fwrite(&num, 4, 1, out);
            continue;
        }
        if ((symbol & patterns[2]) == patterns[2])
        {
            symbol = (symbol & 15);
            num += symbol;
            for (int i = 0; i < 2; ++i)
            {
                if (fread(&symbol, 1, 1, in) == 0)
                {
                    return;
                }
                if (symbol >= 192 || symbol < 128)
                    return;
                symbol = (symbol & 63);
                num = num << 6;
                num += symbol;
            }
            if (num > 1114111 || (num >= 55296 && num <= 57343) || num < 1024)
                num = 65533;
            fwrite(&num, 4, 1, out);
            continue;
        }
        if ((symbol & patterns[1]) == patterns[1])
        {
            symbol = (symbol & 31);
            num += symbol;

            if (fread(&symbol, 1, 1, in) == 0)
            {
                return;
            }
            if (symbol >= 192 || symbol < 128)
                return;
            symbol = (symbol & 63);
            num = num << 6;
            num += symbol;
            if (num > 1114111 || (num >= 55296 && num <= 57343) || num < 64)
                num = 65533;
            fwrite(&num, 4, 1, out);
            continue;
        }
        if (((symbol ^ patterns[0]) & 128) == 0)
        {
            num = symbol;
            /*if (num > 1114111 || (num >= 55296 && num <= 57343))
                num = 65533;*/
            fwrite(&num, 4, 1, out);
            continue;
        }
        return;//hard - 1, 2, 3, 4 |||| soft - 1, 2, 3
    }
}
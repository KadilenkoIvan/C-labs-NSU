#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
    int first, last, k, count = 0;
    scanf("%d%d%d", &first, &last, &k);
    if (last <= first && k == 1)
    {
        count = 1;
    }
    else
    {
        for (int i = first; i < last; ++i)
        {
            for (int j = 1; j < last; ++j)
            {
                if ((i + j * (k - 1) <= last) && (i + j * k > last))
                {
                    for (int p = 0; p < k; ++p)
                    {
                        //printf("%d ", i + p*j);
                    }
                    //printf("\n");
                    count += 1;
                }
            }
        }
    }
    
    printf("%d", count);
}

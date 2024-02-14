#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

extern long long* arr_sum;
extern int rig;

int64_t Sum(int l, int r);

int Query(int l, int64_t sum)
{
    if (sum <= arr_sum[0] || l >= rig)
    {
        return l;
    }

    /* if (l > 0)
     {
         sum += arr_sum[l - 1];
     }
     int left = 0;
     int r = rig;
     int m = 0;

     while (left < r)
     {
         m = (left + r) / 2;
         if (arr_sum[m] < sum)
         {
             left = m + 1;
         }
         else
         {
             r = m;
         }
     }
     return left;*/

    if (l > 0)
    {
        sum += arr_sum[l - 1];
    }

    long long curr = 0, r = 0;
    for (int i = l; i < rig; ++i)
    {
        if (arr_sum[i] > sum)
        {
            return i;
        }

    }
    return rig;
}
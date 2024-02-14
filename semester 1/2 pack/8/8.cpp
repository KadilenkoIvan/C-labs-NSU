#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//до 2000 (включительно) было 485 весокосных годов
// years/4 - years/100 + years/400

int main()
{
    int m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int m_v[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = 0, mounth = 0, years = 0, n = 0;
    scanf("%d%d%d%d", &days, &mounth, &years, &n);

    for (int i = 0; i < n; ++i)
    {
        days += 1;
        if (years % 400 == 0 || (years % 4 == 0 && years % 100 != 0))
        {
            if (days > m_v[mounth - 1])
            {
                mounth += 1;
                days = 1;
                if (mounth == 13)
                {
                    years += 1;
                    mounth = 1;
                }
            }
            continue;
        }
        if (days > m[mounth - 1])
        {
            mounth += 1;
            days = 1;
            if (mounth == 13)
            {
                years += 1;
                mounth = 1;
            }
        }
    }
    printf("%d %d %d", days, mounth, years);
}
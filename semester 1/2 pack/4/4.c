#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
//#include <assert.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// || (max1 < sr1) || (max2 < sr1) || (max1 < sr2) || (max2 < sr2) || (max1 < min1) || (max2 < min1) || (max1 < min2) || (max2 < min1)

int main()
{
	int a1, a2, b1, b2, c1, c2, Sa, Sb, Sc;
	scanf("%d%d%d%d%d%d", &a1, &a2, &b1, &b2, &c1, &c2);

	Sa = a1 * a2;
	Sb = b1 * b2;
	Sc = c1 * c2;

	int maxS = MAX(Sa, MAX(Sb, Sc));
	int minS = MIN(Sa, MIN(Sb, Sc));
	int srS = Sa + Sb + Sc - maxS - minS;
	//printf("%d %d %d", maxS, srS, minS);

	int max1, max2, sr1, sr2, min1, min2;

	if (maxS == Sa)
	{
		max1 = MAX(a1, a2);
		max2 = MIN(a1, a2);
		sr1 = MAX(b1, b2);
		sr2 = MIN(b1, b2);
		min1 = MAX(c1, c2);
		min2 = MIN(c1, c2);
	}
	else if (maxS == Sb)
	{
		max1 = MAX(b1, b2);
		max2 = MIN(b1, b2);
		sr1 = MAX(a1, a2);
		sr2 = MIN(a1, a2);
		min1 = MAX(c1, c2);
		min2 = MIN(c1, c2);
	}
	else
	{
		max1 = MAX(c1, c2);
		max2 = MIN(c1, c2);
		sr1 = MAX(b1, b2);
		sr2 = MIN(b1, b2);
		min1 = MAX(a1, a2);
		min2 = MIN(a1, a2);
	}

	if ((maxS < minS + srS) || (max1 < sr1) || (max2 < sr2) || (max1 < min1) || (max2 < min2))
	{
		printf("NO");
	}
	else
	{
		int ost1 = max1 - sr1;
		int ost2 = max2 - sr2;
		if (((min1 > ost1 && min2 > ost2) || (min1 > ost2 && min2 > ost1)) && (ost1 > 0) && (ost2 > 0))
			printf("NO");
		else
			printf("YES");
	}
}
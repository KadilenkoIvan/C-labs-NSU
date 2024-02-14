
;

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main()
{
	#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
	{
		printf("Compiler: GCC");
	}
	#elif defined(__clang__)
	{
		printf("Compiler: clang");
	}
	#elif defined(__TINYC__)
	{
		printf("Compiler: TCC");
	}
	//#elif 
	//{
	//	printf("Compiler: MCVC");
	//}
	#endif

	if (sizeof(void*) == 4)
	{
		printf("\nBitness: 32");
	}
	else
	{
		printf("\nBitness: 64");
	}

	#if NDEBUG
	{
		printf("\nAsserts: disabled");
	}
	#else
	{
		printf("\nAsserts: enabled");
	}
	#endif
	return 0;
}

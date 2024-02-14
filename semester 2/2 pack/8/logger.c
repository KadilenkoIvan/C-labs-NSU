#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "logger.h"

FILE* curr_file;
int calls_count = 0;

void logSetFile(FILE* file)
{
	if (file == 0)
		curr_file = 0;
	else
		curr_file = file;
}

void logPrintf(const char* format, ...)
{
	if (curr_file == 0) return;

	va_list ap;
	va_start(ap, format);
	vfprintf(curr_file, format, ap);
	va_end(ap);
	++calls_count;
}

int getLogCallsCount()
{
	return calls_count;
}
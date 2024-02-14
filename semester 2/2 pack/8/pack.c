#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "pack.h"

int pack(char* buffer, const char* format, ...)
{
	//printf("1\n");
	int size = 0, j = 0;
	int buf_int = 0;
	double buf_double = 0;
	//printf("2\n");
	char *buf_str = malloc(1000000);//too small???
	//printf("3\n");
	va_list ap;
	va_start(ap, format);
	//printf("4\n");
	int str_lenth = strlen(format);
	for (int i = 1; i < str_lenth; i += 2)
	{
		//printf("%d\n", 4 + i);
		if (format[i] == 'd')
		{
			size += 4;
			buf_int = va_arg(ap, int);
			continue;
		}
		if (format[i] == 'l')
		{
			size += 8;
			buf_double = va_arg(ap, double);
			++i;
			continue;
		}
		if (format[i] == 's')
		{
			//++size;
			memcpy(buf_str, va_arg(ap, char*), 10000);
			size += strlen(buf_str) + 1;
			continue;
		}
	}
	va_end(ap);
	//printf("1.1\n");
	if (buffer == NULL)
	{
		return size;
	}

	va_start(ap, format);
	for (int i = 1; i < str_lenth; i += 2)
	{
		if (format[i] == 'd')
		{
			buf_int = va_arg(ap, int);
			memcpy(&buffer[j], &buf_int, 4);
			j += 4;
			continue;
		}
		if (format[i] == 'l')
		{
			buf_double = va_arg(ap, double);
			memcpy(&buffer[j], &buf_double, 8);
			j += 8;
			++i;
			continue;
		}
		if (format[i] == 's')
		{
			memcpy(buf_str, va_arg(ap, char*), 10000);
			memcpy(&buffer[j], buf_str, strlen(buf_str) + 1);
			j += strlen(buf_str) + 1;
			continue;
		}
	}
	va_end(ap);
	free(buf_str);
	return size;

}
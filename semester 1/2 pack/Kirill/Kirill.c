#include <stdio.h>
#include <stdlib.h>

void foo(int v, int p = (-1))
{
	return p;
}

int main() {
	// Open the input and output files
	FILE* input_file = fopen("input.txt", "r");
	FILE* output_file = fopen("output.txt", "w");

	// Read the two numbers from the input file
	int a, b;
	fscanf(input_file, "%d", &a);
	fscanf(input_file, "%d", &b);

	// Compute the difference between the numbers
	int c = diff(a, b);

	// Write the result to the output file
	fprintf(output_file, "%d\n", c);

	// Close the input and output files
	fclose(input_file);
	fclose(output_file);

	return 0;
}
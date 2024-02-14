#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct State
{
	char* regs[256];
} State;

//loads string A from I-th register ([idx0] contains its index)
//loads string B from J-th register ([idx1] contains its index)
//then stores concatenation of A and B into I-th register
//BEWARE: [idx0] and [idx1] are allowed to be equal indices
void concat_2(State* state, char* idx0, char* idx1)
{
	int new_length = strlen(state->regs[atoi(idx0)]) + strlen(state->regs[atoi(idx1)]);
	int idx0_length = strlen(state->regs[atoi(idx0)]);
	state->regs[atoi(idx0)] = realloc(state->regs[atoi(idx0)], sizeof(char) * (new_length + 1));
	for (int i = idx0_length; i < new_length; ++i)
	{
		state->regs[atoi(idx0)][i] = state->regs[atoi(idx1)][i - idx0_length];
	}
	state->regs[atoi(idx0)][new_length] = '\0';
}

//extracts sequence of tokens/words separated by underscore character from string [arg]
//puts K –- number of tokens into 0-th register
//puts the tokens into 1-th, 2-th, ..., K-th registers (in correct order)
void tokenize_1(State* state, char* arg)
{
	int curr = 0;
	int i = 0;
	//after it 'i' on non '_' symbol
	while (arg[i] != '\0')
	{
		while (arg[i] == '_')
			++i;
		//after it 'i' on non '_' symbol

		int j = i;
		int k = 0;
		char new_str[100000];
		while (arg[j] != '_')
		{
			new_str[k] = arg[j];
			++k;
			++j;
		}//after it 'j' on '_' symbol
		new_str[k] = '\0';

		if (state->regs[curr] == NULL)
			state->regs[curr] = malloc(sizeof(char) * (j - i + 1));
		else
		{
			free(state->regs[curr]);
			state->regs[curr] = malloc(sizeof(char) * (j - i + 1));
		}
		strcpy(state->regs[curr], new_str);
		++curr;
	}
	state->regs[0] = curr;
}
//
// Created by nikita on 25.9.17.
//
#include "kasiski.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DEFAULT_GCD_UPPER_BOUND 500
#define DEFALUT_DIGRAM_LENGTH 3

struct kasiski {
    int intervals[DEFAULT_GCD_UPPER_BOUND];
    int gcd_freqs[DEFAULT_GCD_UPPER_BOUND];
    int intervals_cnt;
};

static void find_intervals(struct kasiski *k, const char *input);
static void calculate_interval_gcds(struct kasiski *k);
static int find_most_probable_keylen(struct kasiski *k);
static int gcd(int a, int b)
{
	int i;

	for (i = a; i > 1; i--)
		if ((a % i == 0) && (b % i == 0))
			return i;

	return 1;
}

struct kasiski *kasiski_init()
{
	struct kasiski *result = calloc(1, sizeof *result);

	return result;
}

int kasiski_find_key_length(struct kasiski *k, const char *input)
{
	find_intervals(k, input);
	calculate_interval_gcds(k);

	return find_most_probable_keylen(k);
}

void kasiski_destroy(struct kasiski *k)
{
	free(k);
}

void find_intervals(struct kasiski *k, const char *input)
{
	int i;
	int j;
	char digram[DEFALUT_DIGRAM_LENGTH + 1];
	char window[DEFALUT_DIGRAM_LENGTH + 1];

	for (i=0;i<strlen(input);++i)
	{
		strncpy(digram, input + i, DEFALUT_DIGRAM_LENGTH);
		digram[DEFALUT_DIGRAM_LENGTH]='\0';

		for (j=i+1;j<strlen(input);++j)
		{
			strncpy(window, input + j, DEFALUT_DIGRAM_LENGTH);
			window[DEFALUT_DIGRAM_LENGTH]='\0';

			if (!strcmp(digram,window))
				k->intervals[k->intervals_cnt++]=j-i;

		}
	}
}

void calculate_interval_gcds(struct kasiski *k)
{
	int i;
	int j;

	for (i = 0; i < k->intervals_cnt; i++)
		for (j = i + 1; j < k->intervals_cnt; j++)
			k->gcd_freqs[gcd(k->intervals[i], k->intervals[j])]++;
}

int find_most_probable_keylen(struct kasiski *k)
{
	int i;
	int keylen = 0;

	for (i = 2; i < 500; i++)
		if (k->gcd_freqs[keylen] < k->gcd_freqs[i])
			keylen=i;

	return keylen;
}

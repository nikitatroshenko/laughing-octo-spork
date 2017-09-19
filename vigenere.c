//
// Created by nikita on 11.9.17.
//
#include "vigenere.h"
#include <string.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define DEFAULT_OFFSET_START ('A')
#define DEFAULT_ALPHABET_LENGTH 26
#define NEUTRAL_CHARACTERS " \r\n\t"

struct vigenere {
    char *offsets;
    size_t key_length;
};

static char *do_substitute_str(struct vigenere *v,
			       char *buf,
			       size_t len,
			       int is_encrypt);

static char do_substitute(struct vigenere *v,
			  char in,
			  char offset,
			  int is_encrypt);

static void vigenere_substitute_stream(struct vigenere *v,
				       FILE *in,
				       FILE *out,
				       int is_encrypt);

static int is_neutral(struct vigenere *v, char c);

struct vigenere *vigenere_init(const char *key, size_t len)
{
	struct vigenere *v = calloc(1, sizeof *v);
	int i;

	v->key_length = len;
	v->offsets = calloc(len, sizeof *(v->offsets));

	for (i = 0; i < len; i++) {
		v->offsets[i] = (char) (key[i] - DEFAULT_OFFSET_START);
	}

	return v;
}

char *vigenere_encrypt(struct vigenere *v, char *buf, size_t len)
{
	return do_substitute_str(v, buf, len, TRUE);
}

char *vigenere_decrypt(struct vigenere *v, char *buf, size_t len)
{
	return do_substitute_str(v, buf, len, FALSE);
}


void vigenere_destroy(struct vigenere *v)
{
	free(v->offsets);
	free(v);
}

void vigenere_decrypt_stream(struct vigenere *v, FILE *in, FILE *out)
{
	vigenere_substitute_stream(v, in, out, FALSE);
}

void vigenere_encrypt_stream(struct vigenere *v, FILE *in, FILE *out)
{
	vigenere_substitute_stream(v, in, out, TRUE);
}

char *do_substitute_str(struct vigenere *v,
			char *buf,
			size_t len,
			int is_encrypt)
{
	int i;

	for (i = 0; i < len; i++) {
		if (is_neutral(v, buf[i]))
			continue;

		buf[i] = do_substitute(v, buf[i],
				       v->offsets[i % v->key_length],
				       is_encrypt);
	}

	return buf;
}

char do_substitute(struct vigenere *v, char in, char offset, int is_encrypt)
{
	/* TODO: will be used to store offset start and alphabet length */
	(void) v;

	char result_offset = (is_encrypt) ? offset : -offset;
	int char_modulo = ((in - DEFAULT_OFFSET_START)
			   + result_offset + DEFAULT_ALPHABET_LENGTH) %
			  DEFAULT_ALPHABET_LENGTH;

	return (char) (char_modulo + DEFAULT_OFFSET_START);
}

int is_neutral(struct vigenere *v, char c)
{
	/* TODO: will be used to store neutral characters */
	(void) v;

	return c < 'A' || c > 'Z';//strchr(NEUTRAL_CHARACTERS, c) != NULL;
}

void vigenere_substitute_stream(struct vigenere *v,
				FILE *in,
				FILE *out,
				int is_encrypt)
{
	char *buf = calloc(v->key_length, sizeof *buf);
	size_t read;

	while (0 != (read = fread(buf, sizeof *buf, v->key_length, in))) {
		do_substitute_str(v, buf, v->key_length, is_encrypt);

		fwrite(buf, 1, read, out);
	}
}

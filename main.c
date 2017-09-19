#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "vigenere.h"

#define DEFAULT_PLAIN_TEXT "CRYPTOGRAPHY AND DATA SECURITY"
#define DEFAULT_PLAIN_LEN 31
#define DEFAULT_KEY "MOUSE"

//struct vigenere_options {
//    FILE *in;
//    FILE *out;
//    char *str;
//    char *key;
//    int is_encrypt;
//};
//
//typedef void(*arg_executor)(int argc, char **argv, struct vigenere_options *opts);
//
//static void set_input(int argc, char **argv, struct vigenere_options *opts);
//static void set_output(int argc, char **argv, struct vigenere_options *opts);
//static void set_key(int argc, char **argv, struct vigenere_options *opts);
//static void set_str(int argc, char **argv, struct vigenere_options *opts);
//static void set_encrypt(int argc, char **argv, struct vigenere_options *opts);
//
//struct vigenere_args {
//    const char *arg;
//    const char *description;
//    arg_executor executor;
//};
//
//struct vigenere_args args[] = {
//	{"if", "=<path> Specify input file", set_input},
//	{"of", "=<path> Specify output file", set_output},
//	{"key", "=<key> Specify key", set_key},
//	{"str", "=<string_to_process> Specify input string. Cannot be used with 'if'", set_str},
//	{"encrypt", "={true|false} Specify whether to encrypt or decrypt input", set_encrypt}
//};

int main(int argc, char const *argv[])
{
	struct vigenere *v = vigenere_init("MOUSE", 5);

	FILE *in = stdin;// */fopen("/home/nikita/lorem_ipsum", "rt");
	FILE *out = stdout;// */fopen("/home/nikita/lorem_ipsum_decrypted", "wt");

	if (argc < 2) {
		fprintf(stderr, "no args specified\n");
		exit(1);
	} else if (!strncmp(argv[1], "encrypt", strlen("encrypt"))) {
		vigenere_encrypt_stream(v, in, out);
	} else if (!strncmp(argv[1], "decrypt", strlen("decrypt"))) {
		vigenere_decrypt_stream(v, in, out);
	} else {
		fprintf(stderr, "no action specified\n");
		exit(1);
	}

	vigenere_destroy(v);

	return 0;
}

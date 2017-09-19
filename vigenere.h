//
// Created by nikita on 11.9.17.
//

#ifndef DSS_VIGENERE_H
#define DSS_VIGENERE_H

#include <stdlib.h>
#include <stdio.h>

struct vigenere;

struct vigenere *vigenere_init(const char *key, size_t len);

char *vigenere_encrypt(struct vigenere *v, char *plain, size_t len);

char *vigenere_decrypt(struct vigenere *v, char *cipher, size_t len);

void vigenere_encrypt_stream(struct vigenere *v, FILE *in, FILE *out);

void vigenere_decrypt_stream(struct vigenere *v, FILE *in, FILE *out);

void vigenere_destroy(struct vigenere *v);

#endif /* DSS_VIGENERE_H */

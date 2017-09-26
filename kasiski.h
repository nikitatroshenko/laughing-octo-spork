//
// Created by nikita on 26.9.17.
//

#ifndef DSS_VIGENERE_KASISKI_H
#define DSS_VIGENERE_KASISKI_H

struct kasiski;

struct kasiski *kasiski_init();

int kasiski_find_key_length(struct kasiski *k, const char *input);

void kasiski_destroy(struct kasiski *k);

#endif //DSS_VIGENERE_KASISKI_H

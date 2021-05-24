#ifndef _BUSTER_H
#define _BUSTER_H

#include <stdio.h>

#define BUSTER_VERSION "0.1"

char *buster_wordlist_gets(char *restrict s, size_t n, FILE *restrict stream);

#endif // _BUSTER_H

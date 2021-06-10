#ifndef _BUSTER_H
#define _BUSTER_H

#include <stdio.h>

#define BUSTER_VERSION "0.1"

struct wordlist {
    char **buf;
    size_t pos;
};

char *wordlist_next(struct wordlist *wl);

struct wordlist *wordlist_init(FILE *stream);

#endif // _BUSTER_H

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define BUSTER_VERSION "0.1"

struct bwordlist {
    char **buf;
    size_t len;
};

struct bwordlist *
bwordlist_read(FILE *stream);

void 
bwordlist_free(struct bwordlist *wl);

struct boptions {
    struct bwordlist *wordlist;
    time_t delay;
    size_t routines;
};

#endif // _UTILS_H

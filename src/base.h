#ifndef _BASE_H
#define _BASE_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define BUSTER_VERSION "0.1"

struct bwordlist {
    char **buf;
    size_t len;
};

int
bwordlist_read(FILE *fp, struct bwordlist *wlp);

void 
bwordlist_cleanup(struct bwordlist wl);

struct boptions {
    struct bwordlist wordlist;
    time_t delay;
    size_t routines;
};

#endif /* _BASE_H */

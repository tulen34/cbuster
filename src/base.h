#ifndef _BASE_H
#define _BASE_H

#include <stdio.h>
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

enum blogger_level {
    ERROR,
    WARN,
    INFO,
    DEBUG,
};

struct blogger {
    enum blogger_level level;
    FILE *output;
};

int
blogger_logf(struct blogger log, enum blogger_level level, 
             const char *format, ...);

void
blogger_cleanup(struct blogger log);

struct boptions {
    struct bwordlist wordlist;
    struct blogger logger;
    time_t delay;
    size_t routines;
};

#endif /* _BASE_H */

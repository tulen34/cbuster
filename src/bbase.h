#ifndef _BBASE_H
#define _BBASE_H

#include <stdio.h>
#include <time.h>

#define BUSTER_VERSION "0.1"

struct bwordlist {
    char **buf;
    long pos;
    long len;
};

int
bwordlist_read(FILE *fp, struct bwordlist *wlp);

void 
bwordlist_cleanup(struct bwordlist *wlp);

enum blogger_level {
    ERROR,
    WARN,
    INFO,
    DEBUG,
};

struct blogger {
    enum blogger_level level;
    FILE *outputfp;
};

int
blogger_logf(struct blogger *lp, enum blogger_level level, 
             const char *format, ...);

void
blogger_cleanup(struct blogger *lp);

struct boptions {
    struct bwordlist *wordlist;
    struct blogger *logger;
    time_t delay;
    size_t routines;
};

#endif /* _BBASE_H */

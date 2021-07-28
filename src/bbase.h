#ifndef _BBASE_H
#define _BBASE_H

#include <stdio.h>
#include <time.h>

#define BUSTER_VERSION "0.1"

struct bwordlist {
    char **buf;
    unsigned long pos;
    unsigned long len;
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
blogger_logf(const struct blogger *lp, enum blogger_level level, 
        const char *format, ...);

void
blogger_cleanup(struct blogger *lp);

struct boptions {
    struct bwordlist *wordlist;
    struct blogger *logger;
    unsigned long delay;
    unsigned long routines;
};

int
boptions_sleep(const struct boptions *op);

#endif /* _BBASE_H */

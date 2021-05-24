#ifndef _DIR_H
#define _DIR_H

#include <stdio.h>

// TODO: Add optional fields
struct busterdir {
    char *host;
    FILE *wordlist;
};

int busterdir_run(struct busterdir dir);

#endif // _DIR_H

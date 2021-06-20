#ifndef _DIR_H
#define _DIR_H

#include <stdio.h>
#include <stdbool.h>

#ifndef USERAGENTS_PATH 
# define USERAGENTS_PATH "etc/dir/user-agents.txt"
#endif

// TODO: Add optional fields
struct busterdir {
    char *host;
    FILE *wordlist;

    size_t nhandles;
    bool use_randuseragents;
};

char *busterdir_wordlist_geturl(char *restrict s, size_t n,
                                const char *host, FILE *restrict wordlist);

char *busterdir_getranduseragent(char *restrict s, size_t n);

int busterdir_run(struct busterdir dir);

#endif // _DIR_H

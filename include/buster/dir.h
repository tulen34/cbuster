#ifndef _DIR_H
#define _DIR_H

#include <curl/curl.h>
#include <stdio.h>

struct buster_dir_optionals {
    bool use_rand_useragent;

    FILE *output;
};

struct buster_dir {
    char *host;
    FILE *wordlist;

    struct buster_dir_optionals optionals;

    pthread_mutex_t *mutex;
};

struct buster_dir buster_dir_init(char *host, FILE *wordlist);

void buster_dir_start(struct buster_dir dir);

#endif // _DIR_H

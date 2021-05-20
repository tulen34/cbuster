#ifndef _DIR_H
#define _DIR_H

#include <utils.h>
#include <stdio.h>

struct buster_dir {
    FILE *wordlist;
    unsigned int nthreads;

    char host[UTILS_STRSIZE + 1];
    char user_agent[UTILS_STRSIZE + 1];
    char http_username[UTILS_STRSIZE + 1];
    char http_password[UTILS_STRSIZE + 1];

    char proxy[UTILS_STRSIZE + 1];
    char proxy_username[UTILS_STRSIZE + 1];
    char proxy_password[UTILS_STRSIZE + 1];
};

struct buster_dir *buster_dir_init(const char *host, FILE *wordlist);

int buster_dir_set_rand_user_agent(struct buster_dir *dir, const char *path);

#endif // _DIR_H

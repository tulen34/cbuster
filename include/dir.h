#ifndef _DIR_H
#define _DIR_H

#include <stdio.h>

struct buster_dir {
    FILE *wordlist_stream;
    unsigned int nthreads;

    char *host;
    char *user_agent;
    char *http_username, *http_password;

    char *proxy, *proxy_username, *proxy_password;
};

struct buster_dir *buster_dir_init(char *host);

#endif

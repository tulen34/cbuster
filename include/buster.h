#ifndef _BUSTER_H
#define _BUSTER_H

#include <stdio.h>

#define BUSTER_VERSION "0.1"

struct wordlist {
    char **buf;
    size_t pos;
};

#endif // _BUSTER_H

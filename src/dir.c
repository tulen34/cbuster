#include <dir.h>
#include <utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

extern int errno;

struct buster_dir *buster_dir_init(const char *host, FILE *wordlist) {
    struct buster_dir *dir = (struct buster_dir *)malloc(
            sizeof(struct buster_dir));

    if (host == NULL) {
        errno = EINVAL;
        return NULL;
    }
    strcpy(dir->host, host);

    dir->wordlist = wordlist == NULL ? stdin : wordlist;
    sprintf(dir->user_agent, "cbuster/%s", BUSTER_VERSION);
    dir->nthreads = 8U;
    return dir;
}

int buster_dir_set_rand_user_agent(struct buster_dir *dir, const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        errno = ENOENT;
        return errno;
    }

    unsigned int nlines = 0;
    int c;
    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            ++nlines;
    rewind(fp);

    srand(time(NULL));
    int nline = rand() % nlines + 1;
    for (int i = 0; i < nline; ++i)
        fgets(dir->user_agent, STRSIZE, fp);
    return EXIT_SUCCESS;
}

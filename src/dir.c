#include <dir.h>
#include <stdio.h>

struct buster_dir *buster_dir_init(char *host) {
    struct buster_dir *ret = (struct buster_dir *)malloc(
            sizeof(struct buster_dir));
    ret->wordlist_stream = stdin;
    ret->nthreads = 10U

    ret->host = host;
    ret->user_agent = "cbuster";
    ret->http_username = NULL;
    ret->http_password = NULL;

    ret->proxy = NULL;
    ret->proxy_username = NULL;
    ret->proxy_password = NULL;
    return ret;
}

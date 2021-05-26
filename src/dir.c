#include <buster/dir.h>
#include <buster.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>

#define STRSIZE 1064

char *busterdir_wordlist_geturl(char *restrict s, size_t n,
                                const char *host, FILE *restrict wordlist) {
    strcpy(s, host);
    if (s[strlen(s) - 1] != '/')
        strcat(s, "/");
    buster_wordlist_gets(s + strlen(s), n, wordlist);
    return s;
}

char *busterdir_getranduseragent(char *restrict s, size_t n) {
    FILE *fp = fopen(USERAGENTS_PATH, "r");
    if (fp == NULL) {
        s = NULL;
        goto ret;
    }

    unsigned int nlines = 0;
    int c;
    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            ++nlines;
    rewind(fp);

    int rand_nline = rand() % nlines + 1;
    for (int i = 0; i < rand_nline; ++i)
        fgets(s, STRSIZE, fp);
ret:
    return s;
}

int *busterdir_curl_multi_add_handle(struct busterdir dir, 
                                     CURLM *curlm, FILE *devnull) {
    CURL *curl = curl_easy_init();
    if (curl == NULL)
        return EIO;

    // Setting output to /dev/null
    curl_easy_setopt(handles[i], CURLOPT_WRITEDATA, devnull);

    // Getting url using wordlist
    char url[STRSIZE];
    busterdir_wordlist_geturl(url, STRSIZE, dir.host, dir.wordlist);
    if (url == NULL)
        return EOF;
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Setting random user-agent if needed or default
    char user_agent[STRSIZE];
    if (dir.use_randuseragents)
        busterdir_getranduseragent(user_agent, STRSIZE);
    else
        sprintf(user_agent, "cbuster/%s", BUSTER_VERSION);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);

    curl_multi_add_handle(curlm, curl);
    return EXIT_SUCCESS;
}

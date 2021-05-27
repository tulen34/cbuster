#include <buster/dir.h>
#include <buster.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
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
        fgets(s, n, fp);
ret:
    return s;
}

int busterdir_curl_multi_add_handle(struct busterdir dir, 
                                    CURLM *curlm, FILE *restrict devnull) {
    CURL *curl = curl_easy_init();
    if (curl == NULL)
        return EIO;

    // Setting output to /dev/null
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, devnull);

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

void check_curlmsg(CURLM *curlm) {
    struct CURLMsg *m;
    do {
        int msgs_in_queue;
        m = curl_multi_info_read(curlm, &msgs_in_queue);
        if (m == NULL || m->msg != CURLMSG_DONE)
            continue;

        CURL *curl = m->easy_handle;

        long code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

        char *method, *url;
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_METHOD, &method);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        char output[STRSIZE];
        sprintf(output, "%-40s - %-7s - %ld", url, method, code);
        puts(output);

        curl_multi_remove_handle(curlm, curl);
        curl_easy_cleanup(curl);
    } while (m != NULL);
}

int busterdir_run(struct busterdir dir) {
    CURLM *curlm = curl_multi_init();
    if (curlm == NULL)
        return EIO;

    FILE *devnull = fopen("/dev/null", "w+");
    if (devnull == NULL)
        return ENOENT;

    while (!feof(dir.wordlist)) {
        for (size_t i = 0; i < dir.nhandles; ++i) {
            int status = busterdir_curl_multi_add_handle(dir, curlm, devnull);
            if (status != EXIT_SUCCESS)
                return status;
        }

        int nrunning;
        do {
            curl_multi_perform(curlm, &nrunning);
            check_curlmsg(curlm);
        } while (nrunning > 0);
    }
    return EXIT_SUCCESS;
}

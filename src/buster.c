#include <buster.h>
#include <stdio.h>
#include <string.h>

char *buster_wordlist_gets(char *restrict s, size_t n, FILE *restrict stream) {
    fgets(s, n, stream);

    char *comment = strchr(s, '#'); 
    if (comment != NULL)
        *comment = '\0';
    return s;
}

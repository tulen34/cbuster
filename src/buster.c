#include <buster.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *buster_wordlist_gets(char *restrict s, size_t n, FILE *restrict stream) {
    fgets(s, n, stream);

    for (int i = 0; s[i] != '\0'; ++i)
        // Ignore comments and all after space
        if (isspace(s[i]) || s[i] == '#')
            s[i] = '\0';
    return s;
}

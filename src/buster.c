#include <buster.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 4096

char **wordlist_read(FILE *stream) {
    int ch, nlines, stat, i;
    char **wl, s[STRSIZE];

    nlines = 0;
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n') ++nlines;
    rewind(stream);

    wl = calloc((size_t)nlines, sizeof(char *));
    if (wl == NULL) return NULL;

    i = 0;
    while ((stat = fscanf(stream, "%[^#\n]s\n", s)) != EOF)
        if (stat == 1) wl[i++] = strdup(s);
    return wl;
}

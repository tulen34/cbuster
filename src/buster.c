#include <buster.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wordlist *wordlist_init(FILE *stream) {
    struct wordlist *wl = malloc(sizeof(struct wordlist));
    if (wl == NULL)
        return NULL;

    fseek(stream, 0L, SEEK_END);
    long nbytes = ftell(stream);
    rewind(stream);

    char *text = calloc((size_t)nbytes, sizeof(char));
    if (text == NULL) {
        free(wl);
        return NULL;
    }
    fread(text, sizeof(char), (size_t)nbytes, stream);

    int nlines = 0;
    for (int i = 0; i < nbytes; ++i)
        if (text[i] == '\n')
            ++nlines;

    wl->buf = calloc((size_t)nlines, sizeof(char *));
    if (wl->buf == NULL) {
        free(wl);
        free(text);
        return NULL;
    }

    int nchars = 0;
    int top = 0;
    for (int i = 0; i < nbytes; ++i) {
        if (text[i] != '\n' && text[i] != '#') {
            ++nchars;
            continue;
        }
        char *start = text + i - nchars;
        wl->buf[top++] = strndup(start, (size_t)nchars - 1);
        nchars = 0;
    }

    free(text);
    return wl;
}

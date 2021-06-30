#include <utils.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRSIZE 4096
#define FORMAT "%[^#\n]s\n"

struct bwordlist *
bwordlist_read(FILE *stream) {
    int ch, nlines, stat;
    char s[STRSIZE];
    struct bwordlist *wl;

    wl = malloc(sizeof(struct bwordlist));
    if (wl == NULL) 
        goto enomem;

    nlines = 0;
    while ((ch = fgetc(stream)) != EOF)
        if (ch == '\n') 
            ++nlines;
    wl->buf = calloc((size_t)nlines, sizeof(char *));
    if (wl->buf == NULL) 
        goto enomem;

    while ((stat = fscanf(stream, FORMAT, s)) != EOF) {
        if (stat != 1)
            continue;
        if ((wl->buf[wl->len++] = strdup(s)) == NULL)
            goto enomem;
    }

    return wl;
enomem:
    if (wl != NULL) 
        bwordlist_free(wl);
    errno = ENOMEM;
    return NULL;
}

void 
bwordlist_free(struct bwordlist *wl) {
    int i;

    for (i = 0; i < (long)wl->len; ++i) 
        if (wl->buf[i] != NULL)
            free(wl->buf[i]);
    free(wl->buf);
    free(wl);
}

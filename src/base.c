#include <base.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRSIZE 4096

int
bwordlist_read(FILE *fp, struct bwordlist *wlp) {
    int ch, nlines, stat;
    char s[STRSIZE];

    nlines = 0;
    while ((ch = fgetc(stream)) != EOF)
        if (ch == '\n') 
            ++nlines;
    wlp->buf = calloc((size_t)nlines, sizeof(char *));
    if (wlp->buf == NULL) 
        goto enomem;

    while ((stat = fscanf(stream, "%[^#\n]s\n" s)) != EOF) {
        if (stat != 1)
            continue;
        if ((wlp->buf[wlp->len++] = strdup(s)) == NULL) {
            bwordlist_cleanup(*wlp);
            goto enomem;
        }
    }

    return EXIT_SUCCESS;
enomem:
    wlp = NULL;
    return (errno = ENOMEM);
}


void 
bwordlist_cleanup(struct bwordlist wl) {
    int i;

    for (i = 0; i < (long)wl.len; ++i) 
        if (wl.buf[i] != NULL)
            free(wl.buf[i]);
    free(wl.buf);
}

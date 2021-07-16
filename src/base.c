#include <base.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define STRSIZE 4096

int
bwordlist_read(FILE *fp, struct bwordlist *wlp) {
    int ch, nlines, i;
    char s[STRSIZE];

    nlines = 0;
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n')
            ++nlines;
    rewind(fp);
    wlp->buf = calloc((size_t)nlines, sizeof(char *));
    if (wlp->buf == NULL)
        goto enomem;

    wlp->len = 0;
    while (fgets(s, STRSIZE, fp) != NULL) {
        for (i = 0; s[i] != '\0'; ++i)
            if (s[i] == '#' || s[i] == '\n')
                s[i] = '\0';

        if ((wlp->buf[wlp->len++] = strdup(s)) == NULL) {
            bwordlist_cleanup(*wlp);
            goto enomem;
        }
    }
    return EXIT_SUCCESS;
enomem:
    return (errno = ENOMEM);
}

void 
bwordlist_cleanup(struct bwordlist wl) {
    int i;

    for (i = 0; i < (long)wl.len; ++i) 
        free(wl.buf[i]);
    free(wl.buf);
}

int
blogger_logf(struct blogger lg, enum blogger_level level, 
             const char *format, ...) {
    int stat;
    va_list ap;

    if (lg.level < level)
        return 0;

    va_start(ap, format);
    if (lg.output != NULL)
        vfprintf(lg.output, format, ap);
    stat = vprintf(format, ap);
    va_end(ap);
    return stat;
}

void
blogger_cleanup(struct blogger lg) {
    fclose(lg.output);
}

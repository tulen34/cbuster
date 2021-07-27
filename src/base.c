#include <base.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>

#define STRSIZE 4096

int
bwordlist_read(FILE *fp, struct bwordlist *wlp) {
    int ch;
    size_t n = 0;
    char s[STRSIZE];

    memset(wlp, 0, sizeof(struct bwordlist));

    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n')
            ++n;
    rewind(fp);
    wlp->buf = calloc(n, sizeof(char *));
    if (wlp->buf == NULL)
        goto enomem;

    while (fgets(s, STRSIZE, fp) != NULL) {
        n = 0;
        while (s[n] != '\0' && s[n] != '\n' && s[n] != '#')
            ++n;
        if (n == 0)
            continue;
        if ((wlp->buf[wlp->len++] = strndup(s, n - 1)) == NULL)
            goto enomem;
    }
    return EXIT_SUCCESS;
enomem:
    bwordlist_cleanup(wlp);
    return (errno = ENOMEM);
}

void
bwordlist_cleanup(struct bwordlist *wlp) {
    int i;

    for (i = 0; i < wlp->len; ++i)
        free(wlp->buf[i]);
    free(wlp->buf);
}

int
blogger_logf(struct blogger *lp, enum blogger_level level, 
             const char *format, ...) {
    int stat;
    va_list ap;

    if (lp->level < level)
        return 0;

    va_start(ap, format);
    if (lp->outputfp != NULL)
        vfprintf(lp->outputfp, format, ap);
    stat = vprintf(format, ap);
    va_end(ap);
    return stat;
}

void
blogger_cleanup(struct blogger *lp) {
    fclose(lp->outputfp);
}

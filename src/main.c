#include <bbase.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

struct option long_options[] = {
    { "help", no_argument, NULL, 'h' },
    { "verbose", no_argument, NULL, 'v' },
    { "quiet", no_argument, NULL, 'q' },
    { "delay", required_argument, NULL, 'd' },
    { "routines", required_argument, NULL, 'r' },
    { "output", required_argument, NULL, 'o' },
    { NULL, 0, NULL, 0 }
};
const char *optstring = "hvqd:r:o:";
const char *help_format = 
"Usage:\n"
"  %s [options] [arguments]\n"
"Global flags:\n"
"  -h, --help\n" 
"  -v, --verbose\n" 
"  -q, --quiet\n"
"  -d, --delay MS\n" 
"  -r, --routines NUM\n" 
"  -o, --output PATH\n";

int main(int argc, char *argv[]) {
    int ch;
    char *end;
    struct bbase base = {
        .logger = { INFO },
    };

    for(;;) {
        ch = getopt_long(argc, argv, optstring, long_options, NULL);
        if (ch == -1)
            break;
        switch (ch) {
        case '?':
            printf(help_format, argv[0]);
            return 1;
        case 'h':
            printf(help_format, argv[0]);
            return 0;
        case 'v':
            base.logger.level = DEBUG;
            break;
        case 'q':
            base.logger.level = ERROR;
            break;
        case 'd':
            base.delay = strtoul(optarg, &end, 10);
            if (errno == ERANGE)
                puts("ERROR!");
            printf("%lu\n", base.delay);
            break;
        case 'r':
            base.routines = strtoul(optarg, &end, 10);
            if (errno == ERANGE)
                puts("ERROR!");
            printf("%lu\n", base.routines);
            break;
        case 'o':
            base.logger.handler = fopen(optarg, "w+");
            if (base.logger.handler == NULL) {
                blogger_logf(&base.logger, ERROR, "Opening file: %s\n", optarg);
                return ENOENT;
            }
            break;
        }
    }
    bbase_cleanup(&base);
    return 0;
}

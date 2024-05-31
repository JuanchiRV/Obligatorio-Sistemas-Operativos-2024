// minish - v1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 1024

void
prompt(char *ps) {
    // ps is the prompt string
    if (isatty(stdin->_fileno)) // only show prompt if running an interactive shell
        fprintf(stderr, "(%s) ^D to exit > ", ps);
}

int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];

    for (;;) {
        prompt(progname);
        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
            break;
        }
        fprintf(stderr, "Will execute command %s", line);
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}
// minish - v4 - catch signals on fork

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define MAXLINE 1024

void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    struct sigaction oldact, newact;

    for (;;) {
        prompt(progname);
        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
            break;
        }
        fprintf(stderr, "Will execute command %s", line);

        if (strncmp(line, "sleep", 5) == 0) { 
            // very bad technique, only for demo purposes
            // will fork a child to run date command

            pid_t pid;                          // process ID: an unsigned integer type
            int wait_status;                    // wait status will be filled by waitpid syscall

            fprintf(stderr, "Will fork sleep command\n");

            // ============== NEW CODE HERE ==============
            sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
            newact = oldact;

            if ((pid = fork()) < 0) {           // fork error, i.e. too many processes
                error(0, errno, "fork error\n"); // will fprintf the error and go on
            }

            else if (pid == 0) {                 // child process
                
                // ============== NEW CODE HERE ==============
                newact.sa_handler = SIG_DFL;
                sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child

                execlp("sleep", "sleep", "5", NULL);    // if successful, child will go on with new executable
                error(EXIT_FAILURE, errno, "execvp error\n"); // if exec not successful, just exit child
            }

            else {                               // pid > 0: parent (shell) process

                // ============== NEW CODE HERE ==============
                newact.sa_handler = SIG_IGN;
                sigaction(SIGINT, &newact, NULL);   // ignore SIGINT while waiting

                waitpid(pid, &wait_status, 0);

                // ============== NEW CODE HERE ==============
                sigaction(SIGINT, &oldact, NULL);   // restore SIGINT when child finishes

                fprintf(stderr, "Ended sleep child process\n");

                // do something with wait_status
            }
        }
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}
#include <stdlib.h>//para exit
#include <sys/types.h>//para pid_t, nos genera muchos problemas
int externo(int argc, char **argv) {
    UNUSED(argc);

    pid_t ch_pid = fork();
    int status = 0;

    // Child process creation unsuccessful
    if (ch_pid == -1) {
        perror("fork");
        return 1;
    }
    
    // Child process
    if (ch_pid == 0) {
        if (execvp(argv[0], argv) == -1) {
            perror("execve");
        }
        exit(EXIT_FAILURE);
    }

    // Wait for child process to complete
    waitpid(ch_pid, &status, 0);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);

    return status;
}

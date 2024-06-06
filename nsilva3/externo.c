#include <stdlib.h>//para exit
#include <sys/types.h>//para pid_t, nos genera muchos problemas
int externo(int argc, char **argv) {//toma un arreglo de argumentos y su cantidad
    UNUSED(argc);//marca argc como no utilizado para evitar warnings del compilador

    pid_t ch_pid = fork();//fork crea un proceso hijo 
    int status = 0;

    if (ch_pid == -1) {//si fork devuelve -1, hubo un error
        perror("fork");//el perror imprime un mensaje de error
        return 1;
    }
    
    if (ch_pid == 0) {//si ch_pid es 0, es el proceso hijo
        if (execvp(argv[0], argv) == -1) {//ejecvp ejecuta el comando en argv[0] con los argumentos en argv
            perror("execve");
        }
        exit(EXIT_FAILURE);//si el execvp falla, se sale con un status de fallo
    }

    waitpid(ch_pid, &status, 0);//el proceso padre espera a que el hijo termine
    if (WIFEXITED(status))//WIFEXITED devuelve verdadero si el hijo termino normalmente
        status = WEXITSTATUS(status);//WEXITSTATUS devuelve el status de salida del hijo

    return status;
}

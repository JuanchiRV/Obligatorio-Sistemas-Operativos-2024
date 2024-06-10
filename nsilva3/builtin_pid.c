#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int builtin_pid (int argc, char **argv){
    UNUSED(argc);//Se declara argc como no utilizado para evitar un warning durante compilacion.
    UNUSED(argv);
<<<<<<< HEAD
    printf("Process ID is: %d\n", getpid());//Imprime el id del proceso actual.
=======
    printf("Process-id: %d\n", getpid());//Imprime el id del proceso actual.
>>>>>>> 802600ce91ea1c32fdb5a8a95c6257fb62381886
    return 0;//Devuelve 0 indicando una salida exitosa.

    }





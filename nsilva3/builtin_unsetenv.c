#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

extern int
builtin_unsetenv(int argc, char **argv)
{
    if(argc==1){ //Si hay solo un argumento (el nombre del comando), ejecuta el siguiente bloque.
        fprintf(stderr, "ERROR, los argumentos son insuficientes.\n"); //Imprime el mensaje en la salida estándar de error (stderr).
        return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
    }
    for(int i = 1; i<=argc; i++){
        unsetenv(argv[i]); //Llama a la función unsetenv para eliminar la variable de entorno especificada en argv[i].
    }
    return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"

int
builtin_status(int argc, char **argv)//funcion que ejecuta el comando status
//argc es el numero de argumentos y argv es un array de caracteres que son los argumentos pasados
{
    if(argc == 1 && strcmp(argv[0], "status") == 0)//Comprueba si el número de argumentos es 1 y si el primer argumento (el comando) es "status"
    {
    fprintf(stderr, "%d\n", globalstatret);//imprime el status del comando
    //"%d\n": Especifica que se va a imprimir un entero seguido de una nueva línea.
    //globalstatret: Es una variable global que contiene un valor de estado.
    return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

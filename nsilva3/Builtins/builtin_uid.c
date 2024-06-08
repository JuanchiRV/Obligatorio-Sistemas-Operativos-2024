/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <pwd.h>
#include "minish.h"


int
builtin_uid(int argc, char **argv)
{
    if(argc == 1 || strcmp(argv[0], "uid") == 0)//Si alguna de estas condiciones es verdadera, la función simplemente continúa sin hacer nada en este bloque (; es una instrucción vacía).
    {
        ;
    }
    uid_t userid = getuid();//getuid(): Llama a la función del sistema que devuelve el UID del usuario que está ejecutando el programa.
    struct passwd *user = getpwuid(userid);// Llama a la función del sistema que toma un UID y devuelve un puntero a una estructura passwd que contiene información sobre el usuario.
//user: Variable que almacena el puntero a la estructura passwd.
    if (user != NULL){//Imprime un mensaje en stderr con el nombre de usuario (user->pw_name) y el UID (userid).
        fprintf(stderr, "El ID del usuario %s es: %d\n", user->pw_name, userid);
        return EXIT_SUCCESS;//Retorna EXIT_SUCCESS (generalmente definido como 0) para indicar que la operación fue exitosa.
    }
    else {
        printf("No se pudo obtener la información del usuario\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/
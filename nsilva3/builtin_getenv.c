#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "minish.h"

int
builtin_getenv(int argc, char **argv)
{
    extern char **environ;//environ es una variable global que almacena todas las variables de entorno y sus valores en el formato nombre=valor
    if (argc==1){
        char **puntero = environ;//char **puntero: Declara un puntero a puntero a char
        for (int i=0; puntero[i]!=NULL; i++){
            fprintf(stderr, "%s\n", puntero[i]);//Imprime la cadena puntero[i] (la entrada actual en environ) en el flujo de error estándar (stderr).
        }
    }
    for (int i=1; i<argc; i++){//esto es para recorrer los demas argumentos
        char *var_env = getenv(argv[i]);//getenv para obtener el valor de la variable de entorno especificada por argv[i]
        if (var_env == NULL){//si retorna null, imprime un error
            error(1, errno, "getenv %s error", argv[i]);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "%s=%s\n", argv[i], var_env);//Si getenv encuentra la variable de entorno, imprime su nombre y valor en stderr
    }
    return EXIT_SUCCESS;        
}

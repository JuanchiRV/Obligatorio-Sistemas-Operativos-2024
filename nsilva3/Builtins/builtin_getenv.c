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
        char **s = environ;//char **s: Declara un puntero a puntero a char
        for (int i=0; s[i]!=NULL; i++){
            fprintf(stderr, "%s\n", s[i]);//Imprime la cadena s[i] (la entrada actual en environ) en el flujo de error estándar (stderr).
        }
    }
    for (int i=1; i<argc; i++){//esto es para recorrer los demas argumentos
        char *env_res = getenv(argv[i]);//getenv para obtener el valor de la variable de entorno especificada por argv[i]
        if (env_res == NULL){//si retorna null, imprime un error
            error(1, errno, "getenv %s error", argv[i]);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "%s=%s\n", argv[i], env_res);//Si getenv encuentra la variable de entorno, imprime su nombre y valor en stderr
    }
    return EXIT_SUCCESS;        
}

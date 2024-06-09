#include <stdio.h>//de guz
#include <stdlib.h>
#include "minish.h"

int builtin_setenv(int argc, char **argv)
{
    if (argc != 3)
    {
        // Si no hay 3 argumentos se imprime el mensaje de error y la forma correcta del comando
        fprintf(stderr, "Error en el comando, escribelo así: setenv <variable> <valor>\n");
        return 1; // Retornar 1 para indicar error
    }

    // Se establece la variable de entorno
    if (setenv(argv[1], argv[2], 1) != 0)//Llama a setenv para establecer una variable de entorno. argv[1] es el nombre de la variable y argv[2] es su valor. El 1 indica que se debe sobrescribir cualquier valor existente de la variable.
//Si setenv falla (retorna un valor diferente de 0), imprime un mensaje de error usando perror("setenv") y retorna 1 para indicar un error.

    {
        // Si setenv falla se imprime el mensaje de error
        perror("setenv");
        return 1; // Retornar 1 para indicar error
    }

    return 0; // Retornar 0 para indicar éxito
}

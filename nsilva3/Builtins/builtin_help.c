#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minish.h"

int builtin_help(int argc, char **argv)
{
    if (argc == 1)
    {
        for (int i = 0; builtin_arr[i].cmd != NULL; i++)//Se recorre el arreglo builtin_arr para encontrar el comando cuyo nombre coincide con argv[0]
        {
            if (strcmp(builtin_arr[i].cmd, argv[0]) == 0)//Si se encuentra una coincidencia, se imprime el texto de ayuda correspondiente
            {
            
                fprintf(stderr, "%s\n", builtin_arr[i].help_txt);//comando ya definido en minish h
            }
        }
    }

    else if (argc == 2)
    {
        for (int i = 0; builtin_arr[i].cmd != NULL; i++)//Se recorre el arreglo builtin_arr para encontrar el comando cuyo nombre coincide con argv[1]
        {
            if (strcmp(builtin_arr[i].cmd, argv[1]) == 0)
            {
        
                fprintf(stderr, "%s\n", builtin_arr[i].help_txt);//Si se encuentra una coincidencia, se imprime el texto de ayuda correspondiente
            }
        }
    }
    return 0; //La función siempre retorna 0, lo que indica que la operación fue exitosa.
}
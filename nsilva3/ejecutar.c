#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "minish.h"
/*ejecutar: decide si el argumento en argv[0] pertenece al conjunto de builtins. Si pertenece, lo ejecuta, y sino, intenta ejecutarlo como externo.
Devuelve el status devuelto por externo o la función del builtin.
*/
extern int
ejecutar(int argc, char **argv)
{
    if(argc == 0)//si no hay argumentos, no se hace nada
    {    
        return 0;//retorna 0 (no se ejecuto nada)
    }
    struct builtin_struct *builtin;
    builtin = builtin_lookup(argv[0]);//argv[0] busca en el array argv la 
    int status;//variable que guarda el status del comando
    if(builtin == NULL)//si no lo encuentra en el array de builtins, es un comando externo
    {
        return externo(argc, argv); //es un comando externo
    }
    status = builtin->func(argc,argv);//si lo encuentra en el array de builtins, ejecuta la funcion asociada al comando
    //builtin es un puntero a una estructura que contiene el nombre del comando y la funcion asociada
    return status;//retorna el status del comando
}

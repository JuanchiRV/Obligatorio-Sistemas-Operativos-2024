#include <stdlib.h>
#include "minish.h"

int builtin_status (int argc, char **argv){
    UNUSED(argc);//marcan los parámetros argc y argv como no utilizados para evitar advertencias del compilador
    UNUSED(argv);
    printf("%d\n", globalstatret);//"%d\n": Especifica que se va a imprimir un entero seguido de una nueva línea.
    //globalstatret: Es una variable global que contiene el estado de retorno del último comando ejecutado
    return 0;
}

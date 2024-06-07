#include <string.h>
#include "minish.h"
#include "wrappers.h"
#include "minish.c"//no sabemmos cual de los 2 archivos es el correcto

//builtin_lookup: recibe un comando y decide si pertenece al grupo de comandos builtin o externos.
//Retorna un puntero a la estructura de ese comando si es un builtin, CC, retorna NULL
struct builtin_struct *builtin_lookup(char *cmd){//cmd es un punter a cadena de caracteres
    struct builtin_struct *result;//inicializamos un puntero a una estructura de tipo builtin_struct
    result = NULL;//inicializamos el puntero a NULL
    for(int i = 0; builtin_arr[i].cmd != NULL; i++){//se itera sobre el array de builtins, 
        if(strcmp(builtin_arr[i].cmd, cmd)==0){//Compara la cadena cmd con el campo cmd del i-ésimo elemento de builtin_arr. strcmp devuelve 0 si las cadenas son iguales
            result = &builtin_arr[i];//se asigna la direccion de la estructura al puntero
        }
    }
    return result;//en caso de que no se encuentre, se retorna NULL
}

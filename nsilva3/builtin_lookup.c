#include <stdio.h>
#include <string.h>
#include "minish.c"//no sabemmos cual de los 2 archivos es el correcto
#include "minish.h"


// Function to lookup a built-in command
extern struct builtin_struct *builtin_lookup(char *cmd) {//declara una funcion llamada que toma un arguemnto cmd, que es un puntero a una cadena de caracteres y decuelve un puntero a una estructura de tipo builtin_struct
    int num_builtins = sizeof(builtin_arr) / sizeof(struct builtin_struct);//Calcula el número de elementos en el array builtin_arr dividiendo el tamaño total del array por el tamaño de un solo elemento.
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(cmd, builtin_arr[i].cmd) == 0) {//Compara la cadena cmd con el campo cmd del i-ésimo elemento de builtin_arr. strcmp devuelve 0 si las cadenas son iguales.
            return &builtin_arr[i];//Si las cadenas son iguales, devuelve un puntero al i-ésimo elemento de builtin_arr.
        }
    }
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "minish.h"

static int isChar(const void* ptr);
void save_history(void);
int
builtin_exit(int argc, char **argv){ //Definición de la función builtin_exit que toma dos argumentos: argc (número de argumentos) y argv (matriz de argumentos).
    save_history(); //Llama a la función save_history para guardar el historial antes de salir.
    if(argc==1){ //Si hay solo un argumento (el nombre del comando), ejecuta el siguiente bloque.
        exit(globalstatret); //Llama a exit con el valor de globalstatret y termina el programa.
        return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
    }
    else if(argc == 2){ //Si hay dos argumentos, ejecuta el siguiente bloque.
        if(isChar(&argv[2])){ //Si el tercer argumento (índice 2 en argv) es un carácter, ejecuta el siguiente bloque.
            error(1, 1, "ERROR, el argumento es inválido\n"); //Imprime un mensaje de error y termina el programa con un codigo de salida 1
            return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
        }
        int estado_salida; //Declara una variable estado_salida para almacenar el estado de salida.
        estado_salida = atoi(argv[2]); //Convierte el tercer argumento a un entero y lo almacena en estado_salida.
        exit(estado_salida); //Llama a exit con el valor de estado_salida y termina el programa.
        return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
   } else { //Si hay más de dos argumentos, ejecuta el siguiente bloque.
        error(1, 1, "ERROR, hay demasiados argumentos\n"); //Imprime y termina el programa con un código de salida de 1.
        return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
    }
    for (int i = 0; i < argc ; i++) { //Un bucle para liberar la memoria asignada para cada argumento en argv.
        free(argv[i]);
    }
    return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
}
static int //Definición de la función isChar que toma un puntero void y devuelve un entero.
isChar(const void* ptr){
    return(sizeof(*(char *)ptr) == sizeof(char));
    //Convierte el puntero void a un puntero char, desreferencia el puntero y compara el tamaño del objeto apuntado con el tamaño de un char.
    //Si son iguales, devuelve 1; de lo contrario, devuelve 0. Esto verifica si el puntero apunta a un char.
}

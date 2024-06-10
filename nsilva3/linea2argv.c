#include <stdio.h>       // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h>      // Incluye funciones de propósito general como malloc, exit, etc.
#include <string.h>      // Incluye funciones de manipulación de cadenas
#include "wrappers.h"    // Incluye funciones auxiliares definidas en wrappers.h

// Función que convierte una línea en un arreglo de argumentos
extern int
line_to_args(char *line, int max_args, char **args)
{
    int num_words = 0;       // Número de palabras encontradas
    int index = 0;           // Índice para recorrer la línea
    int start_pos = -1;      // Indica el inicio de una palabra

    // Bucle principal para recorrer la línea y separar palabras
    while (num_words < max_args && line[index] != '\n') {
        // Encuentra el inicio de una palabra
        if (line[index] != ' ' && line[index] != '\t' && start_pos == -1) {
            start_pos = index;  // Guarda la posición inicial de la palabra
        }

        // Encuentra el final de una palabra
        if (line[index] == ' ' || line[index] == '\t') {
            int word_length = index - start_pos;  // Calcula la longitud de la palabra

            args[num_words] = malloc_or_exit(word_length + 1);  // Reserva memoria para la palabra
            strncpy(args[num_words], &line[start_pos], word_length);  // Copia la palabra en args
            args[num_words][word_length] = '\0';  // Añade el terminador nulo al final de la palabra

            num_words++;
            start_pos = -1;  // Reinicia la variable
        }

        index++;
    }

    // Procesa la última palabra si no terminó en espacio/tabulador
    if (start_pos != -1) {
        int word_length = index - start_pos;

        args[num_words] = malloc_or_exit(word_length + 1);  // Reserva memoria para la palabra
        strncpy(args[num_words], &line[start_pos], word_length);  // Copia la palabra en args
        args[num_words][word_length] = '\0';  // Añade el terminador nulo al final de la palabra

        num_words++;
    }

    args[num_words] = NULL;  // Termina la lista de argumentos con NULL

    return num_words;  // Devuelve el número de palabras encontradas
}

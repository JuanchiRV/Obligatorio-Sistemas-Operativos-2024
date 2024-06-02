#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrappers.h"

int
linea2argv(char *linea, int argc, char **argv)
{
    int N = 0; //nuemero de palabras
    int i = 0;//variable para recorrer la lista
    int word_starts = -1;//indica si se encontro el principio de una palabra


    while (N < argc && linea[i] != '\n') {

        if (linea[i] != ' ' && linea[i] != '\t' && word_starts == -1) { //encontre principio de una palabra
            word_starts = i;//se guarda la posicion de la palabra
        }

        if (linea[i] == ' ' || linea[i] == '\t') { //encontre final de una palabra
            int str_len = i - word_starts;//se calcula la longitud de la palabra

            argv[N] = malloc_or_exit(str_len + 1);//se reserva memoria para la palabra y se guarda en argv

            strncpy(argv[N], &linea[word_starts], str_len);//se copia la palabra en argv
            argv[N][str_len] = '\0';//se agrega el caracter nulo al final de la palabra

            N++;
            word_starts = -1;//se reinicia la variable
        }

        i++;
    }
    if (word_starts != -1) {
        int str_len = i - word_starts;

        argv[N] = malloc(str_len + 1);
        strncpy(argv[N], &linea[word_starts], str_len);
        argv[N][str_len] = '\0';

        N++;
    }

    argv[N] = NULL;

    return N;

}
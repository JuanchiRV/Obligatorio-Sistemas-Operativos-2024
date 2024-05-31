#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrappers.h"

int
linea2argv(char *linea, int argc, char **argv)
{
    int N = 0; //nuemero de palabras
    int i = 0;
    int word_starts = -1;


    while (N < argc && linea[i] != '\n') {

        if (linea[i] != ' ' && linea[i] != '\t' && word_starts == -1) { //encontre principio de una palabra
            word_starts = i;
        }

        if (linea[i] == ' ' || linea[i] == '\t') { //encontre final de una palabra
            int str_len = i - word_starts;

            argv[N] = malloc_or_exit(str_len + 1);

            strncpy(argv[N], &linea[word_starts], str_len);
            argv[N][str_len] = '\0';

            N++;
            word_starts = -1;
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
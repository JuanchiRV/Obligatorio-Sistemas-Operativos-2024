#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "minish.h"

/*int ejecutar(int argc, char **argv) {//
    struct builtin_struct *builtin;
    int status;
    int isInternal = 0;
    for (int i = 0; i < sizeof(builtin) / sizeof(builtin[0]); i++) {
        if (strcmp(argv[0], builtin[i].cmd) == 0) {
            isInternal = 1;
            break;
        }
    }
    status = isInternal ? builtin->func(argc, argv) : externo(argc, argv);
    return status
}/*/
    
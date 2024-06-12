#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minish.h"  // Incluye las declaraciones necesarias
#include "wrappers.h"  // Incluye otras declaraciones necesarias

#define MAX_LINE 1024
#define MAX_ARGS 64


int main() {
    char *line;
    char *argv[MAX_ARGS];
    int argc;
    int status = 0;

    while (1) {
        line = read_line();
        argc = linea2argv(line, MAX_ARGS, argv);

        if (argc == 0) {
            free(line);
            continue;  // Si no hay comandos, continuar
        }

        struct builtin_struct *builtin_cmd = builtin_lookup(argv[0]);
        if (builtin_cmd != NULL) {
            status = builtin_cmd->func(argc, argv);
        } else {
            status = externo(argc, argv);
        }

        free(line);
        // Liberar memoria de los argumentos
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }
    }

    return 0;
}

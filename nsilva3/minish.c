#include <stdio.h>
#include "wrappers.h"
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "minish.h"

#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"
#define HELP_COPIAR "copiar archivo_origen archivo_destino || copiar archivo_origen [archivo_origen ...] dir_destino" //a chequiar
#define HELP_GID     "gid - muestra el grupo principal y los grupos secundarios" //a cheq
#define HELP_UNSETENV "unsetenv var [var] - elimina variables de ambiente" //nosottos 



struct builtin_struct builtin_arr[] = {
    { "cd", builtin_cd, HELP_CD },
    { "status", builtin_status, HELP_STATUS},
    { "help", builtin_help, HELP_HELP},
    { "exit", builtin_exit, HELP_EXIT},
    { "pid", builtin_pid, HELP_PID},
    { "gid", builtin_gid, HELP_GID},
    { "getenv", builtin_getenv, HELP_GETENV},
    { "setenv", builtin_setenv, HELP_SETENV},
    { "unsetenv", builtin_unsetenv, HELP_UNSETENV},
    { "dir", builtin_dir, HELP_DIR},
    { "history", builtin_history, HELP_HISTORY},
    { "uid", builtin_uid, HELP_UID },
    { NULL, NULL, NULL } 
};  

int globalstatret;//para builtin_status y exit


int main() {
    size_t len = 0;             // Variable para almacenar la longitud de la línea, inicializada a 0
    char *line = NULL;         // Puntero para almacenar la línea de entrada del usuario, inicializado a NULL
    char *argv[64];             // Arreglo de punteros para almacenar los argumentos de la línea
    int argc;                   // Número de argumentos
    while (1) {                 // Bucle infinito para el shell interactivo
        printf("(minish) %s:%s > ", getenv("USER"), getenv("PWD")); // Imprime el prompt del shell con el usuario y directorio actual
        if (getline(&line, &len, stdin) == -1) { // Lee una línea de entrada; si hay un error, sale del programa
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (strlen(line) > 1) {  // Si la línea no está vacía (más de 1 carácter), la agrega al historial
            history_agregar(line);
        }
        argc = linea2argv(line, 64, argv); // Convierte la línea en una lista de argumentos y obtiene el número de argumentos
        if (argc > 0) {            // Si hay al menos un argumento, ejecuta el comando
            ejecutar(argc, argv);
        }
    }
    
    return 0;                      // Termina la función main y devuelve 0, indicando éxito
}

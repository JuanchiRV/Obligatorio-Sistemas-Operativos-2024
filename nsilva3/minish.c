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
    { "copiar", builtin_copiar, HELP_COPIAR },
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

int globalstatret;//para builtin_status

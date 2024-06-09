#include <stdio.h>       // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h>      // Incluye funciones de propósito general como malloc, exit, etc.
#include <unistd.h>      // Incluye la API de POSIX como getlogin, getgid, etc.
#include <string.h>      // Incluye funciones de manipulación de cadenas
#include <grp.h>         // Incluye funciones para obtener información de grupos
#include <error.h>       // Incluye funciones para manejo de errores
#include <errno.h>       // Incluye definiciones para reportar errores del sistema
#include "wrappers.h"    // Incluye funciones auxiliares definidas en wrappers.h
#include "minish.h"      // Incluye definiciones y funciones para el programa minish
#define MAX_GRPS 500     // Define el número máximo de grupos que se pueden manejar

// Función que implementa el comando show_user_groups, que muestra el grupo principal y los grupos secundarios del usuario
int
show_user_groups(int arg_count, char **arg_values)
{
    gid_t main_gid = getgid(); // Obtiene el ID del grupo principal del usuario
    char *user_name = getlogin(); // Obtiene el nombre de usuario del proceso actual
    fprintf(stderr, "Real GID: %d(%s)\n", (int) main_gid, user_name); // Imprime el ID del grupo principal y el nombre de usuario

    gid_t group_array[MAX_GRPS]; // Declara un arreglo para almacenar los IDs de los grupos secundarios
    int group_count = getgroups(MAX_GRPS, group_array); // Obtiene la lista de grupos secundarios del usuario

    // Verifica si la llamada a getgroups falló
    if (group_count < 0){
        error(ERROR, errno, "Error al obtener grupos\n"); // Imprime un mensaje de error
        return EXIT_FAILURE; // Devuelve un código de error y sale de la función
    }

    fprintf(stderr,"Grupos: "); // Imprime el encabezado de la lista de grupos secundarios
    // Itera sobre la lista de grupos secundarios
    for (int i = 0; i < group_count; i++){
        struct group *grp_info = getgrgid(group_array[i]); // Obtiene la estructura del grupo a partir del ID
        if (grp_info != NULL){
            // Imprime el ID y el nombre del grupo si se pudo obtener la información del grupo
            fprintf(stderr, "%d (%s) ", grp_info->gr_gid, grp_info->gr_name);
        }
    }
    printf("\n"); // Imprime un salto de línea al final de la lista de grupos
    return EXIT_SUCCESS; // Devuelve un código de éxito y sale de la función
}

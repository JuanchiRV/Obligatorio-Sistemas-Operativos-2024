#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minish.h"
#include "../wrappers.h"

struct hist_st *history_inicializar(FILE *fp) // Inicializa la estructura de historial
{
    struct hist_st *history = malloc_or_exit(sizeof(struct hist_st)); // Asigna memoria para la estructura
    history->arraysize = 10; // Tamaño inicial del array de líneas
    history->used = 0; // Inicialmente no hay líneas usadas
    history->linearray = calloc_or_exit(history->arraysize, sizeof(char *)); // Asigna memoria para el array de líneas

    char line[MAXLINE];
    while (fgets(line, sizeof(line), fp)) // Lee líneas del archivo
    {
        line[strcspn(line, "\n")] = 0; // Elimina el salto de línea
        history_agregar(history, line); // Añade la línea al historial
    }

    return history; // Devuelve la estructura de historial
}
void history_mostrar(struct hist_st *history, size_t n) // Muestra las últimas n líneas del historial
{
    if (n > history->used) // Ajusta n si es mayor que el número de líneas usadas
    {
        n = history->used;
    }
    for (size_t i = history->used - n; i < history->used; i++) // Imprime las últimas n líneas
    {
        printf("%s\n", history->linearray[i]);
    }
}
void history_liberar(struct hist_st *history) // Libera la memoria de la estructura de historial
{
    for (size_t i = 0; i < history->used; i++) // Libera cada línea almacenada
    {
        free(history->linearray[i]);
    }
    free(history->linearray); // Libera el array de punteros
    free(history); // Libera la estructura de historial
}

void history_guardar(struct hist_st *history, FILE *fp) // Guarda el historial en un archivo
{
    for (size_t i = 0; i < history->used; i++) // Itera sobre todas las líneas usadas
    {
        fprintf(fp, "%s\n", history->linearray[i]); // Escribe cada línea en el archivo
    }
}

int builtin_history(int argc, char **argv) // Comando incorporado que muestra el historial
{
    size_t n = 10;
    if (argc > 1) // Si hay un argumento, lo convierte a entero y lo usa como n
    {
        n = atoi(argv[1]);
    }
    history_mostrar(history_session_lines, n); // Muestra las últimas n líneas
    return 0;
}
struct hist_st *history_agregar(struct hist_st *history, char *line) // Añade una línea al historial
{
    if (history->used == history->arraysize) // Duplica el tamaño del array si está lleno
    {
        history->arraysize *= 2;
        history->linearray = reallocarray_or_exit(history->linearray, history->arraysize, sizeof(char *));
    }
    history->linearray[history->used] = strdup_or_exit(line); // Duplica la línea y la almacena
    history->used++; // Incrementa el contador de líneas usadas
    return history; // Devuelve la estructura de historial
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minish.h"
#include "../wrappers.h"

// Inicializa el historial desde un archivo
struct hist_st *history_init(FILE *fp)
{
    // Asigna memoria para la estructura de historial y verifica errores
    struct hist_st *history = malloc_or_exit(sizeof(struct hist_st));
    history->arraysize = 10; // Tamaño inicial del array de líneas
    history->used = 0;       // Inicialmente no hay líneas usadas
    // Asigna memoria para el array de líneas y verifica errores
    history->linearray = calloc_or_exit(history->arraysize, sizeof(char *));

    char line[MAXLINE]; // líne del archivo
    while (fgets(line, sizeof(line), fp))
    {
        // Elimina el carácter de nueva línea al final de la línea leída
        line[strcspn(line, "\n")] = 0;
        // Añade la línea al historial
        history_addline(history, line);
    }

    return history; // Retorna el historial inicializado
}

// Añade una línea al historial
struct hist_st *history_addline(struct hist_st *history, char *line)
{
    // Si el array de líneas está lleno se duplica su tamaño
    if (history->used == history->arraysize)
    {
        history->arraysize *= 2;
        // Realoca memoria para el array de líneas y verifica errores
        history->linearray = reallocarray_or_exit(history->linearray, history->arraysize, sizeof(char *));
    }
    // Duplica la línea y la añade al array de líneas
    history->linearray[history->used] = strdup_or_exit(line);
    history->used++; // Incrementa el contador de líneas usadas
    return history;  // Retorna el historial actualizado
}

// Muestra las últimas N líneas del historial
void history_show(struct hist_st *history, size_t n)
{
    // Si N es mayor que el número de líneas usadas se ajusta a este valor
    if (n > history->used)
    {
        n = history->used;
    }
    // Imprimir las últimas N líneas del historial
    for (size_t i = history->used - n; i < history->used; i++)
    {
        printf("%s\n", history->linearray[i]);
    }
}

// Guarda el historial en un archivo
void history_save(struct hist_st *history, FILE *fp)
{
    // Escribir cada línea del historial en el archivo
    for (size_t i = 0; i < history->used; i++)
    {
        fprintf(fp, "%s\n", history->linearray[i]);
    }
}

// Libera la memoria del historial
void history_free(struct hist_st *history)
{
    // Liberar cada línea en el array de líneas
    for (size_t i = 0; i < history->used; i++)
    {
        free(history->linearray[i]);
    }
    // Liberar el array de líneas y la estructura de historial
    free(history->linearray);
    free(history);
}

int builtin_history(int argc, char **argv)
{
    size_t n = 10; // Valor por defecto
    if (argc > 1)
    {
        n = atoi(argv[1]);
    }
    // Mostrar las últimas N líneas del historial
    history_show(history_session_lines, n);
    return 0; // Retornar 0 para indicar éxito
}
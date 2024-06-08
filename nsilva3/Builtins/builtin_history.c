#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include "minish.h"
#include "wrappers.h"

#define HISTORY_FILE ".minish_history" //el nombre del archivo donde se almacenará el historial de comandos.
#define MAX_LINE_LENGTH 256 //la longitud máxima de una línea de comando.
#define ERROR 1

struct deq *history; //Se declara una variable global history que apunta a una estructura deq. Esta variable se utilizará para almacenar el historial de comandos.

int builtin_history(int argc, char **argv){
    int N;
    if (argc == 1){ //Si no se proporciona ningún argumento, se establece N en 10.
        N = 10;
    }else if (argc == 2){
        N = atoi(argv[1]); //Si se proporciona un argumento, se convierte a un entero (N = atoi(argv[1])
        if(N == 0){
            error(0,errno,"ERROR, %s no es un numero valido\n",argv[1]);
            return 1; //Si el argumento no es un número válido (0), se imprime un mensaje de error y se devuelve un código de error.
        }
    }else{
        perror("ERROR, se han ingresado demasiados argumentos\n");
        return 1; //Si se proporcionan más de un argumento, se imprime un mensaje de error y se devuelve un código de error.
    }
    struct node *temp; //Se declara una variable temp que apunta a una estructura node.
    if (history -> qty < N) { //Se comprueba si la cantidad de elementos en el historial (history->qty) es menor que N
        temp = history -> first; //Si es así, temp se establece en el primer nodo del historial (history->first).
    }else{ 
        temp = history -> last;
        for (int i = 1; i < N; i++){
            temp = temp -> prev;
        } //De lo contrario, temp se establece en el último nodo del historial (history->last) y se retrocede N - 1 veces desde el último nodo.
    }
    for (int i = 1; temp != NULL; i++){ //Se recorre la lista enlazada a partir de temp e imprime cada comando del historial junto con su índice.
        fprintf(stderr,"%d : %s",i, temp -> content);
        temp = temp -> next ; //El bucle continúa hasta que temp sea NULL.
    }
    return 0;
}

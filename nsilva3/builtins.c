#include <stdio.h>       // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h>      // Incluye funciones de propósito general como malloc, exit, etc.
#include <unistd.h>      // Incluye la API de POSIX como getlogin, getgid, etc.
#include <string.h>      // Incluye funciones de manipulación de cadenas
#include <grp.h>         // Incluye funciones para obtener información de grupos
#include <error.h>       // Incluye funciones para manejo de errores
#include <errno.h>       // Incluye definiciones para reportar errores del sistema
#include "wrappers.h"    // Incluye funciones auxiliares definidas en wrappers.h
#include "minish.h"      // Incluye definiciones y funciones para el programa minish
#include "minish.c"      // Incluye definiciones y funciones para el programa minish
#include <pwd.h>
#include "shell.h"
#include "../minish.h"

#define MAXCWD 1024




extern int builtin_cd(int argc, char **argv) {
    // Si se pasa un argumento al comando cd
    if (argc == 2) {
        char camino[MAXCWD]; // Buffer para almacenar el camino especificado
        strcpy(camino, argv[1]); // Copia el camino especificado en el buffer 'camino'
        char direct[MAXCWD]; // Buffer para almacenar el directorio actual
        
        // Si el camino especificado no es absoluto
        if (argv[1][0] != '/') {
            // Si el argumento es '-', se cambia al directorio anterior
            if (argv[1][0] == '-') {
                // Obtiene el directorio actual y lo guarda en 'direct'
                if (getcwd(direct, sizeof(direct)) == NULL) {
                    perror("getcwd error"); // Imprime un mensaje de error si getcwd falla
                    return 1; // Retorna 1 indicando error
                }
                // Cambia al directorio almacenado en la variable de ambiente OLDPWD
                if (chdir(getenv("OLDPWD")) != 0) {
                    perror("chdir error"); // Imprime un mensaje de error si chdir falla
                    return 1; // Retorna 1 indicando error
                }
                setenv("OLDPWD", direct, 1); // Actualiza OLDPWD con el valor de direct
                setenv("PWD", getenv("OLDPWD"), 1); // Actualiza PWD con el valor de OLDPWD
                return 0; // Retorna 0 indicando éxito
            }
            // Obtiene el directorio actual y lo guarda en 'direct'
            if (getcwd(direct, sizeof(direct)) == NULL) {
                perror("getcwd error"); // Imprime un mensaje de error si getcwd falla
                return 1; // Retorna 1 indicando error
            }
            setenv("OLDPWD", direct, 1); // Actualiza OLDPWD con el valor de direct
            strcat(direct, "/"); // Añade un separador '/' al final de direct
            strcat(direct, camino); // Concatenar el camino relativo al directorio actual
            // Cambia al directorio concatenado (relativo)
            if (chdir(direct) != 0) {
                perror("chdir error"); // Imprime un mensaje de error si chdir falla
                return 1; // Retorna 1 indicando error
            }
            setenv("PWD", direct, 1); // Actualiza PWD con el nuevo directorio
            return 0; // Retorna 0 indicando éxito
        }
        // Si el camino especificado es absoluto, cambia directamente a ese directorio
        if (chdir(camino) != 0) {
            perror("chdir error"); // Imprime un mensaje de error si chdir falla
            return 1; // Retorna 1 indicando error
        }
        setenv("PWD", camino, 1); // Actualiza PWD con el nuevo directorio
        return 0; // Retorna 0 indicando éxito
    }

    // Si no se pasa ningún argumento, cambia al directorio HOME
    if (argc == 1) {
        if (chdir(getenv("HOME")) != 0) {
            perror("chdir error"); // Imprime un mensaje de error si chdir falla
            return 1; // Retorna 1 indicando error
        }
        setenv("PWD", getenv("HOME"), 1); // Actualiza PWD con el directorio HOME
        return 0; // Retorna 0 indicando éxito
    }

    // Si se pasa un número incorrecto de argumentos, imprime el mensaje de ayuda
    printf("Use help cd para ver el funcionamiento de cd\n");
    return 1; // Retorna 1 indicando error
}

static int isChar(const void* ptr);
void save_history(void);
extern int
builtin_exit(int argc, char **argv){ //Definición de la función builtin_exit que toma dos argumentos: argc (número de argumentos) y argv (matriz de argumentos).
    save_history(); //Llama a la función save_history para guardar el historial antes de salir.
    if(argc==1){ //Si hay solo un argumento (el nombre del comando), ejecuta el siguiente bloque.
        exit(globalstatret); //Llama a exit con el valor de globalstatret y termina el programa.
        return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
    }
    else if(argc == 2){ //Si hay dos argumentos, ejecuta el siguiente bloque.
        if(isChar(&argv[2])){ //Si el tercer argumento (índice 2 en argv) es un carácter, ejecuta el siguiente bloque.
            error(1, 1, "ERROR, el argumento es inválido\n"); //Imprime un mensaje de error y termina el programa con un codigo de salida 1
            return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
        }
        int estado_salida; //Declara una variable estado_salida para almacenar el estado de salida.
        estado_salida = atoi(argv[2]); //Convierte el tercer argumento a un entero y lo almacena en estado_salida.
        exit(estado_salida); //Llama a exit con el valor de estado_salida y termina el programa.
        return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
   } else { //Si hay más de dos argumentos, ejecuta el siguiente bloque.
        error(1, 1, "ERROR, hay demasiados argumentos\n"); //Imprime y termina el programa con un código de salida de 1.
        return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
    }
    for (int i = 0; i < argc ; i++) { //Un bucle para liberar la memoria asignada para cada argumento en argv.
        free(argv[i]);
    }
    return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
}
static int //Definición de la función isChar que toma un puntero void y devuelve un entero.
isChar(const void* ptr){
    return(sizeof(*(char *)ptr) == sizeof(char));
    //Convierte el puntero void a un puntero char, desreferencia el puntero y compara el tamaño del objeto apuntado con el tamaño de un char.
    //Si son iguales, devuelve 1; de lo contrario, devuelve 0. Esto verifica si el puntero apunta a un char.
}


extern int
builtin_getenv(int argc, char **argv)
{
    extern char **environ;//environ es una variable global que almacena todas las variables de entorno y sus valores en el formato nombre=valor
    if (argc==1){
        char **puntero = environ;//char **puntero: Declara un puntero a puntero a char
        for (int i=0; puntero[i]!=NULL; i++){
            fprintf(stderr, "%s\n", puntero[i]);//Imprime la cadena puntero[i] (la entrada actual en environ) en el flujo de error estándar (stderr).
        }
    }
    for (int i=1; i<argc; i++){//esto es para recorrer los demas argumentos
        char *var_env = getenv(argv[i]);//getenv para obtener el valor de la variable de entorno especificada por argv[i]
        if (var_env == NULL){//si retorna null, imprime un error
            error(1, errno, "getenv %s error", argv[i]);
            return EXIT_FAILURE;
        }
        fprintf(stderr, "%s=%s\n", argv[i], var_env);//Si getenv encuentra la variable de entorno, imprime su nombre y valor en stderr
    }
    return EXIT_SUCCESS;        
}

#define MAX_GRPS 500     // Define el número máximo de grupos que se pueden manejar
// Función que implementa el comando show_user_groups, que muestra el grupo principal y los grupos secundarios del usuario
extern int
show_user_groups(int arg_count, char **arg_values)
{
    gid_t main_gid = getgid(); // Obtiene el ID del grupo principal del usuario
    char *user_name = getlogin(); // Obtiene el nombre de usuario del proceso actual
    fprintf(stderr, "GID: %d(%s)\n", (int) main_gid, user_name); // Imprime el ID del grupo principal y el nombre de usuario

    gid_t group_array[MAX_GRPS]; // Declara un arreglo para almacenar los IDs de los grupos secundarios
    int group_count = getgroups(MAX_GRPS, group_array); // Obtiene la lista de grupos secundarios del usuario

    // Verifica si la llamada a getgroups falló
    if (group_count < 0){
        error(ERROR, errno, "Error obteniendo grupos\n"); // Imprime un mensaje de error
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

extern int builtin_help(int argc, char **argv)
{
    if (argc == 1)
    {
        for (int i = 0; builtin_arr[i].cmd != NULL; i++)//Se recorre el arreglo builtin_arr para encontrar el comando cuyo nombre coincide con argv[0]
        {
            if (strcmp(builtin_arr[i].cmd, argv[0]) == 0)//Si se encuentra una coincidencia, se imprime el texto de ayuda correspondiente
            {
            
                fprintf(stderr, "%s\n", builtin_arr[i].help_txt);//comando ya definido en minish h
            }
        }
    }

    else if (argc == 2)
    {
        for (int i = 0; builtin_arr[i].cmd != NULL; i++)//Se recorre el arreglo builtin_arr para encontrar el comando cuyo nombre coincide con argv[1]
        {
            if (strcmp(builtin_arr[i].cmd, argv[1]) == 0)
            {
        
                fprintf(stderr, "%s\n", builtin_arr[i].help_txt);//Si se encuentra una coincidencia, se imprime el texto de ayuda correspondiente
            }
        }
    }
    return 0; //La función siempre retorna 0, lo que indica que la operación fue exitosa.
}


extern struct hist_st *history_inicializar(FILE *fp) // Inicializa la estructura de historial
{
    struct hist_st *history = malloc_or_exit(sizeof(struct hist_st)); // Asigna memoria para la estructura
    history->used = 0; // Inicialmente no hay líneas usadas
    history->arraysize = 10; // Tamaño inicial del array de líneas
    history->linearray = calloc_or_exit(history->arraysize, sizeof(char *)); // Asigna memoria para el array de líneas
    char linea[MAXLINE];
    while (fgets(linea, sizeof(linea), fp)) // Lee líneas del archivo
    {
        line[strcspn(linea, "\n")] = 0; // Elimina el salto de línea
        history_agregar(history, linea); // Añade la línea al historial
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
extern int builtin_history(int argc, char **argv) // Comando incorporado que muestra el historial
{
    size_t n = 10;
    if (argc > 1) // Si hay un argumento, lo convierte a entero y lo usa como n
    {
        n = atoi(argv[1]);
    }
    history_mostrar(history_session_lines, n); // Muestra las últimas n líneas
    return 0;
}
extern struct hist_st *history_agregar(struct hist_st *history, char *line) // Añade una línea al historial
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


// Function to lookup a built-in command
extern struct builtin_struct *builtin_lookup(char *cmd) {//declara una funcion llamada que toma un arguemnto cmd, que es un puntero a una cadena de caracteres y decuelve un puntero a una estructura de tipo builtin_struct
    int num_builtins = sizeof(builtin_arr) / sizeof(struct builtin_struct);//Calcula el número de elementos en el array builtin_arr dividiendo el tamaño total del array por el tamaño de un solo elemento.
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(cmd, builtin_arr[i].cmd) == 0) {//Compara la cadena cmd con el campo cmd del i-ésimo elemento de builtin_arr. strcmp devuelve 0 si las cadenas son iguales.
            return &builtin_arr[i];//Si las cadenas son iguales, devuelve un puntero al i-ésimo elemento de builtin_arr.
        }
    }
    return NULL;
}

extern int builtin_pid (int argc, char **argv){
    UNUSED(argc);//Se declara argc como no utilizado para evitar un warning durante compilacion.
    UNUSED(argv);
    printf("Process ID is: %d\n", getpid());//Imprime el id del proceso actual.
    return 0;//Devuelve 0 indicando una salida exitosa.

    }


extern int builtin_setenv(int argc, char **argv)
{
    if (argc != 3)
    {
        // Si no hay 3 argumentos se imprime el mensaje de error y la forma correcta del comando
        fprintf(stderr, "Error en el comando, escribelo así: setenv <variable> <valor>\n");
        return 1; // Retornar 1 para indicar error
    }

    // Se establece la variable de entorno
    if (setenv(argv[1], argv[2], 1) != 0)//Llama a setenv para establecer una variable de entorno. argv[1] es el nombre de la variable y argv[2] es su valor. El 1 indica que se debe sobrescribir cualquier valor existente de la variable.
//Si setenv falla (retorna un valor diferente de 0), imprime un mensaje de error usando perror("setenv") y retorna 1 para indicar un error.

    {
        // Si setenv falla se imprime el mensaje de error
        perror("setenv");
        return 1; // Retornar 1 para indicar error
    }

    return 0; // Retornar 0 para indicar éxito
}

extern int builtin_status (int argc, char **argv){
    UNUSED(argc);//marcan los parámetros argc y argv como no utilizados para evitar advertencias del compilador
    UNUSED(argv);
    printf("%d\n", globalstatret);//"%d\n": Especifica que se va a imprimir un entero seguido de una nueva línea.
    //globalstatret: Es una variable global que contiene el estado de retorno del último comando ejecutado
    return 0;
}


extern int
builtin_uid(int argc, char **argv)
{
    if(argc == 1 || strcmp(argv[0], "uid") == 0)//Si alguna de estas condiciones es verdadera, la función simplemente continúa sin hacer nada en este bloque (; es una instrucción vacía).
    {
        ;
    }
    uid_t userid = getuid();//getuid(): Llama a la función del sistema que devuelve el UID del usuario que está ejecutando el programa.
    struct passwd *usuario = getpwuid(userid);// Llama a la función del sistema que toma un UID y devuelve un puntero a una estructura passwd que contiene información sobre el usuario.
//user: Variable que almacena el puntero a la estructura passwd.
    if (usuario != NULL){//Imprime un mensaje en stderr con el nombre de usuario (user->pw_name) y el UID (userid).
        fprintf(stderr, "ID usuario %s es: %d\n", usuario->pw_name, userid);
        return EXIT_SUCCESS;//Retorna EXIT_SUCCESS (generalmente definido como 0) para indicar que la operación fue exitosa.
    }
    else {
        printf("Error, no se encontro informacion del usuario\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

extern int
builtin_unsetenv(int argc, char **argv)
{
    if(argc==1){ //Si hay solo un argumento (el nombre del comando), ejecuta el siguiente bloque.
        fprintf(stderr, "ERROR, los argumentos son insuficientes.\n"); //Imprime el mensaje en la salida estándar de error (stderr).
        return EXIT_FAILURE; //Devuelve EXIT_FAILURE (1) indicando una salida con error.
    }
    for(int i = 1; i<=argc; i++){
        unsetenv(argv[i]); //Llama a la función unsetenv para eliminar la variable de entorno especificada en argv[i].
    }
    return EXIT_SUCCESS; //Devuelve EXIT_SUCCESS (0) indicando una salida exitosa.
}

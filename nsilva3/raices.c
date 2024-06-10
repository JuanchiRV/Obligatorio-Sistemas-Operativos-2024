include <stdio.h>
include<math.h>
#include <stdio.h>
#include <math.h>
#define Min1
#define Max10
int main() {
    int i;
    
    printf(" Nro   Raiz\n");
    printf(" ---   -----\n");
    
    for (i = MIN; i <= MAX; i++) {
        printf("%3d   %.4f\n", i, sqrt(i));
    }
    
    return 0;
}


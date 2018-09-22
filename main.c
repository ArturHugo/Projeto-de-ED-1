#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

//A estrutura atual da main esta voltada ao teste de LeDados
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Erro - numero de argumentos incorreto.\n");
        exit(1);
    }

    Fila* f = LeDados(argv[1]);

    FreeFila(f);

    return 0;
}
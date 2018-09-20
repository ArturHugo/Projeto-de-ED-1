#include <stdio.h>
#include <stdlib.h> //Malloc() e free()
#include "headers.h"



int main(int argc, char** argv){
    if(argc != 2){
        printf("Quantidade de argumentos invalida\n");
        exit(1);
    }
    Fila *PrimeiraFila;
    Cliente *C;
    PrimeiraFila=LeDados(argv[1]);
    int a = FVazia(PrimeiraFila);
    while(!FVazia(PrimeiraFila)){
        C=TiraCliente(PrimeiraFila);
        printf("%d %d\n",C->cond, C->idade);
        free(C);
    }
    return 0;
}
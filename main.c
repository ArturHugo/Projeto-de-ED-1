#include <stdio.h>
#include <stdlib.h>
#include "headers.h"


int main(int argc, char *argv[]){
    /* Para a execução do programa caso os arquivos não tenham sido informados na linha de comando */
    if(argc != 4){
        printf("Erro na quantidade de parametros para a utilização do programa.\n");
        printf("Por favos dê 3 arquivos para leitura/escrita de dados... \nParando...\n");
        exit(1);
    }
    Fila* Guiches;
    Guiches=LeDadosGuiches(argv[2]);
    return 0;
}
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
    /* Leitura de Dados */
    Fila* Guiches, *Clientes;
    Guiches=LeDadosGuiches(argv[2]);
    Clientes=LeDadosClientes(argv[1]);

    /* Separação de Variaveis */
    Fila **GuicheLivre;
    Fila **GuicheOcupado;
    Guiche* TrocadeFila;
    GuicheLivre=Separa5Guiches(Guiches);
    



    /* Free Nos dados Alocados */
    FreeFila(Clientes);
    FreeFila(GuicheLivre[0]);
    FreeFila(GuicheLivre[2]);
    FreeFila(GuicheLivre[3]);
    FreeFila(GuicheLivre[4]);
    FreeFila(GuicheLivre[1]);
    free(GuicheLivre);
    FreeFila(Guiches);

    return 0;
}
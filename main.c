#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

/* Não executar esse programa */
int main(int argc, char *argv[]){
    /* Para a execução do programa caso os arquivos não tenham sido informados na linha de comando */
    if(argc != 4){
        printf("Erro na quantidade de parametros para a utilização do programa.\n");
        printf("Por favos dê 3 arquivos para leitura/escrita de dados... \nParando...\n");
        exit(1);
    }

    Fila* Guiches, *ClientesChegando;           //Variaveis para entrada de dados
    InfoGlobal InformGeral;                     //Struct que armazena informações sobre o final do simulador
    int tempo=0;                                //Auxiliar para receber o tempo de duração da simulação (em unidades de tempo)
    Fila* ClientesAtendidos;                    //Variavel para armazenar Fila depois do atendimento 

    /* Leitura de Dados */
    Guiches=LeDadosGuiches(argv[1]);            //Cria uma fila Com os dados lidos dos guiches e passa-a para "Guiches"
    ClientesChegando=LeDadosClientes(argv[2]);  //Cria uma fila com os dados dos clientes Organizando-os por tempo de chegada e passa-a para "ClientesChegando"

    /* Simulador do Laboratorio*/
    ClientesAtendidos=Simulador(ClientesChegando,Guiches,&tempo);

    /* Calculo das informações adicionais sobre a Simulação */
    InformGeral.tempoMedio = CalculaTempodeEsperaMedio(ClientesAtendidos);
    InformGeral.clientePorTempo = (float)ClientesAtendidos->tamanho/(tempo);     

    /* Escreve arquivo de Saida com os dados adiquiridos */                                       
    EscreveRelatorio( argv[3] ,InformGeral, ClientesAtendidos);

    /* Liberação dos dos dados alocados para leitura*/
    FreeFila(ClientesChegando);
    FreeFila(Guiches);

    return 0;
}

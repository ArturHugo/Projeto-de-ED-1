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
    /* Leitura de Dados */
    Fila* Guiches, *ClientesChegando;
    Guiches=LeDadosGuiches(argv[2]);
    ClientesChegando=LeDadosClientes(argv[1]);

    /* Criação de Filas auxiliares */
    Fila **GuicheLivre;                         //Fila Dos GUICHES livre
    Fila **GuicheOcupado;                       //Fila dos GUICHES ocupados
    Fila *ClientesAtendidos;                    //Fila dos Clientes que já foram atendidos
    Fila **ClientesNaLoja;                      //Fila dos CLIENTES para cada tipo de guiche
    Guiche* TrocadeFila;
    GuicheLivre=Separa5Guiches(Guiches);        //Separa no index n de GuicheLivre os guiches de serviço n 
    ClientesAtendidos=CriaFilaVazia();          //No inicio da execução não existem Pessoas já atendidas
    GuicheOcupado=Cria5Filas();                 //No incio da execução as 5 filas dos guiches ocuapdos está vazia
    ClientesNaLoja=Cria5Filas();                //No inicio da execução as 5 filas dos clientes na loja estão vazias
    
    /* Variaveis Auxiliares */
    int tempo=0;
    int tempoServico[5]={5,10,8,7,2};           //Pode ser ajustado pra alocamento dinamico posteriormente;
    Cliente* foiAtendido; Cliente* Pessoa;
    Guiche* guicheAux;   

    /* Iteração principal é Feita enquanto há alguem na fila de Chegada E na Fila dos guiches */
    while(!FVazia(ClientesChegando) || !(FVazia(GuicheOcupado[0]) && FVazia(GuicheOcupado[1]) && FVazia(GuicheOcupado[2]) && FVazia(GuicheOcupado[3]) && FVazia(GuicheOcupado[4]))){               
        
        /* Tirar todas as pessoas com tempo de chegada igual ao Tempo */
        /* Botar as pessoas que chegaram nas filas dos Guiches respectivos (organizados por prioridade) */
            /* Falta Criar Filas pra Clientes Com Guiche como base */
        while(!FVazia(ClientesChegando)){
            Pessoa=(Cliente*)ClientesChegando->Head->prox->info;
            if(Pessoa->tempo_chegada == tempo){
                Pessoa=TiraElementoDaFila(ClientesChegando);
                InsereClientePrioridade(ClientesNaLoja[Pessoa->serv], Pessoa);
            }
            else break;
        }
        

        /*  Ver se tem guiches disponiveis (um pra cada tipo) para botar as pessoas para serem atendidas */
            /* Lembrar de gravar o tempo em que cada pessoa começou a ser atendida */ 
        for(int i=0;i<5;i++){
            while(!FVazia(GuicheOcupado[i])){
                guicheAux=GuicheOcupado[i]->Head->prox->info;
                if((guicheAux->tempoUltimoAtendimento + tempoServico[i]) == tempo){
                    guicheAux = TiraElementoDaFila(GuicheOcupado[i]);
                    InserirNaFila(GuicheLivre[i], guicheAux);
                }
                else break;
            }
            while(!FVazia(GuicheLivre[i])){
                if(!FVazia(ClientesNaLoja[i])){
                    foiAtendido=TiraElementoDaFila(ClientesNaLoja[i]);
                    guicheAux = TiraElementoDaFila(GuicheLivre[i]);

                    foiAtendido->tempo_inicio=tempo;
                    foiAtendido->guiche=guicheAux->num;
                    guicheAux->tempoUltimoAtendimento=tempo;


                    InserirNaFila(ClientesAtendidos,foiAtendido);
                    InserirNaFila(GuicheOcupado[i],guicheAux);
                }
                else break;
            }
        }
        /* Tirar as pessoas que acabaram de ser atendidas e passar elas para uma fila exterior */


        tempo++;
    }

    /* Usar dados Contidos na Fila de clientes final para tirar informações */

    InfoGlobal Glob;
    Glob.clientePorTempo=10;
    Glob.tempoMedio=10;
    EscreveRelatorio( argv[3] ,Glob, ClientesAtendidos);

    /* Free Nos dados Alocados */
    //FreeFila(ClientesAtendidos);
    FreeFila(ClientesChegando);
    for(int i=0;i<5;i++){
        FreeFila(ClientesNaLoja[i]);
        FreeFila(GuicheLivre[i]);
        FreeFila(GuicheOcupado[i]);
    }
    free(ClientesNaLoja);
    free(GuicheOcupado);
    free(GuicheLivre);
    FreeFila(Guiches);

    return 0;
}
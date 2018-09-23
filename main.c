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
    Guiches=LeDadosGuiches(argv[2]);            //Cria uma fila Com os dados lidos dos guiches e passa-a para "Guiches"
    ClientesChegando=LeDadosClientes(argv[1]);  //Cria uma fila com os dados dos clientes Organizando-os por tempo de chegada e passa-a para "ClientesChegando"

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

    /* Iteração principal é Feita enquanto há alguem na fila de Chegada ou na Fila dos guiches */
    while(!FVazia(ClientesChegando) || !(FVazia(GuicheOcupado[0]) && FVazia(GuicheOcupado[1]) && FVazia(GuicheOcupado[2]) && FVazia(GuicheOcupado[3]) && FVazia(GuicheOcupado[4]))){               
        
        /* Tirar todas as pessoas com tempo de chegada igual ao Tempo */
        /* Botar as pessoas que chegaram nas filas dos Guiches respectivos (organizados por prioridade) */
        while(!FVazia(ClientesChegando)){
            Pessoa=(Cliente*)ClientesChegando->Head->prox->info;                //Pega a informação do primeiro elemento da fila
            if(Pessoa->tempo_chegada == tempo){                                 //Confere Se ele já chegou
                Pessoa=TiraElementoDaFila(ClientesChegando);                    //Passa o primeiro elemento para pessoa
                InsereClientePrioridade(ClientesNaLoja[Pessoa->serv], Pessoa);  //Insere essa pessoa na Fila de Clientes na loja de acordo com o serviço escolhido
            }
            else break;                                                         //Como esse dados estão organizados em ordem crescente de chegada, se o primeiro não tiver
        }                                                                       //chegado, nenhum atrás dele tbm irá ter chegado e portanto para o iteração
        

        /*  Ver se tem guiches disponiveis (um pra cada tipo) para botar as pessoas para serem atendidas */
            /* Lembrar de gravar o tempo em que cada pessoa começou a ser atendida */ 
        for(int i=0;i<5;i++){                                                           //Para cada tipo de atendimento:

            while(!FVazia(GuicheOcupado[i])){                                           //Se houver algum guiche ocupado
                guicheAux=GuicheOcupado[i]->Head->prox->info;                           //confere se ele pode ser desocupado
                if((guicheAux->tempoUltimoAtendimento + tempoServico[i]) == tempo){     //somando o tempo de quando ele começou
                    guicheAux = TiraElementoDaFila(GuicheOcupado[i]);                   //a atender com o tempo necessario pra atender.
                    InserirNaFila(GuicheLivre[i], guicheAux);                           //Passa o guiche ocupado para fila de Livres
                }
                else break;                                                             //Como o primeiro guiche é obrigatoriamente o mais perto de
            }                                                                           //terminar o atendimento, há a interrupção da iteração caso nenhum guiche seja removido

            while(!FVazia(GuicheLivre[i])){                                             //Equanto houver algum Guiche livre 
                if(!FVazia(ClientesNaLoja[i])){                                         //e se houver Cliente esperando para ser atendido
                    foiAtendido=TiraElementoDaFila(ClientesNaLoja[i]);                  //Tira uma pessoa da fila de clientes na loja
                    guicheAux = TiraElementoDaFila(GuicheLivre[i]);                     //Tira um dos guiches livres

                    foiAtendido->tempo_inicio=tempo;                                    //Salva o tempo do incio do atendimento
                    foiAtendido->guiche=guicheAux->num;                                 //Salva o numero do guiche que a pessoa foi atendida
                    guicheAux->tempoUltimoAtendimento=tempo;                            //Salva o tempo do inicio do atendimento no guiche para saber quando ele estará disponivel novamente
                                                                                    

                    InserirNaFila(ClientesAtendidos,foiAtendido);                       //Passa a pessoa para fila dos já atendidos (Problema: isso foi um pseudoatendido já que ele só deveria poder ir pra Lista de Atendidos depois que passasse o tempo de atendimento)
                    InserirNaFila(GuicheOcupado[i],guicheAux);                          //Passa o Guiche para fila dos guiches ocupados
                }
                else break;                                                             //Se o primeiro da fila não puder entrar, há a interrupção da iteração 
            }                                                                        
        }
        /* Tirar as pessoas que acabaram de ser atendidas e passar elas para uma fila exterior */


        tempo++;
    }

    /* Usar dados Contidos na Fila de clientes final para tirar informações */
        /* Informações adicionadas com proposito de teste do que foi feito anteriormente */
    InfoGlobal Glob;                                            
    Glob.clientePorTempo=10;
    Glob.tempoMedio=10;
    EscreveRelatorio( argv[3] ,Glob, ClientesAtendidos);

    /* Free Nos dados Alocados */
    //FreeFila(ClientesAtendidos);              //Foi retirado esse free pois a função de escrever relatorio já libera os dados enquanto escreve-os
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

#define NUMERO_FILAS 5


/* Função Para simulação do Laboratorio */
/* Recebe Como parametro uma Fila com os clientes organizados por ordem de chegada e uma fila dos guiches do arquivo de configuração */
/* Retorna uma Fila com os dados de horario de atendimento de todos os clientes atualizados, na mesma ordem da entrada */
/* Retorna por referencia o tempo de duração (em unidades de tempo da simulação) do simulador */  
Fila* Simulador(Fila* ClientesChegando, Fila* Guiches, int *tempoRetorno){
    /* Criação de Filas auxiliares */
    Fila **GuicheLivre;                         //Fila Dos GUICHES livre
    Fila **GuicheOcupado;                       //Fila dos GUICHES ocupados
    Fila *ClientesAtendidos;                    //Fila dos Clientes que já foram atendidos
    Fila **ClientesNaLoja;                      //Fila dos CLIENTES para cada tipo de guiche
    Guiche* TrocadeFila;
    GuicheLivre=SeparaGuiches(NUMERO_FILAS, Guiches);   //Separa no index n de GuicheLivre os guiches de serviço n 
    ClientesAtendidos=CriaFilaVazia();                  //No inicio da execução não existem Pessoas já atendidas
    GuicheOcupado=CriaFilas(NUMERO_FILAS);              //No incio da execução as 5 filas dos guiches ocuapdos está vazia
    ClientesNaLoja=CriaFilas(NUMERO_FILAS);             //No inicio da execução as 5 filas dos clientes na loja estão vazias
    
    /* Variaveis Auxiliares */
    int tempo=0;

    int *tempoServico = (int*)malloc(NUMERO_FILAS*sizeof(int));
    
    /*Inicializa os tempos de cada tipo de servico.*/
    tempoServico[0] = 5;                                //Essa parte nao tem como generalizar como as outras,
    tempoServico[1] = 10;                               //ja que esses dados nao sao fornecidos na entrada.
    tempoServico[2] = 8;
    tempoServico[3] = 7;
    tempoServico[4] = 2;

    Cliente* foiAtendido; Cliente* Pessoa;
    Guiche* guicheAux;
    InfoGlobal InformGeral;   
    int HaGuicheOcupado = 0;                            //Indica se ha guiche ocupado (0 se nao ha e 1 se ha).
    
    /* Iteração principal é Feita enquanto há alguem na fila de Chegada ou na Fila dos guiches */
    while(!FVazia(ClientesChegando) || HaGuicheOcupado){               
        HaGuicheOcupado = 0;
        /* Tirar todas as pessoas com tempo de chegada igual ao Tempo */
        /* Botar as pessoas que chegaram nas filas dos Guiches respectivos (organizados por prioridade) */
        while(!FVazia(ClientesChegando)){
            Pessoa=(Cliente*)ClientesChegando->Head->prox->info;                        //Pega a informação do primeiro elemento da fila
            if(Pessoa->tempo_chegada == tempo){                                         //Confere Se ele já chegou no laboratorio, comparando seu tempo de chegada com o tempo atual
                Pessoa=TiraElementoDaFila(ClientesChegando);                            //Passa o primeiro elemento para pessoa
                InsereClientePrioridade(ClientesNaLoja[Pessoa->serv], Pessoa);          //Insere essa pessoa na Fila de Clientes na loja de acordo com o serviço escolhido
            }
            else break;                                                                 //Como esse dados estão organizados em ordem crescente de chegada, se o primeiro não tiver
        }                                                                               //chegado, nenhum atrás dele tbm irá ter chegado e portanto para o iteração
        

        /*  Ver se tem guiches disponiveis (um pra cada tipo) para botar as pessoas para serem atendidas */ 
        for(int i=0;i<NUMERO_FILAS;i++){                                                //Para cada tipo de atendimento:

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
                                                                                    

                    InsereClienteNum(ClientesAtendidos,foiAtendido);                    //Passa a pessoa para fila dos já atendidos (Problema: isso foi um pseudoatendido já que ele só deveria poder ir pra Lista de Atendidos depois que passasse o tempo de atendimento)
                    InserirNaFila(GuicheOcupado[i],guicheAux);                          //Passa o Guiche para fila dos guiches ocupados
                }
                else break;                                                             //Se o primeiro da fila não puder entrar, há a interrupção da iteração 
            }                                                                        
        }
        tempo+=1;
        /*Verifica se ha guiche ocupado*/
        for(int i=0; i<NUMERO_FILAS; i++){
            if(!FVazia(GuicheOcupado[i])){
                HaGuicheOcupado = 1;
                break;
            }
        }
    }

    tempo--;                             //É retirada uma unidade de tempo pois no fim do programa sempre há um incremento a mais antes da verificação do fim

    /* Free nas Filas Auxliares */
    for(int i=0;i<NUMERO_FILAS;i++){
        FreeFila(ClientesNaLoja[i]);
        FreeFila(GuicheLivre[i]);
        FreeFila(GuicheOcupado[i]);
    }
    free(ClientesNaLoja);
    free(GuicheOcupado);
    free(GuicheLivre);
    free(tempoServico);

    *tempoRetorno = tempo;              //Variavel para retorno como referencia


    return ClientesAtendidos;
}
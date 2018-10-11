#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

/* Leitura de dados dos Clientes, devolvendo uma fila com os detalhes */
Fila* LeDadosClientes(char *Filename){
    Fila* ClientesF;
    Cliente *Novo_Cliente;
    FILE* f=fopen(Filename, "r");
    if(f==NULL){
        printf("Arquivo inexistente, parando a execução\n");
        exit(1);
    }
    ClientesF=CriaFilaVazia();
    int tempo_chegada;
    int idade;
    int serv;
    int cond;
    int nume = 1;
    while(fscanf(f,"%d %d %d %d", &tempo_chegada, &idade, &serv, &cond) != EOF){
        Novo_Cliente=CriaCliente();
        PassaDados(Novo_Cliente, tempo_chegada, idade, serv, cond, nume);
        InserirNaFila(ClientesF, Novo_Cliente);
        nume++;
    }
    return ClientesF;
}

Fila* LeDadosGuiches(char *Filename){
    Guiche* Atendimento;
    FILE* Entrada;
    Fila* FilaDosGuiches;
    
    Entrada = fopen(Filename,"r");
    if(Entrada==NULL){
        printf("Erro na leitura do arquivo... Parando...\n");
        exit(1);
    }
    int ServGuiche;
    int Quantidade;
    int NumeroDoGuiche=1;
    FilaDosGuiches=CriaFilaVazia();
    fscanf(Entrada,"%d",&Quantidade);               //Quantidade não será nescessária posteriormente pois o quantidade de guiches estará armazenado no tamanho da fila criada
    for(int i =0; i< Quantidade;i++){
        fscanf(Entrada,"%d",&ServGuiche);
        Atendimento=(Guiche*)malloc(sizeof(Guiche));
        Atendimento->serv=ServGuiche;
        Atendimento->num=NumeroDoGuiche;
        InserirNaFila(FilaDosGuiches, Atendimento);
        NumeroDoGuiche++;
    }
    return FilaDosGuiches;
}

/* Cria Arquivo com as informações sobre a saida de dados */
void EscreveRelatorio(char* ArquivoSaida, InfoGlobal Global, Fila *Clientes){
    FILE* Saida;
    Saida=fopen(ArquivoSaida,"w");                              //Abrindo para escrita do Relatorio, substituindo o arquivo se ele já existir
    if(Saida == NULL){                                          //Conferindo se houve a criação
        printf("Erro na criação do Relatorio, parando...\n");   
        exit(1);
    }
    
    /* Primeira Linha destinada para informações gerais sobre os clientes */
    fprintf(Saida,"%.2f %.2f\n", Global.tempoMedio,Global.clientePorTempo);

    Cliente* Dados;                                             //Ponteiro para auxiliar na escritura dos dados

    /* Enquanto a Fila de clientes não estiver Vazia, os elementos dela são 
    retirados um por um para escrever seus dados coletados */
    while(!FVazia(Clientes)){
        Dados=TiraElementoDaFila(Clientes);                     //Tirando elemento da fila para usar seus dados
        Dados->tempo_espera=Dados->tempo_inicio - Dados->tempo_chegada;
        fprintf(Saida,"%d %d %d %d\n", Dados->guiche,Dados->prioridade, Dados->tempo_espera, Dados->serv);
        free(Dados);                                            // Como os clientes não serão mais usados a partir daqui, seus dados são liberados
    }
    free(Clientes->Head);
    free(Clientes);
    fclose(Saida);
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

/* Leitura de dados dos Clientes*/
/* Retorna uma Fila com os dados lidos */
Fila* LeDadosClientes(char *Filename){
    Fila* ClientesF;
    Cliente *Novo_Cliente;
    FILE* f=fopen(Filename, "r");                               //Abre o Arquivo de dados dos clientes para Leitura
    if(f==NULL){                                                //Verifica se o arquivo foi aberto corretamente
        printf("Arquivo inexistente, parando a execução\n");
        exit(1);
    }
    ClientesF=CriaFilaVazia();                                  //Cria Fila para armazenar todos os clientes

    /* Variaveis auxiliares para leitura dos dados */
    int tempo_chegada, idade, serv, cond, nume = 1;

    while(fscanf(f,"%d %d %d %d", &tempo_chegada, &idade, &serv, &cond) != EOF){ //Lê todos os dados de pessoas até o fim do arquivo
        Novo_Cliente=CriaCliente();                                              //Para cada pessoa cria e aloca espaço para um novo Cliente
        PassaDados(Novo_Cliente, tempo_chegada, idade, serv, cond, nume);        //Armazena os dados na struct criada
        InserirNaFila(ClientesF, Novo_Cliente);                                  //Insere o Cliente na fila de retorno
        nume++;                                                                  //Aumenta o contador que representa a ordem das pessoas no arquivo de entrada
    }
    fclose(f);
    return ClientesF;                                                            //Retorna ponteiro da fila criada
}

/* Leitura da configuração dos Guiches */
/* Retorna uma Fila com os dados lidos */
Fila* LeDadosGuiches(char *Filename){
    Guiche* Atendimento;
    FILE* Entrada;
    Fila* FilaDosGuiches;
    
    Entrada = fopen(Filename,"r");                   //Abrindo arquivo para leitura
    if(Entrada==NULL){                               //Conferindo se foi feita a abertura correta
        printf("Erro na leitura do arquivo... Parando...\n");
        exit(1);
    }
    int ServGuiche, Quantidade, NumeroDoGuiche=1;    //Variaveis para Auxiliar na leitura 
    FilaDosGuiches=CriaFilaVazia();                  //Aloca fila para ser retornada no termino da leitura
    fscanf(Entrada,"%d",&Quantidade);                //Quantidade não será nescessária posteriormente pois o quantidade de guiches estará armazenado no tamanho da fila criada
    
    for(int i =0; i< Quantidade;i++){
        fscanf(Entrada,"%d",&ServGuiche);
        Atendimento=(Guiche*)malloc(sizeof(Guiche));
        Atendimento->serv=ServGuiche;
        Atendimento->num=NumeroDoGuiche;
        InserirNaFila(FilaDosGuiches, Atendimento);
        NumeroDoGuiche++;
    }
    fclose(Entrada);
    return FilaDosGuiches;                          //Retorna ponteiro para Fila com guiches como informação armazenada
}

/* Cria Arquivo com as informações sobre a saida de dados */
/* Essa função também já desaloca A fila que é passada como parametro */
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
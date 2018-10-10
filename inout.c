#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"
/* Função para ajudar na criação dos dados Aleatorios */
int AleatorioRange(int minimo, int maximo){
    
    return (rand() % (maximo-minimo+1))+minimo;
}

/* Inicializando a Seed Da função random */
void InicRandom(){
    time_t Tempo_do_computador;
    srand((unsigned)time(NULL));
}
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
/* Adiciona no arquivo de saida dados aleatorios dos clientes */
void GeraAleatoriosClientes(char* ArquivoSaida, int quantidade){
    FILE* f;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"w");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    InicRandom();
    int tempo_chegada=0, idade, serv, cond;

    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantidade;contador++){
        tempo_chegada=AleatorioRange(tempo_chegada,tempo_chegada+4);
        idade=AleatorioRange(0,100);
        serv=AleatorioRange(0,4);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada,idade,serv,cond);
    }

    fclose(f);
}

/* Adiciona na arquivo de saida clientes com horario de entrada fixo e outros dados aleatorios*/
void GeraClientes_Horario(char* ArquivoSaida, int quantidade, float porcentagem){
     FILE* f;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"w");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    InicRandom();
    int tempo_chegada=0, idade, serv, cond;
    int tempo=0;
    float limite_inferior=porcentagem/2;
    float troca;
    float limite_superior=100-porcentagem/2;
    int pessoamedia = AleatorioRange((quantidade*limite_inferior)/100,(quantidade*limite_superior)/100); 
    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantidade;contador++){
        if(contador > pessoamedia-(porcentagem*quantidade)/200 && contador < pessoamedia+(porcentagem*quantidade)/200){
            tempo_chegada=AleatorioRange(tempo_chegada,tempo_chegada);
        }
        else{
            tempo_chegada=AleatorioRange(tempo_chegada,tempo_chegada+6);
        }
        idade=AleatorioRange(0,100);
        serv=AleatorioRange(0,4);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada, idade, serv, cond);
    }

    fclose(f);
}

/* Adiciona na arquivo de saida clientes com Guichê fixo e outros dados aleatorios*/
void GeraClientes_Guiche(char* ArquivoSaida, int quantidade, int serv){
    FILE* f;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"w");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    InicRandom();
    int tempo_chegada=0, idade, cond;

    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantidade;contador++){
        tempo_chegada=AleatorioRange(tempo_chegada,tempo_chegada+5);
        idade=AleatorioRange(0,100);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada,idade,serv,cond);
    }

    fclose(f);
}

/* Adiciona no arquivo de Saida numeros dos guichês aleatoriamente */
void GeraGuiches(char* ArquivoSaida, int quantidade){
    FILE* f=fopen(ArquivoSaida, "w");
        if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    /* Como a quantidade de Guiches em um Arquivo deve ser pelo menos 5, se a passagem do 
    parametro estiver errada, deve ser corrigida */
    if(quantidade < 5){
        printf("Quantidade inválida, por favor escolha um número inteiro maior que 5:\n~> ");
        scanf("%d",&quantidade);
    }
    fprintf(f,"%d\n",quantidade);
    quantidade-=5;
    InicRandom();
    /* Primeiro é feita a escrita de 5 guiches, um de cada tipo para haver a garantia de que 
    existe pelo menos um de cada tipo de guiche na clinica */
    char* Padroes="0\n3\n4\n2\n1\n";
    fprintf(f,"%s", Padroes);
    for(int Contador=0; Contador < quantidade ;Contador++){
        fprintf(f,"%d\n",AleatorioRange(0,4));
    }
    printf("Criação feita com sucesso\n");
}

/* Cria interatividade pelo terminal para criação de arquivos de saida */
void TeladeCriacao(){
    FILE *Exclui_Arquivo;
    char *clientefile = "Clientes.txt";
    char *guichefile = "Guiche.txt";
    char Resposta;
    int Quantidade,Aux;
    int Mudar_modos;
    float P;
    system("clear");
    printf("\t\t\tAdicione Clientes\n");
    printf("\t(1)Aleatorio\t\t\t(2)Horario de Pico\n");
    printf("\t(3)Guiche Mais Utilizado\t(4)Reiniciar Arquivo\n");
    printf("\t(0)Sair\n");
    printf("~> ");
    scanf("%d",&Mudar_modos);
    if(Mudar_modos==0){
        //break;
    }
    if(Mudar_modos==4){
        Exclui_Arquivo=fopen(clientefile, "w");
        fclose(Exclui_Arquivo);
        Mudar_modos=0;
    }
    if(Mudar_modos){
        printf("Digite a quantidade: ");
        scanf(" %d",&Quantidade);
        if(Mudar_modos==1){
            GeraAleatoriosClientes(clientefile,Quantidade);
        }
        if(Mudar_modos==2){
            printf("Digite porcentagem de pessoas no horario de pico: ");
            scanf(" %f",&P);
            while(P<0||P>100){
                printf("Digite novamente: ");
                scanf("%f",&P);
            }
            GeraClientes_Horario(clientefile, Quantidade, P);
        }
        if(Mudar_modos==3){
            printf("Digite o Guiche mais usado: ");
            scanf(" %d",&Aux);
            while(Aux>4||Aux<0){
                printf("Digite novamente: ");
                scanf("%d",&Aux);
            }
            GeraClientes_Guiche(clientefile, Quantidade, Aux);
        }
    }
    system("clear");
    printf("\tDeseja também criar Guiches? (y/n)\n~> ");
    scanf(" %c",&Resposta);
    if((int)Resposta==110||(int)Resposta==78)return; //n = 110 , N = 78
    if((int)Resposta==121||(int)Resposta==89){        //y = 121 , Y = 89
        printf("Qual a quantidade de Guiches?\n~> ");
        scanf(" %d",&Quantidade);
        GeraGuiches(guichefile, Quantidade);
    }

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
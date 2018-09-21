#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

int AleatorioRange(int minimo, int maximo){
    
    return (rand() % (maximo-minimo+1))+minimo;
}

Fila* LeDados(char *Filename){
    Fila* ClientesF;
    Cliente *Novo_Cliente;
    FILE* f=fopen(Filename, "r");
    if(f==NULL){
        printf("Arquivo inexistente, parando a execução\n");
        exit(1);
    }
    ClientesF=CriaFiladeCliente();
    int tempo_chegada;
    int idade;
    int serv;
    int cond;
    while(fscanf(f,"%d %d %d %d", &tempo_chegada, &idade, &serv, &cond) != EOF){
        Novo_Cliente=CriaCliente();
        PassaDados(Novo_Cliente, tempo_chegada, idade, serv, cond);
        InsereCliente(ClientesF,Novo_Cliente);
    }
    return ClientesF;
}

void GeraAleatoriosClientes(char* ArquivoSaida, int quantiadade){
    FILE* f;
    time_t Tempo_do_computador;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"a");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    
    srand((unsigned)time(&Tempo_do_computador));
    int tempo_chegada, idade, serv, cond;

    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantiadade;contador++){
        tempo_chegada=AleatorioRange(0,50);
        idade=AleatorioRange(0,100);
        serv=AleatorioRange(0,4);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada,idade,serv,cond);
    }

    fclose(f);
}

void GeraClientes_Horario(char* ArquivoSaida, int quantiadade, int horario){
     FILE* f;
    time_t Tempo_do_computador;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"a");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    srand((unsigned)time(&Tempo_do_computador));
    int tempo_chegada, idade, serv, cond;

    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantiadade;contador++){
        tempo_chegada=AleatorioRange(horario-5,horario+5);
        idade=AleatorioRange(0,100);
        serv=AleatorioRange(0,4);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada, idade, serv, cond);
    }

    fclose(f);
}

void GeraClientes_Guiche(char* ArquivoSaida, int quantiadade, int serv){
    FILE* f;
    time_t Tempo_do_computador;
    /* Abrindo arquivo para armazenar os dados dos clientes */ 
    f=fopen(ArquivoSaida,"a");
    /* Checando se foi feita a abertura corretamente */ 
    if(f==NULL){
        printf("Houve problema na abertura do arquivo para escrita, parando...\n");
        exit(1);
    }
    
    srand((unsigned)time(&Tempo_do_computador));
    int tempo_chegada, idade, cond;

    /* Escrevendo no arquivo de saida dados aleatorios dos cliente */
    for(int contador=0;contador<quantiadade;contador++){
        tempo_chegada=AleatorioRange(0,50);
        idade=AleatorioRange(0,100);
        cond=AleatorioRange(0,2);
        fprintf(f,"%d %d %d %d\n", tempo_chegada,idade,serv,cond);
    }

    fclose(f);
}

void TeladeCriacao(){
    FILE *Exclui_Arquivo;
    char *nome = "saida.txt";
    int Quantidade,Aux;
    int Mudar_modos;
    while(1){
        system("clear");
        printf("\t\t\tAdicione Clientes\n");
        printf("\t(1)Aleatorio\t\t\t(2)Horario de Pico\n");
        printf("\t(3)Guiche Mais Utilizado\t(4)Reiniciar Arquivo\n");
        printf("\t(0)Sair\n");
        printf("~>");
        scanf("%d",&Mudar_modos);
        if(Mudar_modos==0){
            break;
        }
        if(Mudar_modos==4){
            Exclui_Arquivo=fopen(nome, "w");
            fclose(Exclui_Arquivo);
            continue;
        }
        printf("Digite a quantidade: ");
        scanf("%d",&Quantidade);
        if(Mudar_modos==1){
            GeraAleatoriosClientes(nome,Quantidade);
        }
        if(Mudar_modos==2){
            printf("Digite horario de pico: ");
            scanf("%d",&Aux);
            while(Aux<0){
                printf("Digite novamente: ");
                scanf("%d",&Aux);
            }
            GeraClientes_Horario(nome, Quantidade, Aux);
        }
        if(Mudar_modos==3){
            printf("Digite o Guiche mais usado: ");
            scanf("%d",&Aux);
            while(Aux>4||Aux<0){
                printf("Digite novamente: ");
                scanf("%d",&Aux);
            }
            GeraClientes_Horario(nome, Quantidade, Aux);
        }
    }
}
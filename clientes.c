#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

Cliente* CriaCliente(){
    Cliente* Novo;
    Novo = (Cliente*)malloc(sizeof(Cliente));
    if(Novo == NULL){
        printf("Erro\n");
    }
    else return Novo;
}
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond,int num){
    C->tempo_chegada=tempo_chegada;
    C->serv=serv;
    C->ordem = num;
    C->prioridade=0;
    if(idade<65)C->prioridade+=1;
    else if(idade>65&&idade<80)C->prioridade+=2;
    else C->prioridade+=3;
    if(cond==0 || cond==1)C->prioridade+=2;
    else C->prioridade+=1;
}
float CalculaTempodeEsperaMedio(Fila *f){
    float tempo_medio=0;
    Cliente* Auxiliar;
    for(int i=0; i < f->tamanho ;i++){
        Auxiliar=TiraElementoDaFila(f);
        tempo_medio+= (Auxiliar->tempo_inicio - Auxiliar->tempo_chegada);
        InserirNaFila(f,Auxiliar);
    }
    return tempo_medio/f->tamanho; 
}
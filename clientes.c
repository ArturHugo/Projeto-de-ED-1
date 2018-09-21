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
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond){
    C->tempo_chegada=tempo_chegada;
    C->serv=serv;
    C->prioridade=0;
    if(idade<65)C->prioridade+=1;
    else if(idade>65&&idade<80)C->prioridade+=2;
    else C->prioridade+=3;
    if(cond==0 || cond==1)C->prioridade+=2;
    else C->prioridade+=1;
}
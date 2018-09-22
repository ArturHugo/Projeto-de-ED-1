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

Fila** Separa5Guiches(Fila* Principal){
    Fila** Separadas;
    Guiche* TrocadeFila;
    Separadas=(Fila**)malloc(5*sizeof(Fila*));
    Separadas[0]=CriaFilaVazia();
    Separadas[1]=CriaFilaVazia();
    Separadas[2]=CriaFilaVazia();
    Separadas[3]=CriaFilaVazia();
    Separadas[4]=CriaFilaVazia();
    while(!FVazia(Principal)){
        TrocadeFila=TiraElementoDaFila(Principal);
        switch(TrocadeFila->serv){
            case 0:
            InserirNaFila(Separadas[0],TrocadeFila);
            break;
            case 1:
            InserirNaFila(Separadas[1],TrocadeFila);
            break;
            case 2:
            InserirNaFila(Separadas[2],TrocadeFila);
            break;
            case 3:
            InserirNaFila(Separadas[3],TrocadeFila);
            break;
            case 4:
            InserirNaFila(Separadas[4],TrocadeFila);
            break;
        }
    }
    return Separadas;
}
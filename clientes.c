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
    Fila** Separadas=Cria5Filas();
    Guiche* TrocadeFila;
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

Fila** Cria5Filas(){
    Fila** Separadas;
    Separadas=(Fila**)malloc(5*sizeof(Fila*));
    Separadas[0]=CriaFilaVazia();
    Separadas[1]=CriaFilaVazia();
    Separadas[2]=CriaFilaVazia();
    Separadas[3]=CriaFilaVazia();
    Separadas[4]=CriaFilaVazia();
    return Separadas;
}

void InsereClientePrioridade(Fila* f, Cliente* c){
    f->tamanho++;
    Lista* auxF = f->Head;
    Lista* aInserir=(Lista*)malloc(sizeof(Lista));
    aInserir->info=c;

    if(auxF==f->Tail){
        auxF->prox=aInserir;
        f->Tail=aInserir;
        return;
    }

    Cliente* auxC = auxF->prox->info;
    while( (auxC->prioridade >= c->prioridade) ){
        auxF=auxF->prox;
        if(auxF==f->Tail){
            auxF->prox=aInserir;
            f->Tail=aInserir;
            return;
        }
        auxC = auxF->prox->info;
    }

    aInserir->prox=auxF->prox;
    auxF->prox=aInserir;
}

void InsereClienteTempo(Fila* f, Cliente* c){
    f->tamanho++;
    Lista* auxF = f->Head;
    Lista* aInserir=(Lista*)malloc(sizeof(Lista));
    aInserir->info=c;

    if(auxF==f->Tail){
        auxF->prox=aInserir;
        f->Tail=aInserir;
        return;
    }

    Cliente* auxC = auxF->prox->info;
    while( (auxC->tempo_chegada < c->tempo_chegada) ){
        auxF=auxF->prox;
        if(auxF==f->Tail){
            auxF->prox=aInserir;
            f->Tail=aInserir;
            return;
        }
        auxC = auxF->prox->info;
    }

    aInserir->prox=auxF->prox;
    auxF->prox=aInserir;
}
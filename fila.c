#include <stdio.h>
#include <stdlib.h> //Malloc() e free()
#include "headers.h"

/* Inicializa a Fila dos Clientes, usando uma célula cabeça */
Fila* CriaFilaVazia(){
    Fila* f;
    f=(Fila*)malloc(sizeof(Fila));
    if(f==NULL)exit(1);
    f->Head=(Lista*)malloc(sizeof(Lista));
    f->Tail=f->Head;
    f->tamanho=0;
    return f;
}
/* Insere um elemento em uma fila qualquer */
void InserirNaFila(Fila* f, void* elemento){
    f->Tail->prox=(Lista*)malloc(sizeof(Lista));
    f->Tail->prox->info=elemento;
    f->Tail=f->Tail->prox;
    f->tamanho++;
}

/* Insere cliente em fila levando em conta a prioridade */

/*********************/
void InsereCliente(Fila* f, Cliente* C){
    f->Tail->prox=(Lista*)malloc(sizeof(Lista));;
    f->Tail->prox->info=(Cliente*)C;
    f->Tail=f->Tail->prox;
    f->tamanho++;
}
/********************/


void* TiraElementoDaFila(Fila* f){
    Lista* aux;
    void* Retorno;
    aux=f->Head;
    f->Head=aux->prox;
    Retorno=f->Head->info;
    free(aux);
    f->tamanho--;
    return Retorno;
} 

int FVazia(Fila* f){
    if(f->Head==f->Tail){
        return 1;
    }
    else return 0;
}

void FreeFila(Fila* f){
    while(!FVazia(f)){
        free(TiraElementoDaFila(f));
    }
    free(f->Head);
    free(f);
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
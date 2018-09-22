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
    Cliente* aux;
    while(!FVazia(f)){
        aux = (Cliente*)TiraElementoDaFila(f);
        free(aux);
    }
    free(f->Head);
    free(f);
}
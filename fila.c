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
    f->Tail->ant=f->Tail
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
        TiraElementoDaFila(f);
    }
    free(f->Head);
    free(f);
}

Lista* MenorTempoChegada(Lista *l){            // Retorna a posicao do cliente com menor tempo
    Lista *Retorno;                            //de chegada a partir da posicao dada.
    Lista *auxLista = l;
    Cliente *auxCliente = (Cliente*)l->info;   
    int menor_tempo = __INT_MAX__;
    while(auxLista->prox != NULL){
       auxCliente = (Cliente*)auxLista->info;
       if(menor_tempo > auxCliente->tempo_chegada){
            menor_tempo = auxCliente->tempo_chegada;
            Retorno = auxLista;
        }
        auxLista = auxLista->prox;
    }   
    return Retorno;
}

void swapLista(Lista *celula1, Lista *celula2){
    Lista *aux = celula1;
    celula1->ant->prox = celula2;
    celula2->ant->prox = celula1;
    celula1->prox = celula2->prox;
    celula2->prox = aux->prox;
}

void OrdenaPorChegada(Fila *f){
    Lista *auxLista, *auxMenor;
    auxLista = f->Head->prox;
    while(auxLista->prox != NULL){
        auxMenor = MenorTempoChegada(auxLista);
        swapElementosFila(auxLista, auxMenor);
        auxLista = auxMenor->prox;
    }
}
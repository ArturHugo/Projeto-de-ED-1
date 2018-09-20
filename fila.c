#include <stdio.h>
#include <stdlib.h> //Malloc() e free()
#include "headers.h"

Fila* CriaFiladeCliente(){
    Fila* f;
    f=(Fila*)malloc(sizeof(Fila));
    if(f==NULL)exit(1);
    f->Head=(Lista*)malloc(sizeof(Lista));
    f->Tail=f->Head;
    f->tamanho=0;
    return f;
}

void InsereCliente(Fila* f, Cliente* C){
    f->Tail->prox=(Lista*)malloc(sizeof(Lista));;
    f->Tail->prox->info=(Cliente*)C;
    f->Tail=f->Tail->prox;
    f->tamanho++;
}

Cliente* TiraCliente(Fila *f){
    Lista* aux;
    Cliente *Retorno;
    aux=f->Head;
    f->Head=aux->prox;

    Retorno = (Cliente*)f->Head->info;
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
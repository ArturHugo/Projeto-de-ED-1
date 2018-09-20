#include <stdio.h>
#include <stdlib.h> //Malloc() e free()

typedef struct Lista{
    struct Fila* prox;
    void* info;
}Lista;

typedef struct Fila{
    Lista* Head;
    Lista* Tail;
    int tamanho;
}Fila;

typedef struct Pessoa{
    int tempo_chegada;
    int idade;
    int serv; //Serviço desejado pelo Cliente
    int cond; //Condição física do Cliente

    //Faltam algumas caracteristicas
    //Exemplo:
    //  int tempo_espera;
    //  int prioridade;
    //  int guiche; 
}Cliente;

void CriaFiladeCliente(Fila* f){
    f=(Fila*)malloc(sizeof(Fila));
    if(f==NULL)exit(1);
    f->Head->info=NULL;
    f->Head=(Lista*)malloc(sizeof(Lista));
    f->Tail=f->Head;
}

void InsereCliente(Fila* f, Cliente* C){
    Lista* aux;
    aux=(Lista*)malloc(sizeof(Lista));
    f->Tail->prox=aux;
    aux->info=(Cliente*)aux->info;
    aux->info=C;
    f->Tail=aux;
}

Cliente* TiraCliente(Fila *f){
    Lista* aux;
    Cliente *Retorno;
    aux=f->Head;
    f->Head=f->Head->prox;

    Retorno = (Cliente*)aux->info;
    free(aux);
    return Retorno;
} 

int FVazia(Fila* f){
    if(f->Head==f->Tail){
        return 1;
    }
    else return 0;
}

Cliente* CriaCliente(){
    Cliente* Novo;
    Novo = (Cliente*)malloc(sizeof(Cliente));
    if(Novo == NULL){
        printf("Erro\n");
    }
    else return Novo;
}

void LeDadosCliente(Cliente* C,int tempo_chegada,int idade,int serv, int cond){
    C->tempo_chegada=tempo_chegada;
    C->idade=idade;
    C->serv=serv;
    C->cond=0;
}

int main(int argc, char** argv){



    return 0;
}
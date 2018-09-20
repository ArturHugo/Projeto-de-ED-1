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
    C->idade=idade;
    C->serv=serv;
    C->cond=0;
}
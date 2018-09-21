#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
/*
Fila* LeDados(char *Filename){
    Fila* ClientesF;
    Cliente *Novo_Cliente;
    FILE* f=fopen(Filename, "r");
    if(f==NULL){
        printf("Arquivo inexistente, parando a execução\n");
        exit(1);
    }
    ClientesF=CriaFiladeCliente();
    int tempo_chegada;
    int idade;
    int serv;
    int cond;
    while(fscanf(f,"%d %d %d %d", &tempo_chegada, &idade, &serv, &cond) != EOF){
        Novo_Cliente=CriaCliente();
        PassaDados(Novo_Cliente, tempo_chegada, idade, serv, cond);
        InsereCliente(ClientesF,Novo_Cliente);
    }
    return ClientesF;
}*/
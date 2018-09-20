#ifndef Header
#define Header

typedef struct Lista{
    struct Lista* prox;
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

Fila* LeDados(char *Filename);

Fila* CriaFiladeCliente();
void InsereCliente(Fila* f, Cliente* C);
Cliente* TiraCliente(Fila *f);
int FVazia(Fila* f);
Cliente* CriaCliente();
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond);



#endif
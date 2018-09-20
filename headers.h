#ifndef Header
#define Header

typedef struct Lista{
    struct Lista* prox;
    struct Lista* ant;
    void* info;
}Lista;

typedef struct Fila{
    Lista* Head;
    Lista* Tail;
    int tamanho;
}Fila;

typedef struct Pessoa{
    int tempo_chegada;      //Tempo de chegada na clinica
    int tempo_inicio;       //Tempo de inicio do atendimento
    int tempo_espera;       //Tempo de inicio - tempo de chegada
    
    //int pr_por_idade;     //1 se idade < 65, 2 se 65 <= idade < 80, 3 se idade >= 80
    //int pr_por_cond;      //Prioridade da condição fisica do Cliente       
    
    int prioridade;         //Prioridade por + prioridade por condicao fisica
    
    int serv;               //Serviço desejado pelo Cliente
    int guiche;             //Numero do guiche para onde a pessoa foi encaminhada
}Cliente;

typedef struct InformacaoGlobal{
    float clientePorTempo;  //Numero de clientes atendidos por unidade de tempo
}InfoGlobal;

typedef struct Guiche{
    int serv;              //Servico do guiche
    int num;               //Numero do guiche
}Guiche;

Fila* LeDados(char *Filename);

Fila* CriaFiladeCliente();
void InsereCliente(Fila* f, Cliente* C);
Cliente* TiraCliente(Fila *f);
int FVazia(Fila* f);
Cliente* CriaCliente();
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond);



#endif
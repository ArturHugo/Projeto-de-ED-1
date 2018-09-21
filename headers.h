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
/* Funções de entrada e saida de dados */
    int AleatorioRange(int minimo, int maximo);                                     //Retorna um numero aleatorio entre valor minimo e maximo
    Fila* LeDados(char *Filename);                                                  //Lê os dados dos CLIENTES e retorna uma fila sem organização
        /* Cria Arquivos Com Dados de clientes */
    void GeraAleatoriosClientes(char* ArquivoSaida, int quantiadade);               //Coloca dados de uma quantidade de clientes com caracteristicas aleatorias  
    void GeraClientes_Horario(char* ArquivoSaida, int quantiadade, int horario);    //Coloca dados de clientes com horario especifico de entrada
    void GeraClientes_Guiche(char* ArquivoSaida, int quantiadade, int serv);        //Coloca dados de clientes com Serviço especifico
    void TeladeCriacao();
/* Fim das funções de entrada e saida */

Fila* CriaFiladeCliente();
void InsereCliente(Fila* f, Cliente* C);
Cliente* TiraCliente(Fila *f);
int FVazia(Fila* f);
Cliente* CriaCliente();
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond);



#endif
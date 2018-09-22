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
    float tempoMedio;       //Tempo medio de espera dos clientes nas filas
}InfoGlobal;

typedef struct Guiche{
    int serv;              //Servico do guiche
    int num;               //Numero do guiche
}Guiche;
/* Funções de entrada e saida de dados */                                    //Retorna um numero aleatorio entre valor minimo e maximo
    Fila* LeDadosClientes(char *Filename);                                                  //Lê os dados dos CLIENTES e retorna uma fila sem organização
    Fila* LeDadosGuiches(char *Filename);
        /* Cria Arquivos Com Dados de clientes */
    void GeraAleatoriosClientes(char* ArquivoSaida, int quantidade);               //Coloca dados de uma quantidade de clientes com caracteristicas aleatorias no arquivo de saida  
    void GeraClientes_Horario(char* ArquivoSaida, int quantidade, int horario);    //Coloca dados de clientes com horario especifico de entrada no arquivo de saida
    void GeraClientes_Guiche(char* ArquivoSaida, int quantidade, int serv);        //Coloca dados de clientes com Serviço especifico no arquivo de saida
    void TeladeCriacao();                                                          //Cria interatividade pelo terminal para criação de arquivos de saida
    void GeraGuiches(char* ArquivoSaida, int quantidade);                          //Adiciona no arquivo de Saida numeros dos guichês aleatoriamente
    void EscreveRelatorio(char* ArquivoSaida, InfoGlobal Global, Fila *Clientes);  //Cria o relatorio com as informações gerais do programa
/* Fim das funções de entrada e saida */

Fila** Separa5Guiches(Fila* Principal); //Separa as filas dos guiches
Fila* CriaFilaVazia();
void FreeFila(Fila* f);
void InsereCliente(Fila* f, Cliente* C);
Cliente* TiraCliente(Fila* f);
int FVazia(Fila* f);
Cliente* CriaCliente();
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond);
void InserirNaFila(Fila* f, void* elemento);
void* TiraElementoDaFila(Fila* f);

#endif
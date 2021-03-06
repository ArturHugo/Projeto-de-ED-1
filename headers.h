#ifndef Header
#define Header

/* Lista Generalizada usando ponteiro para void como forma de apontar para dados */
typedef struct Lista{
    struct Lista* prox;
    void* info;
}Lista;

/* Fila Implementada usando ponteiros para Lista, junto com seus demais metodos Apresentados abaixo*/
typedef struct Fila{
    Lista* Head;
    Lista* Tail;
    int tamanho;
}Fila;

/* Estrutura de Dados Para armazenar informações sobre os clientes do laboratorio */
typedef struct Pessoa{
    int tempo_chegada;      //Tempo de chegada no laboratorio
    int tempo_inicio;       //Tempo de inicio do atendimento
    int tempo_espera;       //Tempo de inicio - tempo de chegada    
    
    int prioridade;         //Prioridade por idade + prioridade por condicao fisica
    
    int serv;               //Serviço desejado pelo Cliente
    int guiche;             //Numero do guiche para onde a pessoa foi encaminhada

    int ordem;
}Cliente;

/* Estrutura de Dados para armazenar informações Gerais do programa */
typedef struct InformacaoGlobal{
    float clientePorTempo;  //Numero de clientes atendidos por unidade de tempo
    float tempoMedio;       //Tempo medio de espera dos clientes nas filas
}InfoGlobal;

/* Estrutura de Dados para armazenar informações sobre cada Guiche do laboratorio */
typedef struct Guiche{
    int serv;              //Servico do guiche
    int num;               //Numero do guiche
    int tempoUltimoAtendimento;
}Guiche;
/* Funções de entrada e saida de dados */                                          
    Fila* LeDadosClientes(char *Filename);                                         //Lê os dados dos CLIENTES e retorna uma fila sem organização
    Fila* LeDadosGuiches(char *Filename);
    void EscreveRelatorio(char* ArquivoSaida, InfoGlobal Global, Fila *Clientes);  //Cria o relatorio com as informações gerais do programa
/* Fim das funções de entrada e saida */


/* Funções de Manipulação de Filas */
Fila** CriaFilas();                                                                //Aloca um vetor de 5 filas
Fila** SeparaGuiches(int numero_guiches, Fila* Principal);                         //Separa as filas dos guiches
Fila* CriaFilaVazia();                                                             //Cria uma fila e retorna ponteiro para ela
void FreeFila(Fila* f);                                                            //Libera os dados da fila e de seus elemento
void InsereClientePrioridade(Fila* f, Cliente* c);                                 //Insere Cliente de acordo com sua prioridade (ordem decrescente)
void InsereClienteNum(Fila* f, Cliente* c);                                        //Insere Cliente de acordo com sua ordem no arquivo de entrada
void InserirNaFila(Fila* f, void* elemento);                                       //Insere elemento no Final da Fila
void* TiraElementoDaFila(Fila* f);                                                 //Tira elemento qualquer da fila, retornando o ponteiro para ele
int FVazia(Fila* f);                                                               //Retorna 1 caso a Fila esteja vazia e 0 caso contrario
/* Fim das funções de Fila */

/* Funções de Manipulação de Clientes */
float CalculaTempodeEsperaMedio(Fila *f);                                           //Usa os dados da fila de clientes para calcular o tempo medio de espera
Cliente* CriaCliente();                                                             //Retorna espaço alocado para um Cliente
void PassaDados(Cliente* C,int tempo_chegada,int idade,int serv, int cond,int num); //Usa dados lidos para adicionar às informações do Cliente
/* Fim das Funções de Clientes */
Fila* Simulador(Fila* ClientesChegando, Fila* Guiches, int *tempo);
#endif
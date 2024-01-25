#ifndef AEROPORTO_H
#define AEROPORTO_H
#define HASHSIZEVOO 10050 // Tamanho da tabela hash
#include "../include/voo.h"


/* Definição do KeyType*/
typedef char KeyType[300];


/* Definição da estrutura Aeroporto, que apresenta o respetivo nome de cada Aeroporto e a lista ligada 
VooResumo que apresenta então todos os voos associados a um determinado Aeroporto. */
typedef struct Aeroporto Aeroporto;


/* Definiçao da estrutura VooResumo que apresenta um resumo dos dados relativos a um voo. */
typedef struct VooResumo VooResumo;


/* Definiçao da estrutura utilizado para criar uma lista com os nomes de aeroportos.*/
typedef struct AeroportoNode AeroportoNode;


/* Definição da estrutura que representa uma lista encadeada de aeroportos*/
typedef struct ListaAeroportos ListaAeroportos;


/* Definição da estrutura que armazena o nome de um aeroporto e o total de passageiros num ano específico*/
typedef struct SomaPassageirosAno SomaPassageirosAno;


/* Definição da estrutura que contém informações sobre a mediana dos atrasos nos voos de um aeroporto*/
typedef struct MedianaAeroporto MedianaAeroporto;


/* Função para criar a hash dos Aeroportos*/
typedef Aeroporto *hash_aeroportos[HASHSIZEVOO];


/*Função para criar um novo nó de aeroporto.*/
Aeroporto *createAeroporto(char *name);


/*Obtém o nome do aeroporto.*/
char *aeroportoGetName(Aeroporto *aeroporto);


/*Obtém o próximo aeroporto*/
Aeroporto *aeroportoGetNext(Aeroporto *aeroporto);


/*Define o próximo aeroporto*/
void setNextAeroporto(Aeroporto *aeroporto, Aeroporto *next);


/*Obtém o o próximo resumo de voo associado ao aeroporto.*/
VooResumo *aeroportoGetNextResumo(Aeroporto *aeroporto);


/*Define o próximo resumo de voo associado ao aeroporto.*/
void setNextVooResumoAeroporto(Aeroporto *aeroporto, VooResumo *next);


/*Obtém o nome do aeroporto associado à soma dos passageiros num ano.*/
char *somaGetNomeAeroporto(SomaPassageirosAno *somaPassageirosAno);


/*Obtém o total de passageiros associado à soma de passageiros num ano.*/
int somaGetTotalPassageiros(SomaPassageirosAno *somaPassageirosAno);


/*Obtém o próximo elemento na lista da soma de passageiros.*/
SomaPassageirosAno *somaGetNext (SomaPassageirosAno *somaPassageirosAno);


/*Obtém o nome do aeroporto associado à estrutura da mediana.*/
char *medianaGetNome(MedianaAeroporto *medianaAeroporto);


/*Obtém o valor da mediana associado à estrutura da mediana.*/
int medianaGetMediana(MedianaAeroporto *medianaAeroporto);


/*Obtém o o próximo elemento da lista encadeada das medianas.*/
MedianaAeroporto *medianaGetNext (MedianaAeroporto *medianaAeroporto);


/* Função de hash que converte uma chave num índice na tabela hash dos Aeroportos. */
int HashAeroportos(KeyType k);


/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h);


/*Função que liberta a memórica alocada para a hash dos aerportos*/
void destroiTableAeroporto(hash_aeroportos h);


/* Função que retorna o Aeroporto pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k);


/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo);


/* Função para dividir a lista e encontrar o pivô (usada no quicksort)*/
SomaPassageirosAno* dividir(SomaPassageirosAno* head, SomaPassageirosAno** pivot);


/*Função auxiliar que realiza a fusão ordenada de duas listas encadeadas*/
SomaPassageirosAno* mesclar(SomaPassageirosAno* lista1, SomaPassageirosAno* lista2);


/* Função principal do quicksort para listas ligadas */
SomaPassageirosAno* quicksort(SomaPassageirosAno* head);


/* Função para ordenar a lista ligada por total de passageiros decrescente*/
void ordenarListaDecrescente(SomaPassageirosAno** head);


/*Função que obtém o ano de uma data*/
int obterAno(const char *data);


/* Função para criar uma lista de aeroportos vazia*/
ListaAeroportos *criarListaAeroportos(void);


/* Função para adicionar um aeroporto à lista (não adiciona se já existir), ignorando maiúsculas e minúsculas*/
void adicionarAeroporto(ListaAeroportos *lista, const char *nomeAeroporto);


/* Função para destruir a lista de aeroportos e liberar a memória*/
void destruirListaAeroportos(ListaAeroportos *lista);


/*Função que cria uma lista de soma de passageiros para um ano específico.*/
SomaPassageirosAno *criarListaSomaPassageirosAno(hash_voos h, int ano, int n);


/*Função que insere um atraso na lista de atrasos de um aeroporto.*/
void inserirAtraso(MedianaAeroporto *aeroporto, int valor);


/*Função  que compara dois elementos apontados por (a) e (b) e retorna 
um valor negativo se o primeiro elemento for menor que o segundo, zero se 
forem iguais e um valor positivo se o primeiro elemento for maior que o segundo.
*/
int comparar(const void *a, const void *b);


/*Função que calcula a diferença em segundos entre duas datas.*/
int diferencaEmSegundos(char *datetime1, char *datetime2);


/*Função que retorna uma lista encadeada de medianas para os aeroportos.*/
MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h);


/*Função que cria um novo resumo de um voo.*/
VooResumo *createVooResumo(char *id, char *schedule_departure_date, char *real_departure_date, char *destination, char *airline, char *plane_model);


/*Obtém o identificador único associado ao Voo.*/
char *vooResumoGetId(VooResumo *voo_resumo);


/*Obtém a data programada para a partida do voo.*/
char *vooResumoGetScheduleDepartureDate(VooResumo *voo_resumo);


/*Obtém a data verdadeira de partida do voo.*/
char *vooResumoGetRealDepartureDate(VooResumo *voo_resumo);


/*Obtém o aeroporto de destino do voo.*/
char *vooResumoGetDestination(VooResumo *voo_resumo);


/*Obtém a companhia aérea responsável pelo voo.*/
char *vooResumoGetAirline(VooResumo *voo_resumo);


/*Obtém o modelo do avião desse voo*/
char *vooResumoGetPlaneModel(VooResumo *voo_resumo);


/*Obtém o número total de passageiros nesse voo*/
int vooResumoGetTotalPassengers(VooResumo *voo_resumo);


/*Obtém o próximo resumo do voo*/
VooResumo *vooResumoGetNext(VooResumo *voo_resumo);


/*Define o próximo resumo do voo*/
void setNextVooResumo(struct VooResumo *voo_resumo, struct VooResumo *next_voo_resumo);


/*Liberta a memória alocada para o vooresumo*/
void destroiVooResumo(VooResumo *vooResumo);


/* Função para incrementar o número total de passageiros na lista ligada VooResumo de um Aeroporto */
int InsertPassengerVooResumo(hash_aeroportos h_aeroportos, KeyType voo_id);


/* Função que retorna uma lista de resumos de Voos entre as datas especificadas para um determinado 
Aeroporto. */
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date);


/*Liberta a memoria alocada para um resumo de voo.*/
void destroiVooAeroportoEntreDatas(VooResumo *voo_resumo);


/*Liberta a memória alocada para a soma de passageiros num ano*/
void destroiSomaPassageirosAno(SomaPassageirosAno *somaPassageirosAno);


/*Liberta a memória alocada para a mediana de um aeroporto*/
void destroiMedianaAeroporto(MedianaAeroporto *medianaAeroporto);


#endif

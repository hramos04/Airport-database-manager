#ifndef AEROPORTO_H
#define AEROPORTO_H
#define HASHSIZEVOO 10050 // Tamanho da tabela hash

#include "../include/voo.h"




/* Definição do KeyType*/
typedef char KeyType[300];

/* Definição da estrutura Aeroporto, que apresenta o respetivo nome de cada Aeroporto e a lista ligada 
VooResumo que apresenta então todos os voos associados a um determinado Aeroporto. */
typedef struct Aeroporto Aeroporto;

typedef struct VooResumo VooResumo;


typedef struct AeroportoNode AeroportoNode;

/* Definição da tabela hash que vai guardar todos os diferentes Aeroportos. */

// Estrutura para a lista de aeroportos
typedef struct ListaAeroportos ListaAeroportos;

typedef struct SomaPassageirosAno SomaPassageirosAno;


typedef struct MedianaAeroporto MedianaAeroporto;

typedef Aeroporto *hash_aeroportos[HASHSIZEVOO];

Aeroporto *createAeroporto(char *name);


char *aeroportoGetName(Aeroporto *aeroporto);

Aeroporto *aeroportoGetNext(Aeroporto *aeroporto);

void setNextAeroporto(Aeroporto *aeroporto, Aeroporto *next);

VooResumo *aeroportoGetNextResumo(Aeroporto *aeroporto);

void setNextAeroporto(Aeroporto *aeroporto, Aeroporto *next);

void setNextVooResumoAeroporto(Aeroporto *aeroporto, VooResumo *next);

char *somaGetNomeAeroporto(SomaPassageirosAno *somaPassageirosAno);

int somaGetTotalPassageiros(SomaPassageirosAno *somaPassageirosAno);

SomaPassageirosAno *somaGetNext (SomaPassageirosAno *somaPassageirosAno);

char *medianaGetNome(MedianaAeroporto *medianaAeroporto);

int medianaGetMediana(MedianaAeroporto *medianaAeroporto);

MedianaAeroporto *medianaGetNext (MedianaAeroporto *medianaAeroporto);


/* Função de hash que converte uma chave num índice na tabela hash dos Aeroportos. */
int HashAeroportos(KeyType k);

/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h);

void destroiTableAeroporto(hash_aeroportos h);


/* Função que retorna o Aeroporto pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k);

/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo);


/* Função para imprimir a tabela hash de aeroportos */
void PrintHashAeroportos(hash_aeroportos h_aeroportos);



// Função para dividir a lista e encontrar o pivô (usada no quicksort)
SomaPassageirosAno* dividir(SomaPassageirosAno* head, SomaPassageirosAno** pivot);

// Função para  duas listas ordenadas
SomaPassageirosAno* mesclar(SomaPassageirosAno* lista1, SomaPassageirosAno* lista2);

// Função principal do quicksort para listas ligadas
SomaPassageirosAno* quicksort(SomaPassageirosAno* head);

// Função para ordenar a lista ligada por total de passageiros decrescente
void ordenarListaDecrescente(SomaPassageirosAno** head);


int obterAno(const char *data);


// Função para criar uma lista de aeroportos vazia
ListaAeroportos *criarListaAeroportos(void);

// Função para adicionar um aeroporto à lista (não adiciona se já existir), ignorando maiúsculas e minúsculas
void adicionarAeroporto(ListaAeroportos *lista, const char *nomeAeroporto);


// Função para destruir a lista de aeroportos e liberar a memória
void destruirListaAeroportos(ListaAeroportos *lista);

SomaPassageirosAno *criarListaSomaPassageirosAno(hash_voos h, int ano, int n);


// Função para imprimir a lista de soma de passageiros por ano
void imprimirListaSomaPassageirosAno(SomaPassageirosAno *lista);

void inserirAtraso(MedianaAeroporto *aeroporto, int valor);

int comparar(const void *a, const void *b);

int diferencaEmSegundos(char *datetime1, char *datetime2);


MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h);

void inserirAtraso(MedianaAeroporto *aeroporto, int valor);

int comparar(const void *a, const void *b);


/* Função para incrementar o número total de passageiros na lista ligada VooResumo de um Aeroporto */
int InsertPassengerVooResumo(hash_aeroportos h_aeroportos, KeyType voo_id);

/* Função que retorna uma lista de resumos de Voos entre as datas especificadas para um determinado 
Aeroporto. */
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date);

VooResumo *createVooResumo(char *id, char *schedule_departure_date, char *real_departure_date, char *destination, char *airline, char *plane_model);

char *vooResumoGetId(VooResumo *voo_resumo);

char *vooResumoGetScheduleDepartureDate(VooResumo *voo_resumo);

char *vooResumoGetRealDepartureDate(VooResumo *voo_resumo);

char *vooResumoGetDestination(VooResumo *voo_resumo);

char *vooResumoGetAirline(VooResumo *voo_resumo);

char *vooResumoGetPlaneModel(VooResumo *voo_resumo);

int vooResumoGetTotalPassengers(VooResumo *voo_resumo);

VooResumo *vooResumoGetNext(VooResumo *voo_resumo);

void setNextVooResumo(struct VooResumo *voo_resumo, struct VooResumo *next_voo_resumo);

void destroiVooResumo(VooResumo *vooResumo);

void destroiSomaPassageirosAno(SomaPassageirosAno *somaPassageirosAno);

void destroiMedianaAeroporto(MedianaAeroporto *medianaAeroporto);

void destroiVooAeroportoEntreDatas(VooResumo *voo_resumo);

#endif

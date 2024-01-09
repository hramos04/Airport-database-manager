#ifndef VOO_H
#define VOO_H
#define HASHSIZE 10050 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];

typedef struct MedianaAeroporto {
	char *name;
	int *atrasos;
	int tamanho;
    int capacidade;
    int mediana;
    struct MedianaAeroporto *next;
} MedianaAeroporto;



/* Definição da estrutura do Voo, que apresenta todos os dados relativos a cada voo, 
sendo ainda acrescentado o número total de passageiros, de cada voo, e o respetivo delay. */
typedef struct Voo {
    char *id;
    char *airline;
    char *plane_model;
    char *total_seats;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;
    char *copilot;
    char *notes;
    int total_passengers;
    int delay;
    struct Voo *next_voo;
} Voo;


/* Definição de um nó da lista ligada VooResumo, que apresenta dados filtrados e importantes 
de cada voo. */
typedef struct VooResumo {
    char *id;
    char *schedule_departure_date;
    char *real_departure_date;
    char *destination;
    char *airline;
    char *plane_model;
    struct VooResumo *next_resumo;
} VooResumo;

/* Definição da estrutura Aeroporto, que apresenta o respetivo nome de cada Aeroporto e a lista ligada 
VooResumo que apresenta então todos os voos associados a um determinado Aeroporto. */
typedef struct Aeroporto {
	char *name;
	struct Aeroporto *next;
	struct VooResumo *next_resumo;
} Aeroporto;


/* Definição da tabela hash que vai guardar todos os diferentes Aeroportos. */
typedef Aeroporto *hash_aeroportos[HASHSIZE];


/* Definição da tabela hash que vai guardar todos os diferentes Voos. */
typedef Voo *hash_voos[HASHSIZE];


/* Função de hash que converte uma chave num índice na tabela hash dos Aeroportos. */
int HashAeroportos(KeyType k);


/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
int HashVoos(KeyType k);


/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h);


/* Função que inicializa a tabela de hash Voos. */
void InitializeTableVoos(hash_voos h);


/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Voo *RetrieveVoo(hash_voos h, KeyType k);


/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k);


/* Função que retorna o Aeroporto pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k);


/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s);


/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo);


/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo);


/* Função que retorna uma lista de resumos de Voos entre as datas especificadas para um determinado 
Aeroporto. */
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date);

MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h);

#endif


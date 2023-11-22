#ifndef VOO_H
#define VOO_H
#define HASHSIZE 10050 // Tamanho da tabela hash

typedef char KeyType[300];


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

typedef struct VooResumo {
    char *id;
    char *schedule_departure_date;
    char *destination;
    char *airline;
    char *plane_model;
    struct VooResumo *next_resumo;
} VooResumo;

typedef struct Aeroporto {
	char *name;
	struct Aeroporto *next;
	struct VooResumo *next_resumo;
} Aeroporto;

typedef Aeroporto *hash_aeroportos[HASHSIZE];
typedef Voo *hash_voos[HASHSIZE];


int HashAeroportos(KeyType k);
int HashVoos(KeyType k) ;
void InitializeTableAeroportos(hash_aeroportos h);
void InitializeTableVoos(hash_voos h);
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo);
Voo *RetrieveVoo(hash_voos h, KeyType k);
int InsertPassengerVoo(hash_voos h, KeyType k);
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo);
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date);
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k) ;
void convertToUpper(char *s) ;

#endif


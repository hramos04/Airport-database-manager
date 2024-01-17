#ifndef VOO_H
#define VOO_H
#define HASHSIZEVOO 10050 // Tamanho da tabela hash



/* Definição do KeyType*/
typedef char KeyType[300];

/* Definição da estrutura do Voo, que apresenta todos os dados relativos a cada voo, 
sendo ainda acrescentado o número total de passageiros, de cada voo, e o respetivo delay. */
typedef struct Voo Voo;



typedef Voo *hash_voos[HASHSIZEVOO];
   




Voo *createVoo(char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes);

char *vooGetId(Voo *voo);

char *vooGetAirline(Voo *voo);

char *vooGetPlaneModel(Voo *voo);

char *vooGetTotalSeats(Voo *voo);

char *vooGetOrigin(Voo *voo);

char *vooGetDestination(Voo *voo);

char *vooGetScheduleDepartureDate(Voo *voo);

char *vooGetScheduleArrivalDate(Voo *voo);

char *vooGetRealDepartureDate(Voo *voo);

char *vooGetRealArrivalDate(Voo *voo);

char *vooGetPilot(Voo *voo);

char *vooGetCopilot(Voo *voo);

char *vooGetNotes(Voo *voo);

int vooGetTotalPassengers(Voo *voo);

int vooGetDelay(Voo *voo);

Voo *vooGetNext(Voo *voo);

void setNextVoo(struct Voo *voo, struct Voo *next_voo);


/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
int HashVoos(KeyType k);


/* Função que inicializa a tabela de hash Voos. */
void InitializeTableVoos(hash_voos h);


void destroiTableVoo(hash_voos h);

/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Voo *RetrieveVoo(hash_voos h, KeyType k);

/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k);

/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s);

/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo);

/* Função para imprimir a tabela hash de voos filtrando por origem, destino e ano de Schedule Departure Date,
   considerando insensibilidade a maiúsculas e minúsculas */
void PrintHashVoos(hash_voos h_voos);

////////////////////////////////////////função que dá o número total de passageiros num ano 
// Função para somar o total de passageiros para voos em um determinado ano
int SomaPassageirosPorAno(hash_voos h, int ano);

//////////////Soma passageiros por mês////////////
// Função para somar o número de passageiros para um determinado ano e imprimir por mês
int SomaPassageirosPorMes(hash_voos h, int ano, int mes);

//////////////Soma passageiros por dia////////////
// Função para somar o número de passageiros para um determinado ano, mês e dia, e imprimir por dia
int SomaPassageirosPorDia(hash_voos h, int ano, int mes, int dia);

////////////função dá o número de voos por ano 
// Função para somar o número de voos para um determinado ano
int SomaVoosPorAno(hash_voos h, int ano);

////////////função dá número de voos por mês 
// Função para somar o número total de voos para um determinado ano e imprimir por mês
int SomaVoosPorMes(hash_voos h, int ano, int mes);

int SomaVoosPorDia(hash_voos h, int ano, int mes, int dia);




#endif


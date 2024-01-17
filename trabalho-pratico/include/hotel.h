#ifndef HOTEL_H
#define HOTEL_H
#define HASHSIZERESERVA 41000 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];

typedef struct ReservaResumo ReservaResumo; 

typedef struct Hotel Hotel;

/* Definição da tabela hash que vai guardar todos os diferentes Hoteis. */
typedef Hotel *hash_hoteis[HASHSIZERESERVA];

ReservaResumo *createReservaResumo(char *id, char *begin_date, char *end_date, char *user_id, char *price_per_night, double total_price, double rating);

char *reservaResumoGetId(ReservaResumo *reservaResumo);

char *reservaResumoGetBeginDate(ReservaResumo *reservaResumo);

char *reservaResumoGetEndDate(ReservaResumo *reservaResumo);

char *reservaResumoGetUserId(ReservaResumo *reservaResumo);

char *reservaResumoGetPricePerNight(ReservaResumo *reservaResumo);

double reservaResumoGetTotalPrice(ReservaResumo *reservaResumo);

double reservaResumoGetRating(ReservaResumo *reservaResumo);

ReservaResumo *reservaResumoGetNext(ReservaResumo *reservaResumo);

char *hotelGetId(Hotel *hotel);

Hotel *hotelGetNext(Hotel *hotel);

void setNextHotel(Hotel *hotel, Hotel *next);

ReservaResumo *hotelGetNextResumo(Hotel *hotel);

void setNextHotelResumo(Hotel *hotel, Hotel *next);

/* Função de hash que converte uma chave num índice na tabela hash dos hoteis. */
int HashHoteis(KeyType k);

/* Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h);


/* A função verifica se um Hotel está presente na tabela hash. Caso não esteja, adiciona o novo Hotel 
à tabela. Posteriormente, insere ordenadamente um novo ReservaResumo associado a esse hotel, na 
lista ligada, vinculada a esse Hotel .*/
void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva);

/* Função que retorna o Hotel pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Hotel *RetrieveHotel(hash_hoteis h, KeyType k);


void destroiReservaResumo(ReservaResumo *reservaResumo);

void destroiTableHotel(hash_hoteis h);


/* Função que calcula a média das classificações de um hotel, percorrendo a lista ligada 
das reservas e somando os diferentes ratings em cada reserva. */
double GetRatingByHotel(hash_hoteis h, KeyType k);


int CalcularNumeroNoitesDias(char *start_date, char *end_date);

int CalcularNumeroNoitesMes(char *start_date, char *end_date);

/* Função para obter o lucro de um hotel entre duas datas */
int GetLucro(hash_hoteis h, KeyType k, char *start_date, char *end_date);







#endif

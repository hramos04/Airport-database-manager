#ifndef RESERVA_H
#define RESERVA_H
#define HASHSIZERESERVA 41000 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];


/* Definição da estrutura da Reserva, que apresenta todos os dados relativos a cada reserva, 
sendo ainda acrescentado o número total de noites, da respetiva reserva, e o total gasto . */
typedef struct Reserva Reserva;


/* Definição da tabela hash que vai guardar todas as diferentes Reservas. */
typedef Reserva *hash_reservas[HASHSIZERESERVA];

Reserva *createReserva(char *id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment, int total_noites, double total_gasto);

/* Função de hash que converte uma chave num índice na tabela hash das reservas. */
int HashReservas(KeyType k);

char *reservaGetId(Reserva *reserva);

char *reservaGetUserId(Reserva *reserva);

char *reservaGetHotelId(Reserva *reserva);

char *reservaGetHotelName(Reserva *reserva);

char *reservaGetHotelStars(Reserva *reserva);

char *reservaGetCityTax(Reserva *reserva);

char *reservaGetAddress(Reserva *reserva);

char *reservaGetBeginDate(Reserva *reserva);

char *reservaGetEndDate(Reserva *reserva);

char *reservaGetPricePerNight(Reserva *reserva);

char *reservaGetIncludesBreakfast(Reserva *reserva);

char *reservaGetRoomDetails(Reserva *reserva);

char *reservaGetRating(Reserva *reserva);

char *reservaGetComment(Reserva *reserva);

int reservaGetTotalNoites(Reserva *reserva);

double reservaGetTotalGasto(Reserva *reserva);

Reserva *reservaGetNext(Reserva *reserva);


/* Função que inicializa a tabela de hash Reservas. */
void InitializeTableReservas(hash_reservas h);


/* Função que retorna a Reserva pretendida, caso esta se encontre na hash, através da sua respetiva 
chave. */
Reserva *RetrieveReserva(hash_reservas h, KeyType k);


void destroiTableReserva(hash_reservas h);




/* A função insere uma Reserva na tabela hash das Reservas, caso a posição estiver livre coloca a 
Reserva nessa posição, caso a posição já estiver ocupada,diciona a reserva no início da lista 
encadeada dessa posição. */
void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva);



#endif


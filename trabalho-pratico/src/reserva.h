#ifndef RESERVA_H
#define RESERVA_H
#define HASHSIZE 10050 // Tamanho da tabela hash

typedef char KeyType[300];


typedef struct Reserva {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_tax;
    char *address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;
    int total_noites;
    double total_gasto;
    struct Reserva *next_reserva;
} Reserva;

typedef struct ReservaResumo {
    char *id;
    char *begin_date;
    char *end_date;
    char *user_id;
    double total_price;
    double rating;
    struct ReservaResumo *next_resumo;
} ReservaResumo;

typedef struct Hotel {
	char *hotel_id;
	struct Hotel *next;
	struct ReservaResumo *next_resumo;
} Hotel;

typedef Hotel *hash_hoteis[HASHSIZE];
typedef Reserva *hash_reservas[HASHSIZE];

void InitializeTableHoteis(hash_hoteis h);
double GetRatingByHotel(hash_hoteis h, KeyType k);
void InitializeTableReservas(hash_reservas h);
Reserva *RetrieveReserva(hash_reservas h, KeyType k);
Hotel *RetrieveHotel(hash_hoteis h, KeyType k);
void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva);
void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva);
void Printhash_reserva(hash_reservas h);
void Printhash_hoteis(hash_hoteis h);

#endif


#ifndef RESERVATION_H
#define RESERVATION_H
#define HASHSIZE 10050 

typedef struct Reservation{
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
    struct Reservation *next;    
} Reservation;


// Tabela hash
typedef Reservation *HashTableReservation[HASHSIZE];

// Função hash
int HashReservation(char *id);

// Função para inicializar a tabela hash
void InitializeTableReservation(HashTableReservation h);

// Função para inserir na tabela hash
void InsertTableReservation(HashTableReservation h, char *id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment);

// Função para imprimir a tabela hash
void PrintHashTableReservation(HashTableReservation h);
/*
typedef struct Hotel{
    
}*/

#endif

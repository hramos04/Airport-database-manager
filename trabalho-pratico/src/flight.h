#ifndef FLIGHT_H
#define FLIGHT_H
#define HASHSIZE 10050 

typedef struct Flight {
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
    char *passengers_number;
    struct Flight *next;
} Flight;

// Tabela hash
typedef Flight * hash_flight[HASHSIZE];

// Função hash
int Hash_flight(char *id);

// Função para inicializar a tabela hash
void InitializeTable_flight(hash_flight h);

// Função para inserir na tabela hash
void InsertTable_flight(hash_flight h, char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes, char *passsengers_number);

// Função para imprimir a tabela hash
void PrintHash_flight(hash_flight h);
/*
typedef struct Aeroport{
    
}*/

#endif
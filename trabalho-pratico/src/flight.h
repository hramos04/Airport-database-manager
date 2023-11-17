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
typedef Flight *HashTableFlight[HASHSIZE];

// Função hash
int HashFlight(char *id);

// Função para inicializar a tabela hash
void InitializeTableFlight(HashTableFlight h);

// Função para inserir na tabela hash
void InsertTableFlight(HashTableFlight h, char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes);

// Função para imprimir a tabela hash
void PrintHashTableFlight(HashTableFlight h);
/*
typedef struct Aeroport{
    
}*/

#endif

#ifndef PASSENGER_H
#define PASSENGER_H
#define HASHSIZE 10050 // Tamanho da tabela hash


// Estrutura para representar usuários
typedef struct Passenger {
    char *flight_id;
    char *user_id;
    struct Passenger *next;
} Passenger;

// Tabela hash
typedef Passenger *HashTablePassenger[HASHSIZE];

// Função hash
int HashPassenger(char *id);

// Função para inicializar a tabela hash
void InitializeTablePassenger(HashTablePassenger h);

// Função para inserir na tabela hash
void InsertTablePassenger(HashTablePassenger h, char *flight_id, char *user_id);

// Função para imprimir a tabela hash
void PrintHashTablePassenger(HashTablePassenger h);

#endif


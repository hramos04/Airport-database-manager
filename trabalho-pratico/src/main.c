#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "parsing.h"

int main(int argc, char *argv[]) {
	
    hash_user minhaTabela;
    InitializeTable(minhaTabela);
    
     // Leitura e parsing do ficheiro "users.csv"
	char *csv_users = (char*)malloc(256);
	strcpy(csv_users, argv[1]);
	strcat(csv_users, "/users.csv");
	
	char *csv_reservas = (char*)malloc(256);
	strcpy(csv_reservas, argv[1]);
	strcat(csv_reservas, "/reservations.csv");
	
	char *csv_passageiros = (char*)malloc(256);
	strcpy(csv_passageiros, argv[1]);
	strcat(csv_passageiros, "/passengers.csv");

    process_csv_file(csv_users, minhaTabela, parse_users_csv);
    process_csv_file(csv_reservas, minhaTabela, parse_reservations_csv);
    process_csv_file(csv_passageiros, minhaTabela, parse_passengers_csv);

    // Imprimir conteúdo da tabela hash
    printf("Conteúdo da Tabela Hash:\n");
    Printhash_user(minhaTabela);

    return 0;
}





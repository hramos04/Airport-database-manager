#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "parsing.h"
#include "reserva.h"
#include "voo.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
	char linha[1024];
	if(argc < 2) {
		return 0;
	}
    hash_user h_users;
    hash_hoteis h_hoteis;
    hash_reservas h_reservas;
    hash_voos h_voos;
    hash_aeroportos h_aeroportos;
    
    InitializeTable(h_users);
    InitializeTableHoteis(h_hoteis);
    InitializeTableReservas(h_reservas);
    InitializeTableVoos(h_voos);
    
     // Leitura e parsing do ficheiro "users.csv"
	char *csv_users = (char*)malloc(256);
	strcpy(csv_users, argv[1]);
	strcat(csv_users, "/users.csv");
	
	char *csv_reservas = (char*)malloc(256);
	strcpy(csv_reservas, argv[1]);
	strcat(csv_reservas, "/reservations.csv");
	
	char *csv_voos = (char*)malloc(256);
	strcpy(csv_voos, argv[1]);
	strcat(csv_voos, "/flights.csv");
	
	char *csv_passengers = (char*)malloc(256);
	strcpy(csv_passengers, argv[1]);
	strcat(csv_passengers, "/passengers.csv");
	
    process_users_csv(h_users, csv_users);
    process_reservas_csv(h_users, h_hoteis, h_reservas, csv_reservas);
    process_voos_csv(h_users, h_aeroportos, h_voos, csv_voos);
    process_passengers_csv(h_users, h_voos, csv_passengers);
	
	
	
	FILE *fp = fopen(argv[2], "r");
	int i = 1;
	char str_i[100];
	if(fp) {
		while((fgets(linha, 1024, fp)) != NULL) {
			linha[strlen(linha)-2] = '\0';
			char *destination_folder = (char*)malloc(256);
			strcpy(destination_folder, "Resultados/command");
			sprintf(str_i, "%d",i);
			strcat(destination_folder, str_i);
			strcat(destination_folder, "_output.txt");
			FILE *fp_output = fopen(destination_folder, "w");
			comando(linha, h_users, h_voos, h_reservas, h_hoteis, fp_output);
			fclose(fp_output);
			free(destination_folder);
			i++;
		}
		fclose(fp);
	}
    
    

    return 0;
}





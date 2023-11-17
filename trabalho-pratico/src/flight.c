#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"



int HashFlight(char *id) {
    int hash = 0;
    while (*id) {
        hash += *id;
        ++id;
    }
    return hash % HASHSIZE;
}

// Função para inicializar a tabela hash
void InitializeTableFlight(HashTableFlight h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

Flight *RetrieveFlight(HashTableFlight h, char *id) {
	 int i = HashFlight(id);
	 Flight *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->id, id) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}



/*void InsertReserva(HashTable h, char *id, Reserva reserva) {
	User *res = RetrieveUser(h, id);
	if(res) {
		//inserir na lista ligada de reservas do User
		
		
	}
	
}*/



// Função para inserir na tabela hash usando encadeamento separado em caso de colisão
void InsertTableFlight(HashTableFlight h, char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes) {
    
    
    
    int i = HashFlight(id);

    // Criar novo usuário
    Flight *novo_voo = malloc(sizeof(Flight));
    novo_voo->id = strdup(id);
    novo_voo->airline = strdup(airline);
    novo_voo->plane_model = strdup(plane_model);
    novo_voo->total_seats = strdup(total_seats);
    novo_voo->origin = strdup(origin);
    novo_voo->destination = strdup(destination);
    novo_voo->schedule_departure_date = strdup(schedule_departure_date);
    novo_voo->schedule_arrival_date = strdup(schedule_arrival_date);
    novo_voo->real_departure_date = strdup(real_departure_date);
    novo_voo->real_arrival_date = strdup(real_arrival_date);
    novo_voo->pilot = strdup(pilot);
    novo_voo->copilot = strdup(copilot);
    novo_voo->notes= strdup(notes);
    novo_voo->next = NULL;

    // Lidar com colisões usando encadeamento separado
    if (h[i] == NULL) {
        // Se o slot estiver vazio, apenas insira o novo usuário
        h[i] = novo_voo;
        printf("inseri: %s\n",novo_voo->id);
    } else {
        // Se houver colisão, adicione o novo usuário no início da lista
        novo_voo->next = h[i];
        h[i] = novo_voo;
    }
}


// Função para imprimir a tabela hash
void PrintHashTableFlight(HashTableFlight h) {
    for (int i = 0; i < HASHSIZE; ++i) {
        Flight *aux = h[i];
        while (aux) {
			printf("ID: %s, Airline: %s, Plane model: %s, Total Seats: %s, Origin: %s, Destination: %s, Schedule Departure Date: %s, Schedule Arrival Date: %s, Real Departure Date: %s, Real Arrival Date: %s, Pilot: %s, Copilot: %s, Notes: %s\n",
                   aux->id, aux->airline, aux->plane_model, aux->total_seats,
                   aux->origin, aux->destination, aux->schedule_departure_date, aux->schedule_arrival_date,
                   aux->real_departure_date, aux->real_arrival_date, aux->pilot, aux->copilot, aux->notes);
            aux = aux->next;
        }
    }
}










#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"


int HashReservation(char *id) {
    int hash = 0;
    while (*id) {
        hash += *id;
        ++id;
    }
    return hash % HASHSIZE;
}

// Função para inicializar a tabela hash
void InitializeTableReservation(HashTableReservation h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

Reservation *RetrieveReservation(HashTableReservation h, char *id) {
	 int i = HashReservation(id);
	 Reservation *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->id, id) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}



/*void InsertReserva(HashTable h, char *id, Reserva reserva) {
	Reservation *res = RetrieveReservation(h, id);
	if(res) {
		//inserir na lista ligada de reservas do Reservation
		
		
	}
	
}*/



// Função para inserir na tabela hash usando encadeamento separado em caso de colisão
void InsertTableReservation(HashTableReservation h, char *id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment){
    
    
    
    int i = HashReservation(id);

    // Criar nova usuário
    Reservation *nova_reserva = malloc(sizeof(Reservation));
    nova_reserva->id = strdup(id);
    nova_reserva->user_id = strdup(user_id);
    nova_reserva->hotel_id = strdup(hotel_id);
    nova_reserva->hotel_name = strdup(hotel_name);
    nova_reserva->hotel_stars = strdup(hotel_stars);
    nova_reserva->city_tax = strdup(city_tax);
    nova_reserva->address = strdup(address);
    nova_reserva->begin_date = strdup(begin_date);
    nova_reserva->end_date = strdup(end_date);
    nova_reserva->price_per_night = strdup(price_per_night);
    nova_reserva->includes_breakfast = strdup(includes_breakfast);
    nova_reserva->room_details = strdup(room_details);
    nova_reserva->rating = strdup(rating);
    nova_reserva->comment = strdup(comment);
    nova_reserva->next = NULL;

    // Lidar com colisões usando encadeamento separado
    if (h[i] == NULL) {
        // Se o slot estiver vazio, apenas insira o nova usuário
        h[i] = nova_reserva;
        printf("inseri: %s\n",nova_reserva->id);
    } else {
        // Se houver colisão, adicione o nova usuário no início da lista
        nova_reserva->next = h[i];
        h[i] = nova_reserva;
    }
}


// Função para imprimir a tabela hash
void PrintHashTableReservation(HashTableReservation h) {
    for (int i = 0; i < HASHSIZE; ++i) {
        Reservation *aux = h[i];
        while (aux) {
			printf("ID: %s, User Id: %s, Hotel Id: %s, Hotel Name: %s, Hotel Stars: %s, City Tax: %s, Address: %s, Begin Date: %s, End Date: %s, Price Per Night: %s, Includes Breakfast: %s, Room Details: %s\n, Rating: %s\n, Comment: %s\n",
                   aux->id, aux->user_id, aux->hotel_id, aux->hotel_name,
                   aux->hotel_stars, aux->city_tax, aux->address, aux->begin_date,
                   aux->end_date, aux->price_per_night, aux->includes_breakfast, 
                   aux->room_details,aux->rating,aux->comment);
            aux = aux->next;
        }
    }
}











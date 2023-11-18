#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"

int HashHoteis(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZE;
}

int HashReservas(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZE;
}

void InitializeTableHoteis(hash_hoteis h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

void InitializeTableReservas(hash_reservas h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

Reserva *RetrieveReserva(hash_reservas h, KeyType k) {
	 int i = HashReservas(k);
	 Reserva *res;
	 for(res = h[i]; res; res = res->next_reserva) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

Hotel *RetrieveHotel(hash_hoteis h, KeyType k) {
	 int i = HashHoteis(k);
	 Hotel *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->hotel_id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

double GetRatingByHotel(hash_hoteis h, KeyType k) {
	Hotel *aux = RetrieveHotel(h, k);
	if(aux) {
		double total_rating = 0;;
		int total_opinioes = 0;
		ReservaResumo *reserva = aux->next_resumo;
		while(reserva) {
			if(reserva->rating >= 1 && reserva->rating <= 5) {
				total_opinioes++;
				total_rating += reserva->rating;
			}
			
			reserva = reserva->next_resumo;
		}
		
		if(total_opinioes > 0) {
			
			return total_rating/total_opinioes;
		}
	}
	return -1;
}



void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva) {
    int i = HashHoteis(k);
    
    Hotel *aux = RetrieveHotel(h, k);
    if(!aux) {
		Hotel *novo_hotel = (Hotel *)malloc(sizeof(Hotel));
		novo_hotel->hotel_id = strdup(k);
		novo_hotel->next = NULL;
		novo_hotel->next_resumo = NULL;
		aux = novo_hotel;
		if (h[i] == NULL) {
			h[i] = aux;
		}
		else {
			aux->next = h[i];
			h[i] = aux;
		}
	}
	
	ReservaResumo *currentQ2 = aux->next_resumo;
	ReservaResumo *prevQ2 = NULL;
	
	while (currentQ2 != NULL && strcmp(currentQ2->begin_date, reserva->begin_date) >= 0) {
		
		prevQ2 = currentQ2;
		currentQ2 = currentQ2->next_resumo;
	}

	if (prevQ2 == NULL) {
		// Inserir no início
		reserva->next_resumo = aux->next_resumo;
		aux->next_resumo = reserva;
	} else {
		// Inserir no meio ou no final
		prevQ2->next_resumo = reserva;
		reserva->next_resumo = currentQ2;
	}
}


void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva) {
    int i = HashReservas(k);
    if (h[i] == NULL) {
        h[i] = reserva;
    }
    else {
        reserva->next_reserva = h[i];
        h[i] = reserva;
    }
}

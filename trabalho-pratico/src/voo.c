#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voo.h"

int HashAeroportos(KeyType k) {
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

int HashVoos(KeyType k) {
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

void InitializeTableAeroportos(hash_aeroportos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

void InitializeTableVoos(hash_voos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

Voo *RetrieveVoo(hash_voos h, KeyType k) {
	 int i = HashVoos(k);
	 Voo *res;
	 for(res = h[i]; res; res = res->next_voo) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}


int InsertPassengerVoo(hash_voos h, KeyType k) {
	 Voo *aux = RetrieveVoo(h, k);
	 if(aux) {
		 aux->total_passengers++;
		 return 1;
	 }
	 return 0;
}

/*Hotel *RetrieveAeroporto(hash_hoteis h, KeyType k) {
	 int i = HashHoteis(k);
	 Hotel *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->hotel_id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}*/

/*void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva) {
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
	reserva->next_resumo = aux->next_resumo;
	aux->next_resumo = reserva;
}*/


void InsertTableVoos(hash_voos h, KeyType k, Voo *voo) {
    int i = HashVoos(k);
    if (h[i] == NULL) {
        h[i] = voo;
    }
    else {
        voo->next_voo = h[i];
        h[i] = voo;
    }
}


void Printhash_voo(hash_voos h) {
	int total_voos = 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        Voo *aux = h[i];
        while(aux) {
			printf("ZZZ: %s\n",aux->id);
			aux = aux->next_voo;
			total_voos++;
		}
        
    }
    printf("Total Voos: %d\n",total_voos);
}


/*void Printhash_hoteis(hash_hoteis h) {
	int total_hoteis = 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        Hotel *aux = h[i];
        
        while(aux) {
			
			int total_reservas_hotel = 0;
			ReservaResumo *reserva = aux->next_resumo;
			while(reserva) {
				total_reservas_hotel++;
				printf("Resumo: %s\n",reserva->id);
				reserva = reserva->next_resumo;
			}
			printf("ZZZ: %s, Reservas: %d\n",aux->hotel_id, total_reservas_hotel);
			
			aux = aux->next;
			total_hoteis++;
		}
        
    }
    printf("Total Hoteis: %d\n",total_hoteis);
}*/











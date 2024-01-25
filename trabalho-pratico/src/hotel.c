#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/hotel.h"


struct ReservaResumo {
    char *id;
    char *begin_date;
    char *end_date;
    char *user_id;
    char *price_per_night;
    double total_price;
    double rating;
    struct ReservaResumo *next_resumo;
};


struct Hotel {
	char *hotel_id;
	struct Hotel *next;
	struct ReservaResumo *next_resumo;
};


ReservaResumo *createReservaResumo(char *id, char *begin_date, char *end_date, char *user_id, char *price_per_night, double total_price, double rating){
    ReservaResumo *reservaResumo = malloc(sizeof(ReservaResumo));
    
    reservaResumo->id = strdup(id);
    reservaResumo->begin_date = strdup(begin_date);
    reservaResumo->end_date = strdup(end_date);
    reservaResumo->user_id = strdup(user_id);
    reservaResumo->price_per_night = strdup(price_per_night);
    reservaResumo->total_price = total_price;
    reservaResumo->rating = rating;
    reservaResumo->next_resumo = NULL;
    
    return reservaResumo;
}


char *reservaResumoGetId(ReservaResumo *reservaResumo){ 
    return strdup(reservaResumo->id);
}


char *reservaResumoGetBeginDate(ReservaResumo *reservaResumo){ 
    return strdup(reservaResumo->begin_date);
}


char *reservaResumoGetEndDate(ReservaResumo *reservaResumo){  
    return strdup(reservaResumo->end_date);
}


char *reservaResumoGetUserId(ReservaResumo *reservaResumo){  
    return strdup(reservaResumo->user_id);
}


double reservaResumoGetTotalPrice(ReservaResumo *reservaResumo){
    return reservaResumo->total_price;
}


double reservaResumoGetRating(ReservaResumo *reservaResumo){
    return reservaResumo->rating;
}


ReservaResumo *reservaResumoGetNext(ReservaResumo *reservaResumo){
    return reservaResumo->next_resumo;
}


Hotel *hotelGetNext(Hotel *hotel){
    return hotel->next;
}


void setNextHotel(Hotel *hotel, Hotel *next){
    hotel->next = next;
}


ReservaResumo *hotelGetNextResumo(Hotel *hotel){
    return hotel->next_resumo;
}


void setNextHotelResumo(Hotel *hotel, Hotel *next){
    hotel->next = next;
}


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
    return h % HASHSIZEHOTEL;
}


void InitializeTableHoteis(hash_hoteis h) {
    int i;
    for (i = 0; i < HASHSIZEHOTEL; ++i)
        h[i] = NULL;
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
		reserva->next_resumo = aux->next_resumo;
		aux->next_resumo = reserva;
	} else {
		prevQ2->next_resumo = reserva;
		reserva->next_resumo = currentQ2;
	}
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


void destroiReservaResumo(ReservaResumo *reservaResumo){

	while(reservaResumo!=NULL){
		ReservaResumo *atual = reservaResumo;
		reservaResumo = reservaResumo->next_resumo;
		free(atual->id);
		free(atual->begin_date);
		free(atual->end_date);	
		free(atual->user_id);
        free(atual->price_per_night);
        free(atual);
	}
	free(reservaResumo);
}


void destroiTableHotel(hash_hoteis h) {

	for(int i = 0; i<HASHSIZEHOTEL; i++){
		Hotel *atual = h[i];
		while(atual!=NULL){
			Hotel *position = atual;
			atual = atual->next;
			free(position->hotel_id);
			destroiReservaResumo(position->next_resumo);
		}
		free(h[i]);
	}
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


int CalcularNumeroNoitesDias(char *start_date, char *end_date) {
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;

    sscanf(start_date, "%d/%d/%d", &start_year, &start_month, &start_day);
    sscanf(end_date, "%d/%d/%d", &end_year, &end_month, &end_day);

    int num_noites;

    num_noites = (end_day - start_day) +1;

    return num_noites;
}


int CalcularNumeroNoitesMes(char *start_date, char *end_date) {
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;

    sscanf(start_date, "%d/%d/%d", &start_year, &start_month, &start_day);
    sscanf(end_date, "%d/%d/%d", &end_year, &end_month, &end_day);

    int num_noites;
    num_noites = (end_year - start_year) * 365 + (end_month - start_month) * 29 + (end_day - start_day);
    

    return num_noites;
}


int GetLucro(hash_hoteis h, KeyType k, char *start_date, char *end_date) {
    Hotel *hotel = RetrieveHotel(h, k);
    if (hotel) {
        int lucro = 0;

        ReservaResumo *reserva_resumo = hotel->next_resumo;
        while (reserva_resumo != NULL) {
            if (strcmp(reserva_resumo->end_date, start_date) < 0 || strcmp(reserva_resumo->begin_date, end_date) > 0) {
                reserva_resumo = reserva_resumo->next_resumo;
                continue;
            }

            char *inicio_reserva = (strcmp(reserva_resumo->begin_date, start_date) >= 0) ? reserva_resumo->begin_date : start_date;
            char *fim_reserva = (strcmp(reserva_resumo->end_date, end_date) <= 0) ? reserva_resumo->end_date : end_date;

            if (strcmp(inicio_reserva, start_date) == 0 && strcmp(fim_reserva, end_date) == 0) {
                int num_noites = CalcularNumeroNoitesDias(inicio_reserva, fim_reserva);
                lucro += num_noites * atof(reserva_resumo->price_per_night);
            } else {
                int num_noites = CalcularNumeroNoitesMes(inicio_reserva, fim_reserva);
                lucro += num_noites * atof(reserva_resumo->price_per_night);
            }
            reserva_resumo = reserva_resumo->next_resumo;
        }
        return lucro;
    }
    return -1; 
}

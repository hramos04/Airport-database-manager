#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/reserva.h"


struct Reserva {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_tax;
    char *address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;
    int total_noites;
    double total_gasto;
    struct Reserva *next_reserva;
};


Reserva *createReserva(char *id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment, int total_noites, double total_gasto){
	Reserva *reserva = malloc(sizeof(Reserva));
	
	reserva->id = strdup(id);
	reserva->user_id = strdup(user_id);
	reserva->hotel_id = strdup(hotel_id);
	reserva->hotel_name = strdup(hotel_name);
	reserva->hotel_stars = strdup(hotel_stars);
	reserva->city_tax = strdup(city_tax);
	reserva->address = strdup(address);
	reserva->begin_date = strdup(begin_date);
	reserva->end_date = strdup(end_date);
	reserva->price_per_night = strdup(price_per_night);
	reserva->includes_breakfast = strdup(includes_breakfast);
	reserva->room_details = strdup(room_details);
	reserva->rating = strdup(rating);
	reserva->comment = strdup(comment);
	
	reserva->total_noites = total_noites;
	reserva->total_gasto = total_gasto;
	reserva->next_reserva = NULL;
	
	return reserva;
}


void freeReserva(Reserva *reserva) {
    if (reserva == NULL) {
        return;
    }

    free(reserva->id);
    free(reserva->user_id);
    free(reserva->hotel_id);
    free(reserva->hotel_name);
    free(reserva->hotel_stars);
    free(reserva->city_tax);
    free(reserva->address);
    free(reserva->begin_date);
    free(reserva->end_date);
    free(reserva->price_per_night);
    free(reserva->includes_breakfast);
    free(reserva->room_details);
    free(reserva->rating);
    free(reserva->comment);

    free(reserva);
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
    return h % HASHSIZERESERVA;
}


void InitializeTableReservas(hash_reservas h) {
    int i;
    for (i = 0; i < HASHSIZERESERVA; ++i)
        h[i] = NULL;
}


char *reservaGetHotelId(Reserva *reserva){ 
	return strdup(reserva->hotel_id);
}


char *reservaGetHotelName(Reserva *reserva){ 
	return strdup(reserva->hotel_name);
}


char *reservaGetHotelStars(Reserva *reserva){ 
	return strdup(reserva->hotel_stars);
}


char *reservaGetBeginDate(Reserva *reserva){ 
	return strdup(reserva->begin_date);
}


char *reservaGetEndDate(Reserva *reserva){ 
	return strdup(reserva->end_date);
}


char *reservaGetIncludesBreakfast(Reserva *reserva){ 
	return strdup(reserva->includes_breakfast);
}


int reservaGetTotalNoites(Reserva *reserva){
	return reserva->total_noites;
}


double reservaGetTotalGasto(Reserva *reserva){
	return reserva->total_gasto;
}


Reserva *reservaGetNext(Reserva *reserva){
	return reserva->next_reserva;
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


void destroiTableReserva(hash_reservas h) {

	for(int i = 0; i<HASHSIZERESERVA; i++){
		Reserva *atual = h[i];
		while(atual!=NULL){
			Reserva *position = atual;
			atual = atual->next_reserva;
			free(position->id);
			free(position->user_id);
			free(position->hotel_id);
			free(position->hotel_name);
			free(position->hotel_stars);
			free(position->city_tax);
			free(position->address);
			free(position->begin_date);
			free(position->end_date);
			free(position->price_per_night);
			free(position->includes_breakfast);
			free(position->room_details);
			free(position->rating);
			free(position->comment);
            free(position);
		}
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


int ContarReservasPorAno(hash_reservas h, int ano) {
    int totalReservas = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            int anoReserva;
            sscanf(res->begin_date, "%d", &anoReserva);

            if (anoReserva == ano) {
                totalReservas++;
            }

            res = res->next_reserva;
        }
    }

    return totalReservas;
}


int ContarReservasPorMes(hash_reservas h, int ano, int mes) {
    int totalReservasNoMes = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            int anoReserva, mesReserva;
            sscanf(res->begin_date, "%d/%d", &anoReserva, &mesReserva);

            if (anoReserva == ano && mesReserva == mes) {
                totalReservasNoMes++;
            }

            res = res->next_reserva;
        }
    }
    return totalReservasNoMes;
}


int ContarReservasPorData(hash_reservas h, int ano, int mes, int dia) {
    int totalReservasNaData = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            int anoReserva, mesReserva, diaReserva;
            sscanf(res->begin_date, "%d/%d/%d", &anoReserva, &mesReserva, &diaReserva);

            if (anoReserva == ano && mesReserva == mes && diaReserva == dia) {
                totalReservasNaData++;
            }

            res = res->next_reserva;
        }
    }
    return totalReservasNaData;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"
#include "../include/aeroporto.h"


struct Voo {
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
    int total_passengers;
    int delay;
    struct Voo *next_voo;
};


Voo *createVoo(char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes, int delay){
    Voo *voo = malloc(sizeof(struct Voo));

    voo->id = strdup(id);
    voo->airline = strdup(airline);
    voo->plane_model = strdup(plane_model);
    voo->total_seats = strdup(total_seats);
    voo->origin = strdup(origin);
    voo->destination = strdup(destination);
    voo->schedule_departure_date = strdup(schedule_departure_date);
    voo->schedule_arrival_date = strdup(schedule_arrival_date);
    voo->real_departure_date = strdup(real_departure_date);
    voo->real_arrival_date = strdup(real_arrival_date);
    voo->pilot = strdup(pilot);
    voo->copilot = strdup(copilot);
    voo->notes = strdup(notes);
    
    voo->total_passengers = 0;
    voo->delay = delay;
    voo->next_voo = NULL;

    return voo;
}


char *vooGetId(Voo *voo){ 
    return strdup(voo->id);
}


char *vooGetAirline(Voo *voo){ 
    return strdup(voo->airline);
}


char *vooGetPlaneModel(Voo *voo){ 
    return strdup(voo->plane_model);
}


char *vooGetOrigin(Voo *voo){  
    return strdup(voo->origin);
}


char *vooGetDestination(Voo *voo){  
    return strdup(voo->destination);
}


char *vooGetScheduleDepartureDate(Voo *voo){ 
    return strdup(voo->schedule_departure_date);
}


char *vooGetScheduleArrivalDate(Voo *voo){ 
    return strdup(voo->schedule_arrival_date);
}


int vooGetTotalPassengers(Voo *voo){
    return voo->total_passengers;
}


int vooGetDelay(Voo *voo){
    return voo->delay;
}


Voo *vooGetNext(Voo *voo){
    return voo->next_voo;
}


void setNextVoo(struct Voo *voo, struct Voo *next_voo) {
    voo->next_voo = next_voo;
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
    return h %HASHSIZEVOO;
}


void InitializeTableVoos(hash_voos h) {
    int i;
    for (i = 0; i <HASHSIZEVOO; ++i)
        h[i] = NULL;
}


void destroiTableVoo(hash_voos h) {

	for(int i = 0; i<HASHSIZEVOO; i++){
		Voo *atual = h[i];
		while(atual!=NULL){
			Voo *position = atual;
			atual = atual->next_voo;
			free(position->id);
			free(position->airline);
			free(position->plane_model);
			free(position->total_seats);
			free(position->origin);
			free(position->destination);
			free(position->schedule_departure_date);
			free(position->schedule_arrival_date);
			free(position->real_departure_date);
			free(position->real_arrival_date);
			free(position->pilot);
			free(position->copilot);
            free(position->notes);
            free(position);
		}
	}
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


void convertToUpper(char *s) {
	for (int j = 0; s[j] != '\0'; j++) {
        s[j] = toupper(s[j]);
    }
}


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


int SomaPassageirosPorAno(hash_voos h, int ano) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo;
            sscanf(voo->schedule_departure_date, "%d", &anoVoo);

            if (anoVoo == ano) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }

    return totalPassageiros;
}


int SomaPassageirosPorMes(hash_voos h, int ano, int mes) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo, mesVoo;
            sscanf(voo->schedule_departure_date, "%d/%d", &anoVoo, &mesVoo);

            if (anoVoo == ano && mesVoo == mes) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }
    return totalPassageiros;
}


int SomaPassageirosPorDia(hash_voos h, int ano, int mes, int dia) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo, mesVoo, diaVoo;
            sscanf(voo->schedule_departure_date, "%d/%d/%d", &anoVoo, &mesVoo, &diaVoo);

            if (anoVoo == ano && mesVoo == mes && diaVoo == dia) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }
    return totalPassageiros;
}


int SomaVoosPorAno(hash_voos h, int ano) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo;
            sscanf(voo->schedule_departure_date, "%d", &anoVoo);

            if (anoVoo == ano) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }

    return totalVoos;
}


int SomaVoosPorMes(hash_voos h, int ano, int mes) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo, mesVoo;
            sscanf(voo->schedule_departure_date, "%d/%d", &anoVoo, &mesVoo);

            if (anoVoo == ano && mesVoo == mes) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }
    return totalVoos;
}


int SomaVoosPorDia(hash_voos h, int ano, int mes, int dia) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            int anoVoo, mesVoo, diaVoo;
            sscanf(voo->schedule_departure_date, "%d/%d/%d", &anoVoo, &mesVoo, &diaVoo);

            if (anoVoo == ano && mesVoo == mes && diaVoo == dia) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }
    return totalVoos;
}


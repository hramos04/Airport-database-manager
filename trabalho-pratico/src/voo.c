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


Voo *createVoo(char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes){
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
    voo->delay = 0;
    voo->next_voo = NULL;

    return voo;
}

char *vooGetId(Voo *voo){ //verificado os leaks
    return strdup(voo->id);
}

char *vooGetAirline(Voo *voo){ //verificado os leaks 
    return strdup(voo->airline);
}

char *vooGetPlaneModel(Voo *voo){ //verificado os leaks
    return strdup(voo->plane_model);
}

char *vooGetOrigin(Voo *voo){  //verificado os leaks 
    return strdup(voo->origin);
}

char *vooGetDestination(Voo *voo){  //verificado os leaks 
    return strdup(voo->destination);
}

char *vooGetScheduleDepartureDate(Voo *voo){ //verificado os leaks
    return strdup(voo->schedule_departure_date);
}

char *vooGetScheduleArrivalDate(Voo *voo){ //verificado os leaks
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




/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
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


/* Função que inicializa a tabela de hash Voos. */
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



/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
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


/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k) {
	 Voo *aux = RetrieveVoo(h, k);
	 if(aux) {
		 aux->total_passengers++;
		 return 1;
	 }
	 return 0;
}

/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s) {
	for (int j = 0; s[j] != '\0'; j++) {
        s[j] = toupper(s[j]);
    }
}


/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
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







/* Função para imprimir a tabela hash de voos filtrando por origem, destino e ano de Schedule Departure Date,
   considerando insensibilidade a maiúsculas e minúsculas */
void PrintHashVoos(hash_voos h_voos) {
    for (int i = 0; i <HASHSIZEVOO; i++) {
        Voo *voo = h_voos[i];

        while (voo != NULL) {
            if ((strcasecmp(voo->origin, "FRA") == 0 || strcasecmp(voo->destination, "FRA") == 0) &&
                (obterAno(voo->schedule_departure_date) == 2023)) {

                printf("Voo ID: %s\n", voo->id);
                printf("  - Airline: %s, Plane Model: %s, Total Seats: %s, Origin: %s, Destination: %s\n",
                       voo->airline, voo->plane_model, voo->total_seats, voo->origin, voo->destination);
                printf("  - Schedule Departure Date: %s, Schedule Arrival Date: %s\n",
                       voo->schedule_departure_date, voo->schedule_arrival_date);
                printf("  - Real Departure Date: %s, Real Arrival Date: %s\n",
                       voo->real_departure_date, voo->real_arrival_date);
                printf("  - Pilot: %s, Copilot: %s, Notes: %s\n", voo->pilot, voo->copilot, voo->notes);
                printf("  - Total Passengers: %d, Delay: %d\n", voo->total_passengers, voo->delay);
            }

            voo = voo->next_voo;
        }
    }
}

void freeVoo(Voo *voo) {
    if (voo == NULL) {
        return;
    }

    free(voo->id);
    free(voo->airline);
    free(voo->plane_model);
    free(voo->total_seats);
    free(voo->origin);
    free(voo->destination);
    free(voo->schedule_departure_date);
    free(voo->schedule_arrival_date);
    free(voo->real_departure_date);
    free(voo->real_arrival_date);
    free(voo->pilot);
    free(voo->copilot);
    free(voo->notes);

    free(voo);
}




/*
////////////////////////////////////////função que dá o número total de passageiros num ano 
// Função para somar o total de passageiros para voos em um determinado ano
int SomaPassageirosPorAno(hash_voos h, int ano) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano do campo schedule_departure_date
            int anoVoo;
            sscanf(voo->schedule_departure_date, "%d", &anoVoo);

            // Verificar se o ano coincide com o ano fornecido
            if (anoVoo == ano) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }

    return totalPassageiros;
}

//////////////Soma passageiros por mês////////////
// Função para somar o número de passageiros para um determinado ano e imprimir por mês
int SomaPassageirosPorMes(hash_voos h, int ano, int mes) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano e o mês do campo schedule_departure_date
            int anoVoo, mesVoo;
            sscanf(voo->schedule_departure_date, "%d/%d", &anoVoo, &mesVoo);

            // Verificar se o ano e o mês coincidem com o ano e mês fornecidos
            if (anoVoo == ano && mesVoo == mes) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }

    // Retornando o resultado
    return totalPassageiros;
}

//////////////Soma passageiros por dia////////////
// Função para somar o número de passageiros para um determinado ano, mês e dia, e imprimir por dia
int SomaPassageirosPorDia(hash_voos h, int ano, int mes, int dia) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano, mês e dia do campo schedule_departure_date
            int anoVoo, mesVoo, diaVoo;
            sscanf(voo->schedule_departure_date, "%d/%d/%d", &anoVoo, &mesVoo, &diaVoo);

            // Verificar se o ano, mês e dia coincidem com o ano, mês e dia fornecidos
            if (anoVoo == ano && mesVoo == mes && diaVoo == dia) {
                totalPassageiros += voo->total_passengers;
            }

            voo = voo->next_voo;
        }
    }

    // Retornando o resultado
    return totalPassageiros;
}

////////////função dá o número de voos por ano 
// Função para somar o número de voos para um determinado ano
int SomaVoosPorAno(hash_voos h, int ano) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano do campo schedule_departure_date
            int anoVoo;
            sscanf(voo->schedule_departure_date, "%d", &anoVoo);

            // Verificar se o ano coincide com o ano fornecido
            if (anoVoo == ano) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }

    return totalVoos;
}


////////////função dá número de voos por mês 
// Função para somar o número total de voos para um determinado ano e imprimir por mês
int SomaVoosPorMes(hash_voos h, int ano, int mes) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano e o mês do campo schedule_departure_date
            int anoVoo, mesVoo;
            sscanf(voo->schedule_departure_date, "%d/%d", &anoVoo, &mesVoo);

            // Verificar se o ano e o mês coincidem com o ano e mês fornecidos
            if (anoVoo == ano && mesVoo == mes) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }

    // Retornando o resultado
    return totalVoos;
}

int SomaVoosPorDia(hash_voos h, int ano, int mes, int dia) {
    int totalVoos = 0;

    for (int i = 0; i < HASHSIZEVOO; i++) {
        Voo *voo = h[i];

        while (voo != NULL) {
            // Extrair o ano, mês e dia do campo schedule_departure_date
            int anoVoo, mesVoo, diaVoo;
            sscanf(voo->schedule_departure_date, "%d/%d/%d", &anoVoo, &mesVoo, &diaVoo);

            // Verificar se a data coincide com a data fornecida
            if (anoVoo == ano && mesVoo == mes && diaVoo == dia) {
                totalVoos++;
            }

            voo = voo->next_voo;
        }
    }

    // Retornando o resultado
    return totalVoos;
}

*/
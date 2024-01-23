#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"
#include "../include/aeroporto.h"


typedef struct Voo {
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
} Voo; 


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

// Adicione esta função para libertar a memória alocada em createVoo
void freeVoo(Voo *voo) {
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





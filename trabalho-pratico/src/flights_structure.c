#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "flights_structure.h"
#include "reservations_structure.h"

typedef struct Flight {
    char *id;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;
    char *copilot;
    char *notes;
};

flight **hash_flight;

void allocate_flight(){
    int i;
    hash_flight = (flight **)malloc(n_lines*sizeof(flight*));
    for (i = 0; i < n_lines; i++){
        hash_flight[i] = NULL;
    }
}

bool insert_hash_flight(char *id,char *airline,char *plane_model,int total_seats,char *origin,char *destination,char *schedule_departure_date,char *schedule_arrival_date,char *real_departure_date,char *real_arrival_date,char *pilot,char *copilot,char *notes){

    flight *f = malloc(sizeof(flight));
    f->id = id;
    f->airline = airline;
    f->plane_model = plane_model;
    f->total_seats = total_seats;
    f->origin = origin;
    f->destination = destination;
    f->schedule_departure_date = schedule_departure_date;
    f->schedule_arrival_date = schedule_arrival_date;
    f->real_departure_date = real_departure_date;
    f->real_arrival_date = real_arrival_date;
    f->pilot = pilot;
    f->copilot = copilot;
    f->notes= notes;

    hash_flight[atoi(id)-1] = f;
    return true;
}

void getFlightDetails (int* id, char**airline, char**plane_model, int* total_seats, char** origin, char**destination, char**schedule_departure_date, char**schedule_arrival_date, char** real_departure_date,char**real_arrival_date,char**pilot,char**copilot,char**notes){
    flight* f = NULL;
    f = hash_flight[*id];

    if (f == NULL){
        *airline=NULL;
        return;
    }
    
    *airline = f-> airline;
    *plane_model = f-> plane_model;
    *total_seats = f-> total_seats;
    *origin = f-> origin;
    *destination = f-> destination;
    *schedule_departure_date = f->schedule_departure_date;
    *schedule_arrival_date = f->schedule_arrival_date;
    *real_departure_date = f->real_departure_date;
    *real_arrival_date = f->real_arrival_date;
    *pilot = f->pilot;
    *copilot = f->copilot;
    *notes = f->notes;
}

void free_hash_flights(){
    int i;
    for(i=0;i<n_lines;i++){
        if(hash_flight[i]!=NULL){
            free(hash_flight[i]->id);
            free(hash_flight[i]->airline);
            free(hash_flight[i]->plane_model);
            free(hash_flight[i]->origin);
            free(hash_flight[i]->destination);
            free(hash_flight[i]->schedule_departure_date);
            free(hash_flight[i]->schedule_arrival_date);
            free(hash_flight[i]->real_departure_date);
            free(hash_flight[i]->real_arrival_date);
            free(hash_flight[i]->pilot);
            free(hash_flight[i]->copilot);
            free(hash_flight[i]->notes);
        }
        free(hash_flight[i]);
    }
    free(hash_flight);
}
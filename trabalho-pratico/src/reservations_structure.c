#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "reservations_structure.h"

typedef struct Reservation {
    char *reserva_id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    double hotel_stars;
    double city_tax;
    char *hotel_address;
    char *begin_date;
    char *end_date;
    double price_per_night;
    char *includes_breakfast;
    char *room_details;
    double rating;
    char *comment;
};

reservation **hash_reservation;

void allocate_reservation(){
    int i;
    hash_reservation = (reservation **)malloc(n_lines*sizeof(reservation*));
    for (i = 0; i < n_lines; i++){
        hash_reservation[i] = NULL;
    }
}

bool insert_hash_reservation(char *reserva_id, char *user_id, char *hotel_id, char *hotel_name, double hotel_stars, double city_tax, char *hotel_address, char *begin_date, char *end_date, double price_per_night, char *includes_breakfast, char *room_details, double rating,char *comment){
    reservation *r = malloc(sizeof(reservation));
    r->reserva_id = reserva_id;
    r->user_id = user_id;
    r->hotel_id = hotel_id;
    r->hotel_name = hotel_name;
    r->hotel_stars = hotel_stars;
    r->city_tax = city_tax;
    r->hotel_address = hotel_address;
    r->begin_date = begin_date;
    r->end_date = end_date;
    r->price_per_night = price_per_night;
    r->includes_breakfast = includes_breakfast;
    r->room_details = room_details;
    r->rating = rating;
    r->comment = comment;

    hash_reservation[atoi(reserva_id)-1] = r;
    return true;

}

void getReservationDetails(int* id, char**user_id, char**hotel_id, double* hotel_stars, double* city_tax, char**hotel_address, char**begin_date, char**end_date, double* price_per_night,char**include_breakfast,char**room_details,double*rating,char**comment){
    reservation* r = NULL;
    r = hash_reservation[*id];

    if (r == NULL){
        *user_id=NULL;
        return;
    }
    
    *user_id = r-> user_id;
    *hotel_id = r-> hotel_id;
    *hotel_stars = r-> hotel_stars;
    *city_tax = r-> city_tax;
    *hotel_address = r-> hotel_address;
    *begin_date = r->begin_date;
    *end_date = r->end_date;
    *price_per_night = r->price_per_night;
    *include_breakfast = r->includes_breakfast;
    *room_details = r->room_details;
    *rating = r->rating;
    *comment = r->comment;
}

void free_hash_reservation(){
    int i;
    for(i=0;i<n_lines;i++){
        if(hash_reservation[i]!=NULL){
            free(hash_reservation[i]->reserva_id);
            free(hash_reservation[i]->user_id);
            free(hash_reservation[i]->hotel_id);
            free(hash_reservation[i]->hotel_address);
            free(hash_reservation[i]->begin_date);
            free(hash_reservation[i]->end_date);
            free(hash_reservation[i]->includes_breakfast);
            free(hash_reservation[i]->room_details);
            free(hash_reservation[i]->comment);
        }
        free(hash_reservation[i]);
    }
    free(hash_reservation);
}
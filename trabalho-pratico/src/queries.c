#include "parsing.h"
#include "reservations_structure.h"     //Falta meter nos includes as funções utilizadas
#include "flights_structure.h"
#include "user.h"
#include "flight.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


void query3(char* line, char* file){
    char* user_id = NULL, *hotel_id = NULL,
    *hotel_adress = NULL, *begin_date = NULL, *end_date = NULL,
    *includes_breakfast = NULL, *room_details = NULL, *comment = NULL;

    double average_score = 0.000;
    double rating = 0.000;
    int i, counter = 0;
    double hotel_stars = 0.000;
    double price_per_night = 0.000;
    double city_tax = 0.000;

    FILE* NewFile;
    NewFile = fopen(file,"w");

    for(i = 0; i < n_lines; i++){
        getReservationDetails(&i,&user_id,&hotel_id,&hotel_stars,&city_tax,&hotel_adress,&begin_date,&end_date,&price_per_night
        ,&includes_breakfast,&room_details,&rating,&comment);
        if(user_id != NULL){
            if(strcmp(hotel_id,line) == 0){
                average_score = average_score + rating;
                counter++;
            }
        }
    }

    if(counter!=0) fprintf(NewFile,"%.3f\n", average_score/counter);
    fclose(NewFile);
}

void query5(char* line, char* file){        //Falta a função Calcular Data
    char*id = NULL, * airline = NULL, *plane_model = NULL,
    *origin = NULL, *destination = NULL, *schedule_departure_date = NULL,
    *schedule_arrival_date = NULL, *real_departure_date = NULL, *real_arrival_date = NULL,
    *pilot = NULL, *copilot = NULL, *notes = NULL; 
    int i, counter = 0;
    int n_flights = 0;
    int j = 0;
    int total_seats = 0;
    // Calculating the number of element the program needs to print.
    char*aux=malloc(sizeof(line));
    for (i=0; line[i]!=' '; i++){
        
        aux[i]=line[i];
    }
    aux[i]='\0';
    n_flights = atoi(aux);
    
    // Calculating which city was passed as an argument.
    char *nome = malloc(sizeof(strlen(line)-i));
    for (i=i+1,j=0; line[i]!='\0'; i++,j++){
        nome[j]=line[i];
    }
    nome[j]='\0';
    //Nome da Cidade
    char nome[10];
    for(i=0;line[i] != ' ';i++ ){
        nome[i] = line[i];
    }
    nome[0] = '\0';
    //Datas
    char date1[19], date2[19];
    strncpy(date1, line+i+1,18);
    date1[18] = '\0';
    strncpy(date2, line+i+20,18);
    date2[18] = '\0';
    FILE * NewFile;
    NewFile = fopen(file,'w');

    int ind = n_lines_flights-1;

    while(n_flights != 0){
        getFlightDetails(&i,&airline,&plane_model,&total_seats, &origin,&destination,&schedule_departure_date,&schedule_arrival_date,&real_departure_date,&real_arrival_date,&pilot,&copilot,&notes);
        i++;
        if(airline != NULL){
            if((strcmp(origin,line)==0) && (calculateDate(schedule_departure_date,date1)<=0) && (calculateDate(date2, schedule_departure_date)<=0)){
                fprintf(NewFile,"%s;%s;%s;%s;%s\n", id, schedule_departure_date,destination,airline,plane_model);
            }
        }
        n_flights--;
        ind--;
    }
    free_hash_flights();
    free(nome);
    fclose(NewFile);
}

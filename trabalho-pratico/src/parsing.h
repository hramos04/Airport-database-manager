#ifndef PARSING_H
#define PARSING_H

#include "user.h"
#include "reserva.h"
#include "voo.h"

int is_non_empty_string(char *string);
int valid_user(hash_user h, KeyType user_id) ;
void parse_users_csv(hash_user h, char *line);
int valid_flight(hash_voos h, KeyType flight_id);
void parse_reservations_csv(hash_user h, char *line);
void process_users_csv(hash_user h, char *ficheiro);
void process_reservas_csv(hash_user h, hash_hoteis h_hoteis,hash_reservas h_reservas, char *ficheiro);
void process_voos_csv(hash_user h, hash_aeroportos h_aeroportos, hash_voos h_voos, char *ficheiro);
void process_passengers_csv(hash_user h, hash_voos h_voos, char *ficheiro);
int valid_date(char *string);
int valid_date_hour(char *string);
int compare_birth_with_account_cr(char *string1, char *string2);
int valid_email(char *string);
int valid_country_code(char *string);
int valid_account_status(char *string);
int valid_pay_method(char *string);
int valid_aeroport(char *string);
int valid_stars(char *string);
int compare_begin_with_end(char *string1, char *string2);
int valid_phone_number(char *string);
int valid_sex(char *string);
int compare_datetime(char *datetime1, char *datetime2);
int valid_seat(char *string);
int calcularDiasDatas(char *d1, char *d2);
int valid_breakfast(char *string);
int valid_tax(char *string);
int valid_price(char *string);
int calcularDiferencaSegundos(char *datetime1, char *datetime2);
int valid_rating(char *string);

#endif  // PARSING_H

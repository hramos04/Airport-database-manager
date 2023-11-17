#ifndef PARSING_H
#define PARSING_H

#include "user.h"

int valid_date(char *string);
int valid_date_hour(char *string);
int valid_email(char *string);
int valid_country_code(char *string);
int valid_account_status(char *string);
int valid_pay_method(char *string);
int valid_seat_numbers(char *string, char *string1);
int valid_aeroport(char *string);
int valid_stars(char *string);
int valid_id(char *string);
int valid_phone_number(char *string);
int valid_breakfast(char *string);
int valid_tax(char *string);
int valid_price(char *string);
int valid_rating(char *string);
int compare_begin_with_end(char *string1, char *string2);
int is_non_empty_string(char *string);
void parse_users_csv(hash_user h, char *line);
void parse_reservations_csv(hash_user h, char *line);
void parse_passengers_csv(hash_user h, char *line);
void parse_flights_csv(hash_user h, char *line);
void process_csv_file(const char* filename, hash_user h, void (*parse_function)(hash_user, char*));

#endif  // PARSING_H

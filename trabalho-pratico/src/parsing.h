#ifndef PARSING_H
#define PARSING_H

#include "user.h"
#include "reserva.h"
#include "voo.h"

int compare_date(char *d1, char *d2);
int is_non_empty_string(char *string);
void parse_users_csv(hash_user h, char *line);
void parse_reservations_csv(hash_user h, char *line);
void process_users_csv(hash_user h, char *ficheiro);
void process_reservas_csv(hash_user h, hash_hoteis h_hoteis,hash_reservas h_reservas, char *ficheiro);
void process_voos_csv(hash_user h, hash_aeroportos h_aeroportos, hash_voos h_voos, char *ficheiro);
void process_passengers_csv(hash_user h, hash_voos h_voos, char *ficheiro);
#endif  // PARSING_H

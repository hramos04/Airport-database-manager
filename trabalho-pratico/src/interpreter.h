#ifndef INTERPRETER_H
#define INTERPRETER_H
#define CURRENT_YEAR 2023
#define CURRENT_MONTH 10
#define CURRENT_DAY 1
#define MAX_ARGS 5
#define MAX_LINE_LENGTH 1024
#include <ctype.h>
#include "user.h"
#include "voo.h"
#include "reserva.h"
#include <stdio.h>


int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis,hash_aeroportos h_aeroportos, FILE *fp_output);
void remove_quotes(char *str);
void split(char *line, int *arg_count, char *args[MAX_ARGS]);
int calculaIdade(char *birthDate);
void remover_horas(char* datetime, char data[]);
void q1(hash_user h_users,hash_voos h_voos,hash_reservas h_reservas, char *arg, int f, FILE *fp_output);
void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output);
void q3(hash_hoteis h_hoteis, char *argv,  int f,FILE *fp_output);
void q4(hash_hoteis h_hoteis, char *argv, int f, FILE *fp_output);
void q9(hash_user h_users, char *argv, int f, FILE *fp_output);
void q5(hash_aeroportos h_aeroportos, char *origin, char *begin_date, char *end_date, int f, FILE *fp_output);


#endif

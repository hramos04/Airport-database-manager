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
#include "aeroporto.h"
#include "hotel.h"

/*Função principal usada para executar as queries/comandos*/
int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis,hash_aeroportos h_aeroportos, FILE *fp_output);

/*Remove as aspas de uma string*/
void remove_quotes(char *str);


/*Divide uma linha em argumentos */
void split(char *line, int *arg_count, char *args[MAX_ARGS]);


/*Calcula a idade com base na data de nascimento */
int calculaIdade(char *birthDate);


/*Remove as horas de uma data */
void remover_horas(char* datetime, char data[]);


/* Implementação da Query 1*/
void q1(hash_user h_users,hash_voos h_voos,hash_reservas h_reservas, char *arg, int f, FILE *fp_output);

/*Implementação da Query 2*/
void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output);

/* Implementação da Query 3*/
void q3(hash_hoteis h_hoteis, char *argv,  int f,FILE *fp_output);

/*Implementação da Query 4*/
void q4(hash_hoteis h_hoteis, char *argv, int f, FILE *fp_output);


/*Implementação da Query 6*/
void q6(hash_voos h_voos, char *ano_str, char *N_str, int f, FILE *fp_output);

/* Implementação da Query 9*/
void q9(hash_user h_users, char *argv, int f, FILE *fp_output);


/*Implementação da query 7*/
void q7(hash_aeroportos h_aeroportos, int N, int f, FILE *fp_output);

/*Implementação da Query 5*/
void q5(hash_aeroportos h_aeroportos, char *origin, char *begin_date, char *end_date, int f, FILE *fp_output);

/*Função principal para ser usada no modo interativo*/
int comando_interativo(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos);


#endif

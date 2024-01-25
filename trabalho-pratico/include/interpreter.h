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

/*
 * Função: remove_quotes
 * ---------------------
 * Remove as aspas de uma string, se presentes.
 *
 * str: A string da qual remover as aspas.
 */
void remove_quotes(char *str);


/*
 * Função: split
 * -------------
 * Divide uma linha em argumentos.
 *
 * line: A linha a ser dividida.
 * arg_count: Ponteiro para a variável que armazenará a quantidade de argumentos.
 * args: Array que armazenará os argumentos resultantes da divisão.
 */
void split(char *line, int *arg_count, char *args[MAX_ARGS]);


/*
 * Função: comando
 * ---------------
 * Analisa e executa um comando fornecido.
 *
 * linha: O comando a ser analisado e executado.
 * h_users: Tabela hash de usuários.
 * h_voos: Tabela hash de voos.
 * h_reservas: Tabela hash de reservas.
 * h_hoteis: Tabela hash de hotéis.
 * h_aeroportos: Tabela hash de aeroportos.
 * fp_output: Ponteiro para o ficheiro de saída.
 * Retorna: 1 se o comando for executado com sucesso, 0 caso contrário.
 */
int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos, FILE *fp_output, int tempo);


/*
 * Função: comando_interativo
 * --------------------------
 * Analisa e executa um comando fornecido no modo interativo.
 *
 * linha: O comando a ser analisado e executado.
 * h_users: Tabela hash de usuários.
 * h_voos: Tabela hash de voos.
 * h_reservas: Tabela hash de reservas.
 * h_hoteis: Tabela hash de hotéis.
 * h_aeroportos: Tabela hash de aeroportos.
 * Retorna: 1 se o comando for executado com sucesso, 0 caso contrário.
 */
int comando_interativo(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos);


#endif


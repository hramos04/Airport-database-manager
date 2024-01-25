#ifndef QUERIES_H
#define QUERIES_H
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
 * Função: calculaIdade
 * ---------------------
 * Calcula a idade com base na data de nascimento.
 *
 * birthDate: A data de nascimento no formato "YYYY/MM/DD".
 * Retorna: A idade calculada.
 */
int calculaIdade(char *birthDate);


/*
 * Função: comparaOutputs
 * ---------------------
 * Compara o resultado da query na pasta Resultados com o 
 * resultado na pasta outputs.
 *
 * expectavel: O resultado da query na pasta outputs.
 * real: O resultado da query na pasta Resultados .
 */
int comparaOutputs(FILE *expectavel, FILE *real);


/*
 * Função: remover_horas
 * ---------------------
 * Remove as horas de uma data e hora no formato "YYYY/MM/DD HH:mm:ss".
 *
 * datetime: A data e hora original.
 * data: Array que armazenará a data resultante.
 */
void remover_horas(char* datetime, char data[]);


/*
 * Função: q1
 * ----------
 * Executa a Query 1, que recupera informações de utilizadores, voos ou reservas com base no argumento fornecido.
 *
 * h_users: Tabela hash de utilizadores.
 * h_voos: Tabela hash de voos.
 * h_reservas: Tabela hash de reservas.
 * arg: O argumento fornecido na Query 1.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q1(hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, char *arg, int f, FILE *fp_output);


/*
 * Função: q2
 * ----------
 * Executa a Query 2, que recupera informações da lista ligada Q2 de um utilizador.
 *
 * h_users: Tabela hash de usuários.
 * argv: Array contendo os argumentos fornecidos na Query 2.
 * argc: Número de argumentos fornecidos na Query 2.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output);


/*
 * Função: q3
 * ----------
 * Executa a Query 3, que recupera a classificação de um hotel.
 *
 * h_hoteis: Tabela hash de hotéis.
 * argv: O argumento fornecido na Query 3.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q3(hash_hoteis h_hoteis, char *argv,  int f,FILE *fp_output);


/*
 * Função: q4
 * ----------
 * Executa a Query 4, que recupera informações resumidas de reservas de um hotel.
 *
 * h_hoteis: Tabela hash de hotéis.
 * argv: O argumento fornecido na Query 4.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q4(hash_hoteis h_hoteis, char *argv, int f, FILE *fp_output);


/*
 * Função: q5
 * ----------
 * Executa a Query 5, que recupera informações resumidas de voos entre datas específicas.
 *
 * h_aeroportos: Tabela hash de aeroportos.
 * origin: O aeroporto de origem.
 * begin_date: Data de início no formato "YYYY/MM/DD".
 * end_date: Data de término no formato "YYYY/MM/DD".
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q5(hash_aeroportos h_aeroportos, char *origin, char *begin_date, char *end_date, int f, FILE *fp_output);


/*
 * Função: q6
 * ----------
 * Executa a Query 6, que gera estatísticas de passageiros por aeroporto num determinado ano.
 *
 * h_voos: Tabela hash de voos.
 * ano_str: Ano fornecido como argumento.
 * N_str: Valor N fornecido como argumento.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q6(hash_voos h_voos, char *ano_str, char *N_str, int f, FILE *fp_output);


/*
 * Função: q7
 * ----------
 * Executa a Query 7, que lista os top N aeroportos com maior mediana de atrasos.
 *
 * h_aeroportos: Tabela hash de aeroportos.
 * N: Valor N fornecido como argumento.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q7(hash_aeroportos h_aeroportos, int N, int f, FILE *fp_output);


/*
 * Função: q8
 * ----------
 * Executa a Query 8, que calcula o lucro total de hotéis num intervalo de datas.
 *
 * h_hoteis: Tabela hash de hotéis.
 * argv: O argumento fornecido na Query 8.
 * start_date: Data de início fornecida como argumento.
 * end_date: Data de término fornecida como argumento.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q8(hash_hoteis h_hoteis,char *argv, char *start_date, char *end_date, int f, FILE *fp_output);


/*
 * Função: q9
 * ----------
 * Executa a Query 9, que lista todos os utilizadores com base num prefixo.
 *
 * h_users: Tabela hash de usuários.
 * argv: O argumento fornecido na Query 9.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q9(hash_user h_users, char *argv, int f, FILE *fp_output);


/*
 * Função: q10
 * -----------
 * Executa a Query 10, que realiza análises dos utilizadores, dos voos e das reservas com base em argumentos fornecidos.
 *
 * h_users: Tabela hash de usuários.
 * h_voos: Tabela hash de voos.
 * h_reservas: Tabela hash de reservas.
 * argv: Array de strings contendo argumentos fornecidos na Query 10.
 * argc: Número de argumentos fornecidos.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q10(hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, char **argv, int argc, int f, FILE *fp_output);


#endif

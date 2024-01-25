#ifndef INTERATIVO
#define INTERATIVO
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Função: main_interativo
 * -----------------------
 * Função principal do modo interativo. Inicializa as tabelas hash e processa os arquivos CSV fornecidos.
 *
 * file: Caminho da pasta contendo os arquivos CSV.
 * h_users: Tabela hash de usuários.
 * h_aeroportos: Tabela hash de aeroportos.
 * h_hoteis: Tabela hash de hotéis.
 * h_reservas: Tabela hash de reservas.
 * h_voos: Tabela hash de voos.
 * Retorna 0 em caso de sucesso e 1 em caso de falha.
 */
int main_interativo(char* file, hash_user h_users,hash_aeroportos h_aeroportos,hash_hoteis h_hoteis,hash_reservas h_reservas,hash_voos h_voos);


/*
 * Função: display_page
 * ---------------------
 * Exibe uma página específica do arquivo no modo interativo.
 *
 * file: Ponteiro para o arquivo.
 * start: Linha de início da página.
 * end: Linha de término da página.
 * n_linhas: Número total de linhas no arquivo.
 * isLarge: Indica se o conteúdo da página é grande.
 */
void display_page (FILE *file, int start, int end, int n_linhas, int isLarge);


/*
 * Função: move_pages
 * -------------------
 * Permite a navegação entre páginas do arquivo no modo interativo.
 *
 * file: Ponteiro para o arquivo.
 * win: Janela do modo interativo.
 * n_linhas: Número total de linhas no arquivo.
 * sum: Valor para ajuste no cálculo do número de páginas.
 */
void move_pages(FILE *file, WINDOW* win, int n_linhas, int sum);


/*
 * Função: programa_interativo
 * ---------------------------
 * Realiza as operações principais do modo interativo, como execução de queries e navegação entre opções.
 *
 * highlight: Índice da opção destacada.
 * win: Janela do modo interativo.
 * query: Contador de execuções de queries.
 * Retorna 0 em caso de sucesso e 1 em caso de falha.
 */
int programa_interativo (int highlight, WINDOW* win, int query);


/*
 * Função: interativo
 * -------------------
 * Função principal do modo interativo, inicializa a interface e permite a navegação entre opções.
 */
void interativo (void);

#endif

#ifndef INTERATIVO
#define INTERATIVO
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>





int main_interativo(char* file, hash_user h_users,hash_aeroportos h_aeroportos,hash_hoteis h_hoteis,hash_reservas h_reservas,hash_voos h_voos);
void display_page (FILE *file, int start, int end, int n_linhas, int isLarge);
void move_pages(FILE *file, WINDOW* win, int n_linhas, int sum);
int programa_interativo (int highlight, WINDOW* win, int query);
void interativo (void);

#endif

#include "../include/reserva.h"
#include "../include/user.h"
#include "../include/voo.h"
#include "../include/parsing.h"
#include "../include/curses.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>


int main_interativo(char* file){

	/*Inicialização das tabelas hash*/
    hash_user h_users;
    hash_hoteis h_hoteis;
    hash_reservas h_reservas;
    hash_voos h_voos;
    hash_aeroportos h_aeroportos;
    
    InitializeTable(h_users);
    InitializeTableHoteis(h_hoteis);
    InitializeTableReservas(h_reservas);
    InitializeTableVoos(h_voos);
    InitializeTableAeroportos(h_aeroportos);
    
    /*Leitura e parsing do ficheiro "users.csv"*/
	char *csv_users = (char*)malloc(256);
	strcpy(csv_users, file);
	strcat(csv_users, "/users.csv");
	
	char *csv_reservas = (char*)malloc(256);
	strcpy(csv_reservas, file);
	strcat(csv_reservas, "/reservations.csv");
	
	char *csv_voos = (char*)malloc(256);
	strcpy(csv_voos, file);
	strcat(csv_voos, "/flights.csv");
	
	char *csv_passengers = (char*)malloc(256);
	strcpy(csv_passengers, file);
	strcat(csv_passengers, "/passengers.csv");

	/*Processamento dos arquivos*/
    process_users_csv(h_users, csv_users);
    process_reservas_csv(h_users, h_hoteis, h_reservas, csv_reservas);
    process_voos_csv(h_users, h_aeroportos, h_voos, csv_voos);
    process_passengers_csv(h_users, h_voos, csv_passengers);


    //Input inválido, não sei se é preciso!
    //if(count_lines(csv_users,csv_reservas,csv_voos,csv_passengers)){
    //    printw("INVALID PATH FILE!\n");
    //    refresh();
    //    napms(1000);
    //    move(10,0);
    //    clrtoeol();
    //    refresh();
    //    return 1;

    free(csv_users);
    free(csv_reservas);
    free(csv_voos);
    free(csv_passengers);

    return 0;
}

void display_page (FILE *file, int start, int end, int n_linhas, int isLarge){
    rewind(file);
    int i; 
    char buffer[250];

    if (isLarge == 0){
        for(i = 10; i < 25; i++){
            move(i,0);
            clrtoeol();
        }
    }
    i=0;

    while(fgets(buffer,250,file)!= NULL){
        if(n_linhas == 1){
            move(10,0);
            printw("%s",buffer);
            break;
        }
        if(i>=start && i<end){
            move(i % 15 + 10, 0);
            printw("%d - %s",i + 1, buffer);
        }
        i++;
    }
    refresh();
}

void move_pages(FILE *file, WINDOW* win, int n_linhas, int sum){
    int isLarge = 0;
    move(9,0);
    printw("OUTPUTS:");

    if(n_linhas > 15){
        move(30,14);
        printw("MENU (Q)");
        isLarge = 1;
    }
    else{
        move(n_linhas+11,0);
        printw("MENU (Q)");
        isLarge = 1;
    }

    refresh();
    rewind(file);
    int start = 0;
    int end = 15;
    int botao;
    int flag = 0;
    int pag = 1;
    move(10,0);

    while(1){
        if(n_linhas>15){
            move(26,5);
            clrtoeol();
            printw("(<-) ANTERIOR [%d/%d] SEGUINTE (->)", pag, n_linhas/15+sum);
            move(28,7);
            printw("(P) PRIMEIRA | ÚLTIMA (U)");
            refresh();
        }

        if(flag == 0) display_page(file,start,end,n_linhas,isLarge);

        flag = 0;
        botao = wgetch(win);

        switch (botao)
        {
        case KEY_RIGHT:
            start += 15;
            end += 15;
            if(end-15>=n_linhas){
                start -= 0;
                end -= 15;
                flag = 1;
            }
            else pag++;
            break;

        case KEY_LEFT:
            start -= 15;
            end -= 15;
            if(start < 0){
                start = 0;
                end = 15;
            }
            else pag--;
            break;
        
        case 'f':
            if(n_linhas>15){
                start = 0;
                end = 15;
                pag = 1;
            }
            break;

        case 'l':
            if(n_linhas>15){
                while(end<n_linhas){
                    start += 15;
                    end += 15;
                }
                pag = n_linhas/15+sum;
            }
            break;
        
        case 'q':
            for(int i = 0; i < 30; i++){
                move(i+9, 0);
                clrtoeol();
            }
            refresh();
            move(10,0);
            return;
        }
    }

}


    
    


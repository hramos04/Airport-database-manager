#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/reserva.h"
#include "../include/user.h"
#include "../include/voo.h"
#include "../include/parsing.h"
#include "../include/interpreter.h"
#include "../include/interativo.h"
#include <curses.h>


int main_interativo(char* file){

	//Inicialização das tabelas hash
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
    
    //Leitura e parsing do ficheiro "users.csv"
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

	//Processamento dos arquivos
    process_users_csv(h_users, csv_users);
    process_reservas_csv(h_users, h_hoteis, h_reservas, csv_reservas);
    process_voos_csv(h_users, h_aeroportos, h_voos, csv_voos);
    process_passengers_csv(h_users, h_voos, h_aeroportos, csv_passengers);

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

int programa_interativo (int highlight, WINDOW* win, int query){
    int i;
    hash_user h_users; 
    hash_voos h_voos;
    hash_reservas h_reservas; 
    hash_hoteis h_hoteis; 
    hash_aeroportos h_aeroportos;

    if(highlight == 2){
        endwin();
        //dar free a tudo
        //freehashaeroportos ...
        exit(0);
    }

    if (highlight == 1){

        if (query == 0){
            printw("TEM DE SER INSERIDOS OS DADOS PRIMEIRO");
            refresh();
            napms(1000);
            move(10,0);
            clrtoeol();
            refresh();
            return 0;
        }

        move(10,0);
        printw(">> INSERIR A QUERY: "); 
        char* input_q = malloc(250);
        int ch_q;
        int n_linhas=0;
        char buffer[250];
        echo();
        curs_set(1);
        for(i = 0; i < 250 - 1 && (ch_q = getch()) != '\n'; i++ )
        input_q[i] = ch_q;
        input_q[i] = '\0';
        curs_set(0);
        noecho();
        move(10,0);
        clrtoeol();
        refresh();

        if(comando_interativo (input_q, h_users, h_voos,h_reservas,h_hoteis,h_aeroportos) == 0){

            if(chdir("Resultados/") != 0);
            FILE* ficheiro;
            ficheiro = fopen("file", "r");

            if(fgetc(ficheiro) == EOF){
                printw(">> NÃO HÁ OUTPUTS PARA ESTA QUERY");
                remove("file");
                move(12,6);
                printw("MENU (Q)");
                refresh();
                
                while(wgetch(win) != 'q');
                for(int i = 9; i < 30; i++){
                    move(i,0);
                    clrtoeol();
                }
                move(10,0);
                refresh();
                return 0;
            }

            rewind(ficheiro);

            while(fgets(buffer,250,ficheiro)!= NULL){
                n_linhas++;
            }

            if(n_linhas % 15 != 0) move_pages(ficheiro, win, n_linhas, 1);
            else move_pages(ficheiro, win, n_linhas, 0);

            remove("file");
            if(chdir("trabalho-pratico") != 0);
        }

    else{
        printw(">> QUERY INVALIDA");
        refresh();
        napms(1000);
        move(10,0);
        clrtoeol();
        refresh();
    }
    }

    if(highlight == 0){
        printw(">> INSERIR O CAMINHO PARA A PASTA ONDE ESTAO OS CSV: ");
        mvwprintw(win, 2, 23, "          ");
        wrefresh(win);
        char* input = malloc(250);
        int ch;
        echo();
        curs_set(1);
        for(i = 0; i < 250 - 1 && (ch = getch()) != '\n'; i++ )
        input[i] = ch;
        input[i] = '\0';
        noecho();
        curs_set(0);
        mvwprintw(win, 2, 23, "[...]");
        clrtoeol();
        refresh();

        if(main_interativo(input) == 1){
            mvwprintw(win, 2, 30, "          ");
            wrefresh(win);
            return 1;
        }
        else{
            mvwprintw(win, 2, 35, "[CARREGADO]");
            wrefresh(win);
        }
    }
    return 0;
}

void interativo (void){
    initscr();
    noecho();
    int height = 7;
    int width = 100;
    int start_y = 2;

    WINDOW* win = newwin(height, width, start_y, 0);
    box(win, 0, 0);
    refresh();
    move(10,0);
    wrefresh(win);
    keypad(win, true);
    mvwprintw(win, 0, 5, "GRUPO-25");
    curs_set(0);
    raw();

    const char* choices[] = {"INSERIR CAMINHO PARA A PASTA", "INSERIR QUERY", "SAIR"};
    int choice;
    int highlight = 0;
    int i;
    int query = 0;

    while (1){
        for(i = 0; i < 3; i++){
            if(i == highlight) wattron(win, A_REVERSE);
            mvwprintw(win, i+2, 2, choices[i]);
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if(highlight == -1) highlight = 2;
            break;
        
        case KEY_DOWN:
            highlight++;
            if(highlight == 3) highlight = 0;
            break;
        
        default:
            break;
        }

        if(choice == 10){
            if(highlight == 0) query++;
            if(programa_interativo(highlight,win,query) == 1) query--;
        }

    }

}
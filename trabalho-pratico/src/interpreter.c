#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"
#include "voo.h"
#include "reserva.h"

#define CURRENT_YEAR 2023
#define CURRENT_MONTH 10
#define CURRENT_DAY 1

char **split(const char *linha, int *total) {
	char **arr = (char**)malloc(10 * sizeof(char *));
	char *copy = strdup(linha);
	char *token = strtok(copy, " ");
	int count = 0;
	while (token != NULL && count < 10) {
		arr[count]  =strdup(token);
		token = strtok(NULL, " ");
		count++;
	}
	free(copy);
	*total = count;
	return arr;
	
}

int calculaIdade(char *birthDate) {
	int a_aux, m_aux, d_aux;
	sscanf(birthDate, "%d/%d/%d", &a_aux, &m_aux, &d_aux);
	int idade = CURRENT_YEAR - a_aux;
	if(CURRENT_MONTH < m_aux || (CURRENT_MONTH == m_aux && CURRENT_DAY < d_aux)) {
		idade--;
	}
	return idade;
}

void remover_horas(char* datetime, char data[]) {
	int i=0;
	for(i=0; datetime[i] != ' ' && datetime[i] != '\0'; i++) {
		data[i] = datetime[i];
	}
	data[i] = '\0';
}

void q1(hash_user h_users,hash_voos h_voos,hash_reservas h_reservas, char *arg, FILE *fp_output) {
	User *user = RetrieveUser(h_users, arg);
	Voo *voo = RetrieveVoo(h_voos, arg);
	Reserva *reserva = RetrieveReserva(h_reservas, arg);
	if(user ){
		if((strcasecmp(user->account_status, "active") == 0 )) {
			fprintf(fp_output, "%s;%s;%d;%s;%s;%d;%d;%.3f",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
			//printf("%s;%s;%d;%s;%s;%d;%d;%.3f\n",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
		}
	}
	else if(voo) {
		fprintf(fp_output,"%s;%s;%s;%s;%s;%s;%d;%d",voo->airline, voo->plane_model,voo->origin,voo->destination, voo->schedule_departure_date, voo->schedule_arrival_date, voo->total_passengers, voo->delay);
	}
	else if(reserva) {
		reserva->includes_breakfast[0] = toupper(reserva->includes_breakfast[0]);
		fprintf(fp_output, "%s;%s;%s;%s;%s;%s;%d;%.3f",reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, reserva->includes_breakfast, reserva->total_noites, reserva->total_gasto);
	}
}



void q2(hash_user h_users, char **argv, int argc, FILE *fp_output) {
	char data[50];
	User *user = RetrieveUser(h_users, argv[1]);
	if(user && (strcasecmp(user->account_status, "active") == 0 )) {
		Q2 *q2 = user->q2;
		while(q2) {
			remover_horas(q2->data, data);
			if(argc == 3) {
				if(strcmp(argv[2], "reservations") == 0) {
					if(q2->tipo == 1) {
						
						fprintf(fp_output, "%s;%s\n",q2->id,data);
					}
				}
				else if(strcmp(argv[2], "flights") == 0) {
					if(q2->tipo == 2) {
						fprintf(fp_output,"%s;%s\n",q2->id,data);
					}
				}
			}
			else {
				if(q2->tipo == 1) {
					fprintf(fp_output,"%s;%s;reservation\n",q2->id,data);
				}
				else {
					fprintf(fp_output,"%s;%s;flight\n",q2->id,data);
				}
			}
			q2 = q2->next;
		}
	}
}


void q3(hash_hoteis h_hoteis, char *argv, FILE *fp_output) {
	
	double rating = GetRatingByHotel(h_hoteis, argv);
	if(rating > 0) {
		fprintf(fp_output, "%.3f\n",rating);
	}
}


void q4(hash_hoteis h_hoteis, char *argv, FILE *fp_output) {
	
	Hotel *aux = RetrieveHotel(h_hoteis, argv);
	if(aux) {
		ReservaResumo *reserva = aux->next_resumo;
		while(reserva)  {
			fprintf(fp_output, "%s;%s;%s;%s;%.0f\n",reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating);
			reserva = reserva->next_resumo;
		}
		
	}
	
}

int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, FILE *fp_output) {
	int argc = 0;
	char **args = split(linha, &argc);
	
	
	if(strcmp(args[0], "1") == 0) {
		q1(h_users, h_voos, h_reservas, args[1], fp_output);
	}
	else if(strcmp(args[0], "2") == 0) {
		q2(h_users, args, argc, fp_output);
	}
	else if(strcmp(args[0], "3") == 0) {
		q3(h_hoteis, args[1], fp_output);
	}
	else if(strcmp(args[0], "4") == 0) {
		q4(h_hoteis, args[1], fp_output);
	}
	
	
	return 1;
}



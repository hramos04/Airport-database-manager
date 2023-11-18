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

void q1(hash_user h_users,hash_voos h_voos,hash_reservas h_reservas, char *arg, int f, FILE *fp_output) {
	User *user = RetrieveUser(h_users, arg);
	Voo *voo = RetrieveVoo(h_voos, arg);
	Reserva *reserva = RetrieveReserva(h_reservas, arg);
	if(user ){
		if((strcasecmp(user->account_status, "active") == 0 )) {
			if(f == 1) {
				fprintf(fp_output, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
			}
			else {
				fprintf(fp_output, "%s;%s;%d;%s;%s;%d;%d;%.3f",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
			}
		}
	}
	else if(voo) {
		if(f == 1) {
			fprintf(fp_output,"--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d",voo->airline, voo->plane_model,voo->origin,voo->destination, voo->schedule_departure_date, voo->schedule_arrival_date, voo->total_passengers, voo->delay);
		}
		else {
			fprintf(fp_output,"%s;%s;%s;%s;%s;%s;%d;%d",voo->airline, voo->plane_model,voo->origin,voo->destination, voo->schedule_departure_date, voo->schedule_arrival_date, voo->total_passengers, voo->delay);
		}
		
	}
	else if(reserva) {
		reserva->includes_breakfast[0] = toupper(reserva->includes_breakfast[0]);
		if(f == 1) {
			fprintf(fp_output, " --- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %s\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f",reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, reserva->includes_breakfast, reserva->total_noites, reserva->total_gasto);
		}
		else {
			fprintf(fp_output, "%s;%s;%s;%s;%s;%s;%d;%.3f",reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, reserva->includes_breakfast, reserva->total_noites, reserva->total_gasto);
		}
		
	}
}



void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output) {
	char data[50];
	User *user = RetrieveUser(h_users, argv[1]);
	int i = 1;
	if(user && (strcasecmp(user->account_status, "active") == 0 )) {
		Q2 *q2 = user->q2;
		while(q2) {
			remover_horas(q2->data, data);
			if(argc == 3) {
				if(strcmp(argv[2], "reservations") == 0) {
					if(q2->tipo == 1) {
						if(f == 1) {
							if(i == 1) {
								fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n",i,q2->id,data);
							}
							else {
								fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n",i,q2->id,data);
							}
						}
						else {
							fprintf(fp_output, "%s;%s\n",q2->id,data);
						}
						i++;
						
					}
				}
				else if(strcmp(argv[2], "flights") == 0) {
					if(q2->tipo == 2) {
						if(f == 1) {
							if(i == 1) {
								fprintf(fp_output, "--- %d ---\nidd: %s\ndate: %s\n",i,q2->id,data);
							}
							else {
								fprintf(fp_output, "\n--- %d ---\nidd: %s\ndate: %s\n",i,q2->id,data);
							}
							
						}
						else {
							fprintf(fp_output,"%s;%s\n",q2->id,data);
						}
						i++;
					}
				}
			}
			else {
				if(q2->tipo == 1) {
					if(f == 1) {
						if(i == 1) {
							fprintf(fp_output,"--- %d ---\nid: %s\ndate: %s\ntype: reservation\n",i, q2->id,data);
						}
						else {
							fprintf(fp_output,"\n--- %d ---\nid: %s\ndate: %s\ntype: reservation\n",i, q2->id,data);
						}
						
					}
					else {
						fprintf(fp_output,"%s;%s;reservation\n",q2->id,data);
					}
					
				}
				else {
					if(f == 1) {
						if(i == 1) {
							fprintf(fp_output,"--- %d ---\nid: %s\ndate: %s\ntype: flight\n",i, q2->id,data);
						}
						else {
							fprintf(fp_output,"\n--- %d ---\nid: %s\ndate: %s\ntype: flight\n",i, q2->id,data);
						}
						
					}
					else {
						fprintf(fp_output,"%s;%s;flight\n",q2->id,data);
					}
				}
				i++;
			}
			
			q2 = q2->next;
		}
	}
}


void q3(hash_hoteis h_hoteis, char *argv,  int f,FILE *fp_output) {
	
	double rating = GetRatingByHotel(h_hoteis, argv);
	if(rating > 0) {
		if(f == 1) {
			fprintf(fp_output, "--- 1 ---\nrating: %.3f\n",rating);
		}
		else {
			fprintf(fp_output, "%.3f\n",rating);
		}
		
	}
}


void q4(hash_hoteis h_hoteis, char *argv, int f, FILE *fp_output) {
	int i = 1;
	Hotel *aux = RetrieveHotel(h_hoteis, argv);
	if(aux) {
		ReservaResumo *reserva = aux->next_resumo;
		while(reserva)  {
			if(f == 1) {
				if(i == 1) {
					fprintf(fp_output, "--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %.0f\ntotal_price: %.3f\n",i, reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating, reserva->total_price);
				}
				else {
					fprintf(fp_output, "\n--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %.0f\ntotal_price: %.3f\n",i, reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating, reserva->total_price);
				}
			}
			else {
				fprintf(fp_output, "%s;%s;%s;%s;%.0f;%.3f\n",reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating, reserva->total_price);
			}
			i++;
			reserva = reserva->next_resumo;
		}
	}
	
}

int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, FILE *fp_output) {
	int argc = 0;
	char **args = split(linha, &argc);
	int f = 0;
	if(linha[1] == 'F') {
		f = 1;
	}
	
	if(strcmp(args[0], "1") == 0 || strcmp(args[0], "1F") == 0) {
		q1(h_users, h_voos, h_reservas, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "2") == 0 || strcmp(args[0], "2F") == 0) {
		q2(h_users, args, argc, f, fp_output);
	}
	else if(strcmp(args[0], "3") == 0 || strcmp(args[0], "3F") == 0) {
		q3(h_hoteis, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "4") == 0 || strcmp(args[0], "4F") == 0) {
		q4(h_hoteis, args[1], f, fp_output);
	}
	
	
	return 1;
}



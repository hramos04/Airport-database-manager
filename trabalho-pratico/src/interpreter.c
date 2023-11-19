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
#define MAX_ARGS 5
#define MAX_LINE_LENGTH 1024

void remove_quotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        str[len - 1] = '\0';
    }
}

void split(char *line, int *arg_count, char *args[MAX_ARGS]) {
    *arg_count = 0;
    char buffer[MAX_LINE_LENGTH];
    int in_quotes = 0;
    size_t buffer_index = 0;

    for (size_t i = 0; i < strlen(line) && *arg_count < MAX_ARGS; i++) {
        char current_char = line[i];

        if (current_char == ' ' && !in_quotes) {
            // Final de um argumento
            buffer[buffer_index] = '\0';
            args[(*arg_count)++] = strdup(buffer);
            buffer_index = 0;
        } else if (current_char == '\"') {
            // Início ou final das aspas
            in_quotes = 1 - in_quotes;
        } else {
            // Caracter normal, adiciona ao buffer
            buffer[buffer_index++] = current_char;
        }
    }

    // Adicionar o último argumento
    if (buffer_index > 0 && *arg_count < MAX_ARGS) {
        buffer[buffer_index] = '\0';
        args[(*arg_count)++] = strdup(buffer);
    }

    // Remover aspas dos argumentos
    for (int i = 0; i < *arg_count; i++) {
        remove_quotes(args[i]);
    }
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
	if(user) {
		if((strcasecmp(user->account_status, "active") == 0 )) {
			if(f == 1) {
				fprintf(fp_output, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
			}
			else {
				fprintf(fp_output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n",user->nome,user->sex, calculaIdade(user->birth), user->country,user->passport,user->total_voos, user->total_reservas, user->total_gasto);
			}
		}
	}
	else if(voo) {
		if(f == 1) {
			fprintf(fp_output,"--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n",voo->airline, voo->plane_model,voo->origin,voo->destination, voo->schedule_departure_date, voo->schedule_arrival_date, voo->total_passengers, voo->delay);
		}
		else {
			fprintf(fp_output,"%s;%s;%s;%s;%s;%s;%d;%d\n",voo->airline, voo->plane_model,voo->origin,voo->destination, voo->schedule_departure_date, voo->schedule_arrival_date, voo->total_passengers, voo->delay);
		}
		
	}
	else if(reserva) {
		reserva->includes_breakfast[0] = toupper(reserva->includes_breakfast[0]);
		if(f == 1) {
			fprintf(fp_output, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %s\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, reserva->includes_breakfast, reserva->total_noites, reserva->total_gasto);
		}
		else {
			fprintf(fp_output, "%s;%s;%s;%s;%s;%s;%d;%.3f\n",reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, reserva->includes_breakfast, reserva->total_noites, reserva->total_gasto);
		}
		
	}
}

void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output) {
	char data[100];
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
								fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n",i,q2->id,data);
							}
							else {
								fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n",i,q2->id,data);
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

void q9(hash_user h_users, char *argv, int f, FILE *fp_output) {
	User *aux = GetUserPrefix(h_users, argv);
	int i = 1;
	if(aux) {
		while(aux) {
			if(f == 1) {
				if(i == 1) {
					fprintf(fp_output, "--- %d ---\nid: %s\nname: %s\n",i, aux->id, aux->nome);
				}
				else {
					fprintf(fp_output, "\n--- %d ---\nid: %s\nname: %s\n",i, aux->id, aux->nome);
				}
				i++;
			}
			else {
				fprintf(fp_output, "%s;%s\n",aux->id, aux->nome);
			}
			
			//fprintf(fp_output, "%s;%s;%s;%s;%.0f;%.3f\n",reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating, reserva->total_price);
			aux = aux->next;
		}
	}
	
}


void q5(hash_aeroportos h_aeroportos, char *origin, char *begin_date, char *end_date, int f, FILE *fp_output) {
	VooResumo *aux = GetVoosAeroportoEntreDatas(h_aeroportos, origin, begin_date, end_date);
	int i = 1;
	if(aux) {
		while(aux) {
			if(f == 1) {
				if(i == 1) {
					fprintf(fp_output, "--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",i, aux->id, aux->schedule_departure_date,aux->destination, aux->airline, aux->plane_model);
				}
				else {
					fprintf(fp_output, "\n--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",i, aux->id, aux->schedule_departure_date,aux->destination, aux->airline, aux->plane_model);
				}
				i++;
			}
			else {
				fprintf(fp_output, "%s;%s;%s;%s;%s\n",aux->id, aux->schedule_departure_date,aux->destination, aux->airline, aux->plane_model);
			}
			
			//fprintf(fp_output, "%s;%s;%s;%s;%.0f;%.3f\n",reserva->id, reserva->begin_date, reserva->end_date,reserva->user_id, reserva->rating, reserva->total_price);
			aux = aux->next_resumo;
		}
	}
}
	
int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos, FILE *fp_output) {
	int argc = 0;
	char *args[MAX_ARGS];
	split(linha, &argc, args);
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
	else if(strcmp(args[0], "5") == 0 || strcmp(args[0], "5F") == 0) {
		q5(h_aeroportos, args[1], args[2], args[3], f, fp_output);
	}
	else if(strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) {
		q9(h_users, args[1], f, fp_output);
	}
	
	
	return 1;
}



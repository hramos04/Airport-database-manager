#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../include/user.h"
#include "../include/reserva.h"
#include "../include/voo.h"
#include "../include/interpreter.h"
#include "../include/aeroporto.h"
#include "../include/hotel.h"



//Definição das constantes
#define CURRENT_YEAR 2023
#define CURRENT_MONTH 10
#define CURRENT_DAY 1
#define MAX_ARGS 5
#define MAX_LINE_LENGTH 1024


/*
 * Função: remove_quotes
 * ---------------------
 * Remove as aspas de uma string, se presentes.
 *
 * str: A string da qual remover as aspas.
 */
void remove_quotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        str[len - 1] = '\0';
    }
}

/*
 * Função: split
 * -------------
 * Divide uma linha em argumentos.
 *
 * line: A linha a ser dividida.
 * arg_count: Ponteiro para a variável que armazenará a quantidade de argumentos.
 * args: Array que armazenará os argumentos resultantes da divisão.
 */
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


/*
 * Função: calculaIdade
 * ---------------------
 * Calcula a idade com base na data de nascimento.
 *
 * birthDate: A data de nascimento no formato "YYYY/MM/DD".
 * Retorna: A idade calculada.
 */
int calculaIdade(char *birthDate) {
	int a_aux, m_aux, d_aux;
	sscanf(birthDate, "%d/%d/%d", &a_aux, &m_aux, &d_aux);
	int idade = CURRENT_YEAR - a_aux;
	if(CURRENT_MONTH < m_aux || (CURRENT_MONTH == m_aux && CURRENT_DAY < d_aux)) {
		idade--;
	}
	return idade;
}


/*
 * Função: remover_horas
 * ---------------------
 * Remove as horas de uma data e hora no formato "YYYY/MM/DD HH:mm:ss".
 *
 * datetime: A data e hora original.
 * data: Array que armazenará a data resultante.
 */
void remover_horas(char* datetime, char data[]) {
	int i=0;
	for(i=0; datetime[i] != ' ' && datetime[i] != '\0'; i++) {
		data[i] = datetime[i];
	}
	data[i] = '\0';
}


/*
 * Função: q1
 * ----------
 * Executa a Query 1, que recupera informações de usuários, voos ou reservas com base no argumento fornecido.
 *
 * h_users: Tabela hash de usuários.
 * h_voos: Tabela hash de voos.
 * h_reservas: Tabela hash de reservas.
 * arg: O argumento fornecido na Query 1.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q1(hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, char *arg, int f, FILE *fp_output) {
    User *user = RetrieveUser(h_users, arg);
    Voo *voo = RetrieveVoo(h_voos, arg);
    Reserva *reserva = RetrieveReserva(h_reservas, arg);

    if (user) {
        char *accountStatusValue = userGetAccountStatus(user);

        if ((strcasecmp(accountStatusValue, "active") == 0)) {
            char *sexValue = userGetSex(user);
            char *nomeValue = userGetNome(user);
            char *birthValue = userGetBirth(user);
            char *passportValue = userGetPassport(user);
            char *countryValue = userGetCountry(user);

            if (f == 1) {
                fprintf(fp_output, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",
                        nomeValue, sexValue, calculaIdade(birthValue), countryValue, passportValue, userGetTotalVoos(user), userGetTotalReservas(user), userGetTotalGasto(user));
            } else {
                fprintf(fp_output, "%s;%s;%d;%s;%s;%d;%d;%.3f\n",
                        nomeValue, sexValue, calculaIdade(birthValue), countryValue, passportValue, userGetTotalVoos(user), userGetTotalReservas(user), userGetTotalGasto(user));
            }

            free(accountStatusValue);
            free(sexValue);
            free(nomeValue);
            free(birthValue);
            free(passportValue);
            free(countryValue);
        }
    } else if (voo) {
        char *airlineValue = vooGetAirline(voo);
        char *planeModelValue = vooGetPlaneModel(voo);
        char *originValue = vooGetOrigin(voo);
        char *destinationValue = vooGetDestination(voo);
        char *scheduleDepartureDateValue = vooGetScheduleDepartureDate(voo);
        char *scheduleArrivalDateValue = vooGetScheduleArrivalDate(voo);

        if (f == 1) {
            fprintf(fp_output, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n",
                    airlineValue, planeModelValue, originValue, destinationValue, scheduleDepartureDateValue, scheduleArrivalDateValue, vooGetTotalPassengers(voo), vooGetDelay(voo));
        } else {
            fprintf(fp_output, "%s;%s;%s;%s;%s;%s;%d;%d\n",
                    airlineValue, planeModelValue, originValue, destinationValue, scheduleDepartureDateValue, scheduleArrivalDateValue, vooGetTotalPassengers(voo), vooGetDelay(voo));
        }

        free(airlineValue);
        free(planeModelValue);
        free(originValue);
        free(destinationValue);
        free(scheduleDepartureDateValue);
        free(scheduleArrivalDateValue);
    } else if (reserva) {
        char *hotelIdValue = reservaGetHotelId(reserva);
        char *hotelNameValue = reservaGetHotelName(reserva);
        char *hotelStarsValue = reservaGetHotelStars(reserva);
        char *beginDateValue = reservaGetBeginDate(reserva);
        char *endDateValue = reservaGetEndDate(reserva);
        char *includesBreakfastValue = reservaGetIncludesBreakfast(reserva);
        includesBreakfastValue[0] = toupper(includesBreakfastValue[0]);


        if (f == 1) {
            fprintf(fp_output, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %s\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",
                    hotelIdValue, hotelNameValue, hotelStarsValue, beginDateValue, endDateValue, includesBreakfastValue, reservaGetTotalNoites(reserva), reservaGetTotalGasto(reserva));
        } else {
            fprintf(fp_output, "%s;%s;%s;%s;%s;%s;%d;%.3f\n",
                    hotelIdValue, hotelNameValue, hotelStarsValue, beginDateValue, endDateValue, includesBreakfastValue, reservaGetTotalNoites(reserva), reservaGetTotalGasto(reserva));
        }

        free(hotelIdValue);
        free(hotelNameValue);
        free(hotelStarsValue);
        free(beginDateValue);
        free(endDateValue);
        free(includesBreakfastValue);
    }
}








/*
 * Função: q2
 * ----------
 * Executa a Query 2, que recupera informações da lista ligada Q2 de um usuário.
 *
 * h_users: Tabela hash de usuários.
 * argv: Array contendo os argumentos fornecidos na Query 2.
 * argc: Número de argumentos fornecidos na Query 2.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output) {
    char data[100];
    User *user = RetrieveUser(h_users, argv[1]);
    int i = 1;
    if (user && (strcasecmp(userGetAccountStatus(user), "active") == 0)) {
        Q2 *q2 = userGetQ2(user);
        while (q2) {
            char *dataGet = getData(q2);
            remover_horas(dataGet, data);
            if (argc == 3) {
                if (strcmp(argv[2], "reservations") == 0) {
                    if (getTipo(q2) == 1) {
                        if (f == 1) {
                            if (i == 1) {
                                fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n", i, getId(q2), data);
                            } else {
                                fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n", i, getId(q2), data);
                            }
                        } else {
                            fprintf(fp_output, "%s;%s\n", getId(q2), data);
                        }
                        i++;

                        // Liberar a memória alocada para a string id
                        free(getId(q2));
                    }
                } else if (strcmp(argv[2], "flights") == 0) {
                    if (getTipo(q2) == 2) {
                        if (f == 1) {
                            if (i == 1) {
                                fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n", i, getId(q2), data);
                            } else {
                                fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n", i, getId(q2), data);
                            }

                        } else {
                            fprintf(fp_output, "%s;%s\n", getId(q2), data);
                        }
                        i++;

                        // Liberar a memória alocada para a string id
                        free(getId(q2));
                    }
                }
            } else {
                if (getTipo(q2) == 1) {
                    if (f == 1) {
                        if (i == 1) {
                            fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, getId(q2), data);
                        } else {
                            fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, getId(q2), data);
                        }

                    } else {
                        fprintf(fp_output, "%s;%s;reservation\n", getId(q2), data);
                    }

                    i++;

                    // Liberar a memória alocada para a string id
                    free(getId(q2));
                } else {
                    if (f == 1) {
                        if (i == 1) {
                            fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, getId(q2), data);
                        } else {
                            fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, getId(q2), data);
                        }

                    } else {
                        fprintf(fp_output, "%s;%s;flight\n", getId(q2), data);
                    }

                    i++;

                    // Liberar a memória alocada para a string id
                    free(getId(q2));
                }
            }

            // Liberar a memória alocada para a string data
            free(dataGet);

            q2 = getNext(q2);
        }
    }
}



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
void q4(hash_hoteis h_hoteis, char *argv, int f, FILE *fp_output) {
    int i = 1;
    Hotel *aux = RetrieveHotel(h_hoteis, argv);
    if (aux) {
        ReservaResumo *reserva = hotelGetNextResumo(aux);
        while (reserva)  {
            char *idValue = reservaResumoGetId(reserva);
            char *beginDateValue = reservaResumoGetBeginDate(reserva);
            char *endDateValue = reservaResumoGetEndDate(reserva);
            char *userIdValue = reservaResumoGetUserId(reserva);

            if (f == 1) {
                if (i == 1) {
                    fprintf(fp_output, "--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %.0f\ntotal_price: %.3f\n",
                            i, idValue, beginDateValue, endDateValue, userIdValue, reservaResumoGetRating(reserva), reservaResumoGetTotalPrice(reserva));
                } else {
                    fprintf(fp_output, "\n--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %.0f\ntotal_price: %.3f\n",
                            i, idValue, beginDateValue, endDateValue, userIdValue, reservaResumoGetRating(reserva), reservaResumoGetTotalPrice(reserva));
                }
            } else {
                fprintf(fp_output, "%s;%s;%s;%s;%.0f;%.3f\n", idValue, beginDateValue, endDateValue, userIdValue, reservaResumoGetRating(reserva), reservaResumoGetTotalPrice(reserva));
            }

            // Liberar a memória alocada para a string id, beginDate, endDate e userId
            free(idValue);
            free(beginDateValue);
            free(endDateValue);
            free(userIdValue);

            i++;
            reserva = reservaResumoGetNext(reserva);
        }
    }
}






/*
 * Função: q9
 * ----------
 * Executa a Query 9, que recupera informações de usuários com base em um prefixo.
 *
 * h_users: Tabela hash de usuários.
 * argv: O argumento fornecido na Query 9.
 * f: Indica se o formato de saída é detalhado (1) ou simples (0).
 * fp_output: Ponteiro para o ficheiro de saída.
 */
void q9(hash_user h_users, char *argv, int f, FILE *fp_output) {
    User *aux = GetUserPrefix(h_users, argv);
    int i = 1;
    
    if (aux) {
        while (aux) {
            char *userId = userGetId(aux);
            char *nomeValue = userGetNome(aux);

            if (f == 1) {
                if (i == 1) {
                    fprintf(fp_output, "--- %d ---\nid: %s\nname: %s\n", i, userId, nomeValue);
                } else {
                    fprintf(fp_output, "\n--- %d ---\nid: %s\nname: %s\n", i, userId, nomeValue);
                }
                i++;
            } else {
                fprintf(fp_output, "%s;%s\n", userId, nomeValue);
            }

            free(userId);  // Liberar a memória alocada por userGetId
            free(nomeValue); // Liberar a memória alocada por userGetNome
            freeUser(aux);
            aux = userGetNext(aux);
        
        }
    }
}



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
void q5(hash_aeroportos h_aeroportos, char *origin, char *begin_date, char *end_date, int f, FILE *fp_output) {
    VooResumo *aux = GetVoosAeroportoEntreDatas(h_aeroportos, origin, begin_date, end_date);
    int i = 1;
    if (aux) {
        while (aux) {
            char *idValue = vooResumoGetId(aux);
            char *scheduleDepartureDateValue = vooResumoGetScheduleDepartureDate(aux);
            char *destinationValue = vooResumoGetDestination(aux);
            char *airlineValue = vooResumoGetAirline(aux);
            char *planeModelValue = vooResumoGetPlaneModel(aux);

            // Converter todos os caracteres para maiúsculas
            for (int j = 0; destinationValue[j]; j++) {
                destinationValue[j] = toupper(destinationValue[j]);
            }

            if (f == 1) {
                if (i == 1) {
                    fprintf(fp_output, "--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",
                            i, idValue, scheduleDepartureDateValue, destinationValue, airlineValue, planeModelValue);
                } else {
                    fprintf(fp_output, "\n--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",
                            i, idValue, scheduleDepartureDateValue, destinationValue, airlineValue, planeModelValue);
                }
                i++;
            } else {
                fprintf(fp_output, "%s;%s;%s;%s;%s\n", idValue, scheduleDepartureDateValue, destinationValue, airlineValue, planeModelValue);
            }

            // Liberar a memória alocada para as strings id, scheduleDepartureDate, destination, airline e plane_model
            free(idValue);
            free(scheduleDepartureDateValue);
            free(destinationValue);
            free(airlineValue);
            free(planeModelValue);

            aux = vooResumoGetNext(aux);
        }
    }
}







void q6(hash_voos h_voos, char *ano_str, char *N_str, int f, FILE *fp_output) {
    // Converter os argumentos de string para inteiros
    int ano = atoi(ano_str);
    int N = atoi(N_str);

    // Restante da função permanece inalterado
    SomaPassageirosAno *listaSomaPassageiros = criarListaSomaPassageirosAno(h_voos, ano, N);

    // Imprimir os resultados no arquivo ou na tela, dependendo do valor de f
    int i = 1;
    SomaPassageirosAno *current = listaSomaPassageiros;
    while (current != NULL) {
        char *nomeAeroporto = somaGetNomeAeroporto(current);

        if (f == 1) {
            if (i == 1) {
                fprintf(fp_output, "--- %d ---\nname: %s\npassengers: %d\n", i, nomeAeroporto, somaGetTotalPassageiros(current));
            } else {
                fprintf(fp_output, "\n--- %d ---\nname: %s\npassengers: %d\n", i, nomeAeroporto, somaGetTotalPassageiros(current));
            }
            i++;
        } else {
            fprintf(fp_output, "%s;%d\n", nomeAeroporto, somaGetTotalPassageiros(current));
        }

        // Liberar a memória alocada para a string do nome do aeroporto
        free(nomeAeroporto);

        current = somaGetNext(current);
    }

    // Liberar a memória alocada para a lista
    destroiSomaPassageirosAno(listaSomaPassageiros);
}



void q7(hash_aeroportos h_aeroportos, int N, int f, FILE *fp_output) {
    int i = 0;
    MedianaAeroporto *aux = GetMedianaAeroportos(h_aeroportos);
    while (aux && i++ < N) {
        char *nome = medianaGetNome(aux);

        if (f == 1) {
            if (i == 1) {
                fprintf(fp_output, "--- %d ---\nname: %s\nmedian: %d\n", i, nome, medianaGetMediana(aux));
            } else {
                fprintf(fp_output, "\n--- %d ---\nname: %s\nmedian: %d\n", i, nome, medianaGetMediana(aux));
            }
        } else {
            fprintf(fp_output, "%s;%d\n", nome, medianaGetMediana(aux));
        }

        // Liberar a memória alocada para a string do nome do aeroporto
        free(nome);

        aux = medianaGetNext(aux);
    }

    // Liberar a memória alocada para a lista
    destroiMedianaAeroporto(aux);
}


void q8(hash_hoteis h_hoteis,char *argv, char *start_date, char *end_date, int f, FILE *fp_output) {
	int i = 0;
	int lucro =GetLucro(h_hoteis,argv, start_date, end_date);
		if(f == 1) {
			if(i == 1) {
				fprintf(fp_output,"--- 1 ---\nrevenue: %d\n",lucro);
			}
			else {
				fprintf(fp_output,"--- 1 ---\nrevenue: %d\n",lucro);
			}
			
		}
		else {
			fprintf(fp_output,"%d\n",lucro);
		}
	
}

/*
void q10(hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, char **argv, int argc, int f, FILE *fp_output) {
    int yearToCount = -1;
    int monthToCount = -1;
	int le=0;

	
    // Verifica se o ano foi fornecido como argumento
    if (argc > 1) {
        if (isdigit(argv[1][0])) {
            yearToCount = atoi(argv[1]);

            // Verifica se o mês foi fornecido como argumento
            if (argc > 2) {
                if (isdigit(argv[2][0])) {
                    monthToCount = atoi(argv[2]);
                } else {
                    // Se o segundo argumento não for um dígito, considera-o como parte do ano
                    if (argc > 2 && isdigit(argv[2][0])) {
                        yearToCount = atoi(argv[1]) * 100 + atoi(argv[2]);
                    }
                }
            }
        }
    }

    // Análise de anos
	if (yearToCount == -1) {
		int r = 0;

		for (int j = 2010; j < 2024; j++) {
			int totalUsersAno = CountUsersByYear(h_users, j);
			int totalVoosAno = SomaVoosPorAno(h_voos, j);
			int totalPassageirosAno = SomaPassageirosPorAno(h_voos, j);
			int total = SomaPassageirosPorAnoUnico(h_users, j);
			int totalReservasAno = ContarReservasPorAno(h_reservas, j);
			r++;


			// Modificação na impressão para considerar o formato
			if (f == 1 && (totalUsersAno + totalVoosAno + totalPassageirosAno + total + totalReservasAno) > 0) {
				fprintf(fp_output, "--- %d ---\nyear: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n\n", r, j, totalUsersAno, totalVoosAno, totalPassageirosAno, total, totalReservasAno);
			} else if (totalUsersAno + totalVoosAno + totalPassageirosAno + total + totalReservasAno > 0) {
				fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", j, totalUsersAno, totalVoosAno, totalPassageirosAno, total, totalReservasAno);
			}
		}
	}

    // Análise de meses
	if (yearToCount != -1 && monthToCount == -1) {

		for (int i = 1; i <= 12; i++) {
			int totalUsersNoMes = CountUsersByMonth(h_users, yearToCount, i);
			int totalVoosNoMes = SomaVoosPorMes(h_voos, yearToCount, i);
			int totalPassageirosMes = SomaPassageirosPorMes(h_voos, yearToCount, i);
			int total1 = SomaPassageirosPorAnoMesUnico(h_users, yearToCount, i);
			int totalReservasNoMes = ContarReservasPorMes(h_reservas, yearToCount, i);
			

			if ( (totalUsersNoMes + totalVoosNoMes + totalPassageirosMes + total1 + totalReservasNoMes)>0) {
				// Modificação na impressão para considerar o formato
				if (f == 1) {
					fprintf(fp_output, "--- %d ---\nmonth: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", i, i, totalUsersNoMes, totalVoosNoMes, totalPassageirosMes, total1, totalReservasNoMes);
					if (i<9) {fprintf(fp_output, "\n\n");}
				} else {
					fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", i, totalUsersNoMes, totalVoosNoMes, totalPassageirosMes, total1, totalReservasNoMes);
				}
			}
		}
	}


    // Análise de dias
	if (yearToCount != -1 && monthToCount != -1) {
		int l = 0;

		for (int d = 1; d <= 31; d++) {
			int totalUsersNaData = CountUsersByDate(h_users, yearToCount, monthToCount, d);
			int totalVoosNaData = SomaVoosPorDia(h_voos, yearToCount, monthToCount, d);
			int totalPassageirosDia = SomaPassageirosPorDia(h_voos, yearToCount, monthToCount, d);
			int total2 = SomaPassageirosPorAnoMesDataUnica(h_users, yearToCount, monthToCount, d);
			int totalReservasNaData = ContarReservasPorData(h_reservas, yearToCount, monthToCount, d);
			l++;


			// Modificação na impressão para considerar o formato
			if (f == 1 && (totalUsersNaData + totalVoosNaData + totalPassageirosDia + total2 + totalReservasNaData) > 0) {
				le++;
				fprintf(fp_output, "--- %d ---\nday: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n\n", le, d, totalUsersNaData, totalVoosNaData, totalPassageirosDia, total2, totalReservasNaData);
			} else if ( (totalUsersNaData + totalVoosNaData + totalPassageirosDia + total2 + totalReservasNaData)> 0) {
				fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", d, totalUsersNaData, totalVoosNaData, totalPassageirosDia, total2, totalReservasNaData);
			}
		}
	}
}
*/

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
	else if(strcmp(args[0], "6") == 0 || strcmp(args[0], "6F") == 0) {
		q6(h_voos, args[1], args[2], f, fp_output);
	}
	else if(strcmp(args[0], "7") == 0 || strcmp(args[0], "7F") == 0) {
		q7(h_aeroportos, atoi(args[1]), f, fp_output);
	}
	else if(strcmp(args[0], "8") == 0 || strcmp(args[0], "8F") == 0) {
		q8(h_hoteis, args[1], args[2],args[3], f, fp_output);
	}
	else if(strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) {
		q9(h_users, args[1], f, fp_output);
	}
	//else if(strcmp(args[0], "10") == 0 || strcmp(args[0], "10F") == 0) {
	//	q10(h_users, h_voos, h_reservas, args, argc,f, fp_output);
	//}
	
	
	
	return 1;
}

int comando_interativo(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos){
    int argc = 0;
    char *args[MAX_ARGS];
    split(linha, &argc, args);
    int f = 0;

	if (linha[1] != ' ' && linha[1] != 'F' && linha[1] != '0') return 1;

    if(chdir("Resultados/") != 0){
        printf("Error");
    }

    FILE *fp_output = fopen("comando_output.txt", "w");
    if (fp_output == NULL) {
        // Tratar erro de abertura de arquivo
        return 1;
    }

	if (strstr(linha, "F") != NULL) {
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
	else if(strcmp(args[0], "6") == 0 || strcmp(args[0], "6F") == 0) {
		q6(h_voos, args[1], args[2], f, fp_output);
	}
	else if(strcmp(args[0], "7") == 0 || strcmp(args[0], "7F") == 0) {
		q7(h_aeroportos, atoi(args[1]), f, fp_output);
	}
	else if(strcmp(args[0], "8") == 0 || strcmp(args[0], "8F") == 0) {
		q8(h_hoteis, args[1], args[2],args[3], f, fp_output);
	}
	else if(strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) {
		q9(h_users, args[1], f, fp_output);
	}
	//else if(strcmp(args[0], "10") == 0 || strcmp(args[0], "10F") == 0) {
	//	q10(h_users, h_voos, h_reservas, args, argc,f, fp_output);
	//}

    if (chdir("trabalho-pratico") != 0){
		printf("Error");
	}
    fclose(fp_output);

    return 0;
}

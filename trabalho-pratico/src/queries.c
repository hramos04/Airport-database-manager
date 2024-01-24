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
#include "../include/queries.h"


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
                fprintf(fp_output, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3lf\n",
                        nomeValue, sexValue, calculaIdade(birthValue), countryValue, passportValue, userGetTotalVoos(user), userGetTotalReservas(user), userGetTotalGasto(user));
            } else {
                fprintf(fp_output, "%s;%s;%d;%s;%s;%d;%d;%.3lf\n",
                        nomeValue, sexValue, calculaIdade(birthValue), countryValue, passportValue, userGetTotalVoos(user), userGetTotalReservas(user), userGetTotalGasto(user));
            }

            free(sexValue);
            free(nomeValue);
            free(birthValue);
            free(passportValue);
            free(countryValue);
        }
        free(accountStatusValue);
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


void q2(hash_user h_users, char **argv, int argc, int f, FILE *fp_output) {
    char data[100];
    User *user = RetrieveUser(h_users, argv[1]);
    int i = 1;

    if (user && (strcasecmp(userGetAccountStatus(user), "active") == 0)) {
        Q2 *q2 = userGetQ2(user);

        while (q2) {
            char *dataGet = getData(q2);
            remover_horas(dataGet, data);
            char *idCopy = getId(q2);

            if (argc == 3) {
                if (strcmp(argv[2], "reservations") == 0) {
                    if (getTipo(q2) != 2) {
                        if (f == 1) {
                            if (i == 1) {
                                fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n", i, idCopy, data);
                            } else {
                                fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n", i, idCopy, data);
                            }
                        } else {
                            fprintf(fp_output, "%s;%s\n", idCopy, data);
                        }
                        i++;
                    }
                } else if (strcmp(argv[2], "flights") == 0) {
                    if (getTipo(q2) == 2) {
                        if (f == 1) {
                            if (i == 1) {
                                fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\n", i, idCopy, data);
                            } else {
                                fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\n", i, idCopy, data);
                            }
                        } else {
                            fprintf(fp_output, "%s;%s\n", idCopy, data);
                        }
                        i++;
                    }
                }
            } else {
                if (getTipo(q2) != 2) {
                    if (f == 1) {
                        if (i == 1) {
                            fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, idCopy, data);
                        } else {
                            fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\ntype: reservation\n", i, idCopy, data);
                        }
                    } else {
                        fprintf(fp_output, "%s;%s;reservation\n", idCopy, data);
                    }
                    i++;
                } else {
                    if (f == 1) {
                        if (i == 1) {
                            fprintf(fp_output, "--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, idCopy, data);
                        } else {
                            fprintf(fp_output, "\n--- %d ---\nid: %s\ndate: %s\ntype: flight\n", i, idCopy, data);
                        }
                    } else {
                        fprintf(fp_output, "%s;%s;flight\n", idCopy, data);
                    }
                    i++;
                }
            }
            free(dataGet);
            q2 = getNext(q2);
            free(idCopy);
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
            free(idValue);
            free(beginDateValue);
            free(endDateValue);
            free(userIdValue);

            i++;
            reserva = reservaResumoGetNext(reserva);
        }
    }
}


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
            free(idValue);
            free(scheduleDepartureDateValue);
            free(destinationValue);
            free(airlineValue);
            free(planeModelValue);
            
            VooResumo *temp=aux;
            aux = vooResumoGetNext(aux);
            destroiVooAeroportoEntreDatas(temp);
        }
    }
}


void q6(hash_voos h_voos, char *ano_str, char *N_str, int f, FILE *fp_output) {
    int ano = atoi(ano_str);
    int N = atoi(N_str);

    SomaPassageirosAno *listaSomaPassageiros = criarListaSomaPassageirosAno(h_voos, ano, N);

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

        free(nomeAeroporto);

        current = somaGetNext(current);
    }
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
        free(nome);
        MedianaAeroporto *temp=aux;
        aux = medianaGetNext(aux);
        destroiMedianaAeroporto(temp);
    }
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

            free(userId);  
            free(nomeValue); 
            User *temp = aux;  
            aux = userGetNext(aux);
            freeUser(temp);  
        }
    }
}


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
        int comeco=0;
		for (int j = 2010; j < 2024; j++) {
			int totalUsersAno = CountUsersByYear(h_users, j);
			int totalVoosAno = SomaVoosPorAno(h_voos, j);
			int totalPassageirosAno = SomaPassageirosPorAno(h_voos, j);
			int total = SomaPassageirosPorAnoUnico(h_users, j);
			int totalReservasAno = ContarReservasPorAno(h_reservas, j);
			r++;
            

			if (f == 1 && (totalUsersAno + totalVoosAno + totalPassageirosAno + total + totalReservasAno) > 0) {
                if(comeco==0) {
                    fprintf(fp_output, "--- %d ---\nyear: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", r, j, totalUsersAno, totalVoosAno, totalPassageirosAno, total, totalReservasAno);
                    comeco++;
                } else {
				fprintf(fp_output, "\n\n--- %d ---\nyear: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", r, j, totalUsersAno, totalVoosAno, totalPassageirosAno, total, totalReservasAno);
                }
			} else if (totalUsersAno + totalVoosAno + totalPassageirosAno + total + totalReservasAno > 0) {
				fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", j, totalUsersAno, totalVoosAno, totalPassageirosAno, total, totalReservasAno);
			}
		}
	}

    // Análise de meses
	if (yearToCount != -1 && monthToCount == -1) {
        int comeco=0;
		for (int i = 1; i <= 12; i++) {
			int totalUsersNoMes = CountUsersByMonth(h_users, yearToCount, i);
			int totalVoosNoMes = SomaVoosPorMes(h_voos, yearToCount, i);
			int totalPassageirosMes = SomaPassageirosPorMes(h_voos, yearToCount, i);
			int total1 = SomaPassageirosPorAnoMesUnico(h_users, yearToCount, i);
			int totalReservasNoMes = ContarReservasPorMes(h_reservas, yearToCount, i);

			if ( (totalUsersNoMes + totalVoosNoMes + totalPassageirosMes + total1 + totalReservasNoMes)>0) {
				if (f == 1) {
                    if(comeco==0) {
                        fprintf(fp_output, "--- %d ---\nmonth: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", i, i, totalUsersNoMes, totalVoosNoMes, totalPassageirosMes, total1, totalReservasNoMes);
                        comeco++;
                    }  else {
					fprintf(fp_output, "\n\n--- %d ---\nmonth: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", i, i, totalUsersNoMes, totalVoosNoMes, totalPassageirosMes, total1, totalReservasNoMes);
                    }
				} else {
					fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", i, totalUsersNoMes, totalVoosNoMes, totalPassageirosMes, total1, totalReservasNoMes);
				}
			}
            printf("\n");
		}
	}


    // Análise de dias
	if (yearToCount != -1 && monthToCount != -1) {
		int l = 0;
        int comeco=0;
		for (int d = 1; d <= 31; d++) {
			int totalUsersNaData = CountUsersByDate(h_users, yearToCount, monthToCount, d);
			int totalVoosNaData = SomaVoosPorDia(h_voos, yearToCount, monthToCount, d);
			int totalPassageirosDia = SomaPassageirosPorDia(h_voos, yearToCount, monthToCount, d);
			int total2 = SomaPassageirosPorAnoMesDataUnica(h_users, yearToCount, monthToCount, d);
			int totalReservasNaData = ContarReservasPorData(h_reservas, yearToCount, monthToCount, d);
			l++;
            

			if (f == 1 && (totalUsersNaData + totalVoosNaData + totalPassageirosDia + total2 + totalReservasNaData) > 0) {
				le++;
                if(comeco==0) {
                    fprintf(fp_output, "--- %d ---\nday: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", le, d, totalUsersNaData, totalVoosNaData, totalPassageirosDia, total2, totalReservasNaData);
                    comeco++;
                }
                else {
				fprintf(fp_output, "\n\n--- %d ---\nday: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d", le, d, totalUsersNaData, totalVoosNaData, totalPassageirosDia, total2, totalReservasNaData);
                }
			} else if ( (totalUsersNaData + totalVoosNaData + totalPassageirosDia + total2 + totalReservasNaData)> 0) {
				fprintf(fp_output, "%d;%d;%d;%d;%d;%d\n", d, totalUsersNaData, totalVoosNaData, totalPassageirosDia, total2, totalReservasNaData);
			}
		}
	}
}


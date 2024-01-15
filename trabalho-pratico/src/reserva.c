#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/reserva.h"



/* Função de hash que converte uma chave num índice na tabela hash dos hoteis. */
int HashHoteis(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZERESERVA;
}


/* Função de hash que converte uma chave num índice na tabela hash das reservas. */
int HashReservas(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZERESERVA;
}


/* Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h) {
    int i;
    for (i = 0; i < HASHSIZERESERVA; ++i)
        h[i] = NULL;
}


/* Função que inicializa a tabela de hash Reservas. */
void InitializeTableReservas(hash_reservas h) {
    int i;
    for (i = 0; i < HASHSIZERESERVA; ++i)
        h[i] = NULL;
}


/* Função que retorna a Reserva pretendida, caso esta se encontre na hash, através da sua respetiva 
chave. */
Reserva *RetrieveReserva(hash_reservas h, KeyType k) {
	 int i = HashReservas(k);
	 Reserva *res;
	 for(res = h[i]; res; res = res->next_reserva) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}


/* Função que retorna o Hotel pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Hotel *RetrieveHotel(hash_hoteis h, KeyType k) {
	 int i = HashHoteis(k);
	 Hotel *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->hotel_id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

void destroiTableReserva(hash_reservas h) {

	for(int i = 0; i<HASHSIZERESERVA; i++){
		Reserva *atual = h[i];
		while(atual!=NULL){
			Reserva *position = atual;
			atual = atual->next_reserva;
			free(position->id);
			free(position->user_id);
			free(position->hotel_id);
			free(position->hotel_name);
			free(position->hotel_stars);
			free(position->city_tax);
			free(position->address);
			free(position->begin_date);
			free(position->end_date);
			free(position->price_per_night);
			free(position->includes_breakfast);
			free(position->room_details);
			free(position->rating);
			free(position->comment);
		}
		free(h[i]);
	}
}


void destroiReservaResumo(ReservaResumo *reservaResumo){

	while(reservaResumo!=NULL){
		ReservaResumo *atual = reservaResumo;
		reservaResumo = reservaResumo->next_resumo;
		free(atual->id);
		free(atual->begin_date);
		free(atual->end_date);	
		free(atual->user_id);
	}
	free(reservaResumo);
}

void destroiTableHotel(hash_hoteis h) {

	for(int i = 0; i<HASHSIZERESERVA; i++){
		Hotel *atual = h[i];
		while(atual!=NULL){
			Hotel *position = atual;
			atual = atual->next;
			free(position->hotel_id);
			destroiReservaResumo(position->next_resumo);
		}
		free(h[i]);
	}
}


/* Função que calcula a média das classificações de um hotel, percorrendo a lista ligada 
das reservas e somando os diferentes ratings em cada reserva. */
double GetRatingByHotel(hash_hoteis h, KeyType k) {
	Hotel *aux = RetrieveHotel(h, k);
	if(aux) {
		double total_rating = 0;;
		int total_opinioes = 0;
		ReservaResumo *reserva = aux->next_resumo;
		while(reserva) {
			if(reserva->rating >= 1 && reserva->rating <= 5) {
				total_opinioes++;
				total_rating += reserva->rating;
			}
			
			reserva = reserva->next_resumo;
		}
		
		if(total_opinioes > 0) {
			
			return total_rating/total_opinioes;
		}
	}
	return -1;
}


int CalcularNumeroNoitesDias(char *start_date, char *end_date) {
    // Converte as datas para um formato que pode ser manipulado mais facilmente
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;

    sscanf(start_date, "%d/%d/%d", &start_year, &start_month, &start_day);
    sscanf(end_date, "%d/%d/%d", &end_year, &end_month, &end_day);

    // Calcula o número de noites (arredondando para cima)
    int num_noites;

    num_noites = (end_day - start_day) +1;

    return num_noites;
}

int CalcularNumeroNoitesMes(char *start_date, char *end_date) {
    // Converte as datas para um formato que pode ser manipulado mais facilmente
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;

    sscanf(start_date, "%d/%d/%d", &start_year, &start_month, &start_day);
    sscanf(end_date, "%d/%d/%d", &end_year, &end_month, &end_day);

    // Calcula o número de noites (arredondando para cima)
    int num_noites;
    num_noites = (end_year - start_year) * 365 + (end_month - start_month) * 29 + (end_day - start_day);
    

    return num_noites;
}
/* Função para obter o lucro de um hotel entre duas datas */
int GetLucro(hash_hoteis h, KeyType k, char *start_date, char *end_date) {
    Hotel *hotel = RetrieveHotel(h, k);
    if (hotel) {
        int lucro = 0;

        // Percorre a lista ligada de ReservaResumo do hotel
        ReservaResumo *reserva_resumo = hotel->next_resumo;
        while (reserva_resumo != NULL) {
            // Verifica se há sobreposição de datas entre a reserva e o intervalo estabelecido
            if (strcmp(reserva_resumo->end_date, start_date) < 0 || strcmp(reserva_resumo->begin_date, end_date) > 0) {
                // Não há sobreposição, continua para a próxima reserva
                reserva_resumo = reserva_resumo->next_resumo;
                continue;
            }

            // Ajusta as datas de início e fim para o cálculo do lucro
            char *inicio_reserva = (strcmp(reserva_resumo->begin_date, start_date) >= 0) ? reserva_resumo->begin_date : start_date;
            char *fim_reserva = (strcmp(reserva_resumo->end_date, end_date) <= 0) ? reserva_resumo->end_date : end_date;

            // Verifica se apenas os dias mudaram
            if (strcmp(inicio_reserva, start_date) == 0 && strcmp(fim_reserva, end_date) == 0) {
                int num_noites = CalcularNumeroNoitesDias(inicio_reserva, fim_reserva);
                lucro += num_noites * atof(reserva_resumo->price_per_night);
            } else {
                // Caso geral, incluindo quando meses e dias mudam
                int num_noites = CalcularNumeroNoitesMes(inicio_reserva, fim_reserva);
                lucro += num_noites * atof(reserva_resumo->price_per_night);
            }

            // Avança para a próxima reserva na lista
            reserva_resumo = reserva_resumo->next_resumo;
        }

        return lucro;
    }
    return -1; // Retorna -1 se o hotel não for encontrado
}



/* A função verifica se um Hotel está presente na tabela hash. Caso não esteja, adiciona o novo Hotel 
à tabela. Posteriormente, insere ordenadamente um novo ReservaResumo associado a esse hotel, na 
lista ligada, vinculada a esse Hotel .*/
void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva) {
    int i = HashHoteis(k);
    
    Hotel *aux = RetrieveHotel(h, k);
    if(!aux) {
		Hotel *novo_hotel = (Hotel *)malloc(sizeof(Hotel));
		novo_hotel->hotel_id = strdup(k);
		novo_hotel->next = NULL;
		novo_hotel->next_resumo = NULL;
		aux = novo_hotel;
		if (h[i] == NULL) {
			h[i] = aux;
		}
		else {
			aux->next = h[i];
			h[i] = aux;
		}
	}
	
	ReservaResumo *currentQ2 = aux->next_resumo;
	ReservaResumo *prevQ2 = NULL;
	
	while (currentQ2 != NULL && strcmp(currentQ2->begin_date, reserva->begin_date) >= 0) {
		
		prevQ2 = currentQ2;
		currentQ2 = currentQ2->next_resumo;
	}

	if (prevQ2 == NULL) {
		// Inserir no início
		reserva->next_resumo = aux->next_resumo;
		aux->next_resumo = reserva;
	} else {
		// Inserir no meio ou no final
		prevQ2->next_resumo = reserva;
		reserva->next_resumo = currentQ2;
	}
}


/* A função insere uma Reserva na tabela hash das Reservas, caso a posição estiver livre coloca a 
Reserva nessa posição, caso a posição já estiver ocupada, adiciona a reserva no início da lista 
encadeada dessa posição. */
void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva) {
    int i = HashReservas(k);
    if (h[i] == NULL) {
        h[i] = reserva;
    }
    else {
        reserva->next_reserva = h[i];
        h[i] = reserva;
    }
}


int ContarReservasPorAno(hash_reservas h, int ano) {
    int totalReservas = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            // Extrair o ano da data de início da reserva
            int anoReserva;
            sscanf(res->begin_date, "%d", &anoReserva);

            // Verificar se o ano coincide e incrementar o total
            if (anoReserva == ano) {
                totalReservas++;
            }

            res = res->next_reserva;
        }
    }

    return totalReservas;
}

int ContarReservasPorMes(hash_reservas h, int ano, int mes) {
    int totalReservasNoMes = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            // Extrair o ano e mês da data de início da reserva
            int anoReserva, mesReserva;
            sscanf(res->begin_date, "%d/%d", &anoReserva, &mesReserva);

            // Verificar se o ano e mês coincidem
            if (anoReserva == ano && mesReserva == mes) {
                // Incrementar o total de reservas para o mês correspondente
                totalReservasNoMes++;
            }

            res = res->next_reserva;
        }
    }

    // Retornar o resultado
    return totalReservasNoMes;
}

int ContarReservasPorData(hash_reservas h, int ano, int mes, int dia) {
    int totalReservasNaData = 0;

    for (int i = 0; i < HASHSIZERESERVA; ++i) {
        Reserva *res = h[i];
        while (res != NULL) {
            // Extrair o ano, mês e dia da data de início da reserva
            int anoReserva, mesReserva, diaReserva;
            sscanf(res->begin_date, "%d/%d/%d", &anoReserva, &mesReserva, &diaReserva);

            // Verificar se a data coincide
            if (anoReserva == ano && mesReserva == mes && diaReserva == dia) {
                // Incrementar o total de reservas para a data correspondente
                totalReservasNaData++;
            }

            res = res->next_reserva;
        }
    }

    // Retornar o resultado
    return totalReservasNaData;
}


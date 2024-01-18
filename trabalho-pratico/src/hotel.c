#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/hotel.h"




/* Definição de um nó da lista ligada ReservaResumo, que apresenta dados filtrados e importantes 
de cada reserva. */
struct ReservaResumo {
    char *id;
    char *begin_date;
    char *end_date;
    char *user_id;
    char *price_per_night;
    double total_price;
    double rating;
    struct ReservaResumo *next_resumo;
};


/* Definição da estrutura Hotel, que apresenta o respetivo id de cada hotel e a lista ligada 
ReservaResumo que apresenta então todas as reservas associadas ao determinado hotel. */
struct Hotel {
	char *hotel_id;
	struct Hotel *next;
	struct ReservaResumo *next_resumo;
};

ReservaResumo *createReservaResumo(char *id, char *begin_date, char *end_date, char *user_id, char *price_per_night, double total_price, double rating){
    ReservaResumo *reservaResumo = malloc(sizeof(ReservaResumo));
    
    reservaResumo->id = strdup(id);
    reservaResumo->begin_date = strdup(begin_date);
    reservaResumo->end_date = strdup(end_date);
    reservaResumo->user_id = strdup(user_id);
    reservaResumo->price_per_night = strdup(price_per_night);
    reservaResumo->total_price = total_price;
    reservaResumo->rating = rating;
    reservaResumo->next_resumo = NULL;
    
    return reservaResumo;
}

char *reservaResumoGetId(ReservaResumo *reservaResumo){ //já está tratado os leaks 
    return strdup(reservaResumo->id);
}

char *reservaResumoGetBeginDate(ReservaResumo *reservaResumo){ //já está tratado os leaks 
    return strdup(reservaResumo->begin_date);
}

char *reservaResumoGetEndDate(ReservaResumo *reservaResumo){ //já está tratado os leaks 
    return strdup(reservaResumo->end_date);
}

char *reservaResumoGetUserId(ReservaResumo *reservaResumo){ //já está tratado os leaks 
    return strdup(reservaResumo->user_id);
}

double reservaResumoGetTotalPrice(ReservaResumo *reservaResumo){
    return reservaResumo->total_price;
}

double reservaResumoGetRating(ReservaResumo *reservaResumo){
    return reservaResumo->rating;
}

ReservaResumo *reservaResumoGetNext(ReservaResumo *reservaResumo){
    return reservaResumo->next_resumo;
}

Hotel *hotelGetNext(Hotel *hotel){
    return hotel->next;
}

void setNextHotel(Hotel *hotel, Hotel *next){
    hotel->next = next;
}

ReservaResumo *hotelGetNextResumo(Hotel *hotel){
    return hotel->next_resumo;
}

void setNextHotelResumo(Hotel *hotel, Hotel *next){
    hotel->next = next;
}

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

/* Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h) {
    int i;
    for (i = 0; i < HASHSIZERESERVA; ++i)
        h[i] = NULL;
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


void destroiReservaResumo(ReservaResumo *reservaResumo){

	while(reservaResumo!=NULL){
		ReservaResumo *atual = reservaResumo;
		reservaResumo = reservaResumo->next_resumo;
		free(atual->id);
		free(atual->begin_date);
		free(atual->end_date);	
		free(atual->user_id);
        free(atual->price_per_night);
        free(atual);
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







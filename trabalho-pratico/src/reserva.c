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
    return h % HASHSIZE;
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
    return h % HASHSIZE;
}


/* Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que inicializa a tabela de hash Reservas. */
void InitializeTableReservas(hash_reservas h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
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
	 Hotel *root =h[i];
	 
	 while(root != NULL) {
		 int compare = strcmp(k, root->hotel_id);
		 if(compare == 0) {
			 return root;
		 } else if(compare < 0) {
			 root = root->left;
		 } else {
			 root = root->right;
		 }
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

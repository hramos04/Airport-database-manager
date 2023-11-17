#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passenger.h"



int HashPassenger(char *id) {
    int hash = 0;
    while (*id) {
        hash += *id;
        ++id;
    }
    return hash % HASHSIZE;
}

// Função para inicializar a tabela hash
void InitializeTablePassenger(HashTablePassenger h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

Passenger *RetrievePassenger(HashTablePassenger h, char *id) {
	 int i = HashPassenger(id);
	 Passenger *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->user_id, id) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}



/*void InsertReserva(HashTable h, char *id, Reserva reserva) {
	User *res = RetrieveUser(h, id);
	if(res) {
		//inserir na lista ligada de reservas do User
		
		
	}
	
}*/



// Função para inserir na tabela hash usando encadeamento separado em caso de colisão
void InsertTablePassenger(HashTablePassenger h, char *flight_id, char *user_id) {
    
    
    
    int i = HashPassenger(user_id);

    // Criar novo usuário
    Passenger *novo_passageiro = malloc(sizeof(Passenger));
    novo_passageiro->flight_id = strdup(flight_id);
    novo_passageiro->user_id = strdup(user_id);
    novo_passageiro->next = NULL;

    // Lidar com colisões usando encadeamento separado
    if (h[i] == NULL) {
        // Se o slot estiver vazio, apenas insira o novo usuário
        h[i] = novo_passageiro;
        printf("inseri: %s\n",novo_passageiro->user_id);
    } else {
        // Se houver colisão, adicione o novo usuário no início da lista
        novo_passageiro->next = h[i];
        h[i] = novo_passageiro;
    }
}


// Função para imprimir a tabela hash
void PrintHashTablePassenger(HashTablePassenger h) {
    for (int i = 0; i < HASHSIZE; ++i) {
        Passenger *aux = h[i];
        while (aux) {
			printf("Flight Id: %s, User Id: %s",
                   aux->flight_id, aux->user_id);
            aux = aux->next;
        }
    }
}










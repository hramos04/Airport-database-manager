#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

int Hash(KeyType k) {
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

// Função para inicializar a tabela hash
void InitializeTable(hash_user h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

User *RetrieveUser(hash_user h, KeyType k) {
	 int i = Hash(k);
	 User *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

// Função para inserir na tabela hash usando encadeamento separado em caso de colisão
void InsertTable(hash_user h, KeyType k, User *user) {
    int i = Hash(k);
    if (h[i] == NULL) {
        h[i] = user;
    }
    else {
        user->next = h[i];
        h[i] = user;
    }
}

void InsertReservaUser(hash_user h, KeyType k, Q2 *q2) {
	User *aux = RetrieveUser(h, k);
	if(!aux) {
		return;
	}
	while(aux) {
		if(strcmp(k, aux->id) == 0) {
			break;
		}
		aux = aux->next;
	}
	
	if(aux) {
		aux->total_reservas++;
		aux->total_gasto += q2->total_gasto;
		Q2 *currentQ2 = aux->q2;
		Q2 *prevQ2 = NULL;
		
		while (currentQ2 != NULL && strcmp(currentQ2->data, q2->data) >= 0) {
			prevQ2 = currentQ2;
			currentQ2 = currentQ2->next;
		}

		if (prevQ2 == NULL) {
			// Inserir no início
			q2->next = aux->q2;
			aux->q2 = q2;
		} else {
			// Inserir no meio ou no final
			prevQ2->next = q2;
			q2->next = currentQ2;
		}
	}
}

void InsertVooUser(hash_user h, KeyType k, Q2 *q2) {
	User *aux = RetrieveUser(h, k);
	if(!aux) {
		return;
	}
	while(aux) {
		if(strcmp(k, aux->id) == 0) {
			break;
		}
		aux = aux->next;
	}
	
	if(aux) {
		aux->total_voos++;
		Q2 *currentQ2 = aux->q2;
		Q2 *prevQ2 = NULL;
		
		while (currentQ2 != NULL && strcmp(currentQ2->data, q2->data) >= 0) {
			prevQ2 = currentQ2;
			currentQ2 = currentQ2->next;
		}

		if (prevQ2 == NULL) {
			// Inserir no início
			q2->next = aux->q2;
			aux->q2 = q2;
		} else {
			// Inserir no meio ou no final
			prevQ2->next = q2;
			q2->next = currentQ2;
		}
		/*if(aux->q2 == NULL) {
			aux->q2 = q2;
		}
		else {
			q2->next = aux->q2;
			aux->q2 = q2;
		}*/
	
	}
}


void Printhash_user(hash_user h) {
	int total_users = 0;
	int total_reservas_validas = 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        User *aux = h[i];
        while (aux) {
            Q2 *rr = aux->q2;
            int total_reservas = 0;
            
            //printf("\n\nPos: %d, ID: %s, Nome: %s, Email: %s, Phone: %s, Birth: %s, Sex: %s, Passport: %s, Country: %s, Adrress: %s, Account: %s, Pay: %s, Status: %s\n", i, aux->id, aux->nome, aux->email, aux->phone, aux->birth, aux->sex, aux->passport, aux->country, aux->address, aux->account_creation, aux->pay_method, aux->account_status);
            
            while(rr) {
				printf("%s, %s, %d\n",rr->id, rr->data, rr->tipo);
				total_reservas++;
				total_reservas_validas++;
				rr = rr->next;
			}
			if(total_reservas > 0) {
				
				//printf("Total Reservas: %d\n",total_reservas);
			}
			
            
            aux = aux->next;
            total_users++;
        }
    }
    printf("Total Users: %d\n",total_users);
    printf("Total Reservas Global: %d\n",total_reservas_validas);
}











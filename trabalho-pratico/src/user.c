#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/user.h"


/* Função de hash que converte uma chave num índice na tabela hash. */
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
    return h % HASHSIZEUSER;
}


/* Função que inicializa a tabela de hash User. */
void InitializeTable(hash_user h) {
    int i;
    for (i = 0; i < HASHSIZEUSER; ++i)
        h[i] = NULL;
}


void destroiTableUser(hash_user h) {

	for(int i = 0; i<HASHSIZEUSER; i++){
		User *atual = h[i];
		while(atual!=NULL){
			User *position = atual;
			atual = atual->next;
			free(position->id);
			free(position->nome);
			free(position->email);
			free(position->phone);
			free(position->birth);
			free(position->sex);
			free(position->passport);
			free(position->country);
			free(position->address);
			free(position->account_creation);
			free(position->pay_method);
			free(position->account_status);
			destroiQ2(position->q2);
		}
		free(h[i]);
	}
}


void destroiQ2(Q2 *q2){

	while(q2!=NULL){
		Q2 *atual = q2;
		q2 = q2->next;
		free(atual->id);
		free(atual->data);
		free(atual);
	}
	free(q2);
}


/* Função que retorna o User pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
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


/* Função auxiliar que cria uma copia de um determinado User. */
User* copyUser(User *original) {
    User *copy = malloc(sizeof(User));
    copy->id = strdup(original->id);
    copy->nome = strdup(original->nome);
    copy->next = NULL;
    return copy;
}


/* Função auxiliar que compara duas strings, que neste caso em concreto, vai ser utilizada para
comparar nomes, com a particularidade de ignorar hífens nos mesmos. */
int compareNamesWithoutHyphenIgnoreCase(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        while (*str1 == '-' && *str2 == '-') {
            str1++;
            str2++;
        }

        int result = strcoll(str1, str2);

        if (result != 0) {
            return result;
        } else {
            str1 += strlen(str1); 
            str2 += strlen(str2);  
        }
    }
    return strcoll(str1, str2);
}


/* Função auxiliar que adiciona um User a uma lista, que é ordenada pelos nomes dos diferentes
Users. */
void addUserToList(User **list, User *newUser) {
    while (*list != NULL) {
        int compare = strcoll(newUser->nome, (*list)->nome);
        if (compare < 0  || (compare == 0 && strcoll(newUser->id,(*list)->id) < 0)) {
            newUser->next = *list;
            *list = newUser;
            return;
        }
        list = &(*list)->next;
    }
    *list = newUser;
}


/* Função auxiliar que percorre a tabela hash, procurando Users que apresentem o parametro 
"active" e cujos nomes começam com um determinado prefixo, retornando uma lista ordenada 
desses Users, com a ajuda das função addUserToList e a função copyUser. */
User *GetUserPrefix(hash_user h, KeyType k) {
	User *res = NULL;
    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];
        while (currentUser != NULL) {
            if (strcasecmp(currentUser->account_status, "active") == 0 && strncmp(currentUser->nome, k, strlen(k)) == 0) {
				User *copy = copyUser(currentUser);
				addUserToList(&res, copy);
            }
            currentUser = currentUser->next;
        }
    }
    return res;
}

/* A fução InsertTable calcula o indice da chave, com o auxilio da função Hash, e coloca o User na 
tabela Hash. Caso a posição calculada estiver vazia, o User é adicionado diretamente, caso contrário, 
é adicionado ao início da lista nessa posição. */
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


/* A função verifica com o auxilio da funçao RetriveUser se o User se encontra na hash, caso este 
se encontre, incrementa o número total de reservas e o gasto total do user, em seguida insere a reserva
ordenamente na lista ligada Q2. */
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
			q2->next = aux->q2;
			aux->q2 = q2;
		} else {
			prevQ2->next = q2;
			q2->next = currentQ2;
		}
	}
}


/* A função InsertVooUser segue a mesmo linha de pensamento que a função InsertReservaUser, inserindo os 
flights na lista ligada Q2, de forma ordenada. */
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
			q2->next = aux->q2;
			aux->q2 = q2;
		} else {
			prevQ2->next = q2;
			q2->next = currentQ2;
		}
	
	}
}

/*
int userNumber(hash_user h, char *argv){

	int totalUsers = 0;

	for(int i = 0; i<HASHSIZEUSER; i++){
		if(h[i]!=NULL){
			User* u = h[i];
			if(argv[1]==NULL){
				totalUsers ++;
			}
			
		}
	}
}*/

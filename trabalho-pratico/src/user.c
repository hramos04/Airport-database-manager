#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/user.h"
#include "../include/q2.h"

struct User {
    char *id;
    char *nome;
    char *email;
    char *phone;
    char *birth;
    char *sex;
    char *passport;
    char *country;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_status;
    int total_reservas;
    int total_voos;
    double total_gasto;
    struct User *next;
    struct Q2 *q2;
};


User *create_user(char *id, char *nome, char *email, char *phone, char *birth, char *sex, char *passport, char *country, char *address, char *account_creation, char *pay_method,char *account_status) {
    User *user = malloc(sizeof(struct User));

    user->id = strdup(id);
	user->nome = strdup(nome);
	user->email = strdup(email);
	user->phone = strdup(phone);
	user->birth = strdup(birth);
	user->sex = strdup(sex);
	user->passport = strdup(passport);
	user->country = strdup(country);
	user->address = strdup(address);
	user->account_creation = strdup(account_creation);
	user->pay_method = strdup(pay_method);
	user->account_status = strdup(account_status);

	user->total_reservas = 0;
	user->total_voos = 0;
	user->total_gasto = 0.0;
	user->next = NULL;
	user->q2 = NULL;

    return user;
}

char* userGetId(User *user){
	return strdup(user->id);
}

char* userGetNome(User *user){
	return strdup(user->nome);
}

char* userGetBirth(User *user){
	return strdup(user->birth);
}

char* userGetSex(User *user){
	return strdup(user->sex);
}

char* userGetPassport(User *user){
	return strdup(user->passport);
}

char* userGetCountry(User *user){
	return strdup(user->country);
}

char* userGetAccountStatus(User *user){
	return strdup(user->account_status);
}

int userGetTotalReservas(User *user){
	return user->total_reservas;
}

int userGetTotalVoos(User *user){
	return user->total_voos;
}

double userGetTotalGasto(User *user){
	return user->total_gasto;
}

User* userGetNext(User *user){
	return user->next;
}

void userSetNext(User *user, User *next){
	user->next = next;
}

Q2* userGetQ2(User *user){
	return user->q2;
}

void userSetQ2(User *user, Q2 *q2){
	user->q2 = q2;
}











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
		aux->total_gasto += getTotalGasto(q2);
		Q2 *currentQ2 = aux->q2;
		Q2 *prevQ2 = NULL;
		
		while (currentQ2 != NULL && strcmp(getData(currentQ2), getData(q2)) >= 0) {
			prevQ2 = currentQ2;
			currentQ2 = getNext(currentQ2);
		}

		if (prevQ2 == NULL) {
			setNext(q2,aux->q2);
			aux->q2 = q2;
		} else {
			setNext(prevQ2,q2);
			setNext(q2,currentQ2);
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
		
		while (currentQ2 != NULL && strcmp(getData(currentQ2), getData(q2)) >= 0) {
			prevQ2 = currentQ2;
			currentQ2 = getNext(currentQ2);
		}

		if (prevQ2 == NULL) {
			setNext(q2,aux->q2);
			aux->q2 = q2;
		} else {
			setNext(prevQ2,q2);
			setNext(q2,currentQ2);
		}
	}
}

/*
//////////////////////////usar esta função quando só aparece a pedir o ano 

int CountUsersByYear(hash_user h, int year) {
    int count = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            // Extraindo o ano da string de criação da conta
            int accountYear;
            sscanf(currentUser->account_creation, "%d", &accountYear);

            // Verificando se o ano coincide
            if (accountYear == year) {
                count++;
            }

            currentUser = currentUser->next;
        }
    }

    return count;
}



////Função que conta os usuários, mas que dá todos os meses

int CountUsersByMonth(hash_user h, int year, int month) {
    int userCount = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            // Extraindo o ano e o mês da string de criação da conta
            int accountYear, accountMonth;
            if (sscanf(currentUser->account_creation, "%d/%d", &accountYear, &accountMonth) == 2 && accountYear == year && accountMonth == month) {
                // Incrementando o contador para o mês correspondente
                userCount++;
            }

            currentUser = currentUser->next;
        }
    }

    // Retornando o resultado
    return userCount;
}

int CountUsersByDate(hash_user h, int year, int month, int day) {
    int userCount = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            // Extraindo o ano, mês e dia da string de criação da conta
            int accountYear, accountMonth, accountDay;
            if (sscanf(currentUser->account_creation, "%d/%d/%d", &accountYear, &accountMonth, &accountDay) == 3 &&
                accountYear == year && accountMonth == month && accountDay == day) {
                // Incrementando o contador para a data correspondente
                userCount++;
            }

            currentUser = currentUser->next;
        }
    }

    // Retornando o resultado
    return userCount;
}



// Função que retorna o número total de passageiros para um determinado ano
int SomaPassageirosPorAnoUnico(hash_user h, int ano) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            int viagensNoAno = 0;  // Contador de viagens do usuário no ano fornecido

            Q2 *q2 = currentUser->q2;

            while (q2 != NULL) {
                // Verificar se é um voo (tipo 2) e se é do ano desejado
                if (getTipo(q2) == 2) {
                    int anoVoo;
                    sscanf(getData(q2), "%d", &anoVoo);

                    if (anoVoo == ano) {
                        viagensNoAno += 1;
                        // Verificar se é a única viagem do usuário no ano
                        if (viagensNoAno == 1) {
                            // Incrementar o total de passageiros apenas uma vez por usuário
                            totalPassageiros += 1;  // Cada voo representa um passageiro
                        }
                    }
                }

                q2 = getNext(q2);
            }

            currentUser = currentUser->next;
        }
    }

    return totalPassageiros;
}

// Função que retorna o número total de passageiros para um determinado ano e mês
int SomaPassageirosPorAnoMesUnico(hash_user h, int ano, int mes) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            int viagensNoAnoMes = 0;  // Contador de viagens do usuário no ano e mês fornecidos

            Q2 *q2 = currentUser->q2;

            while (q2 != NULL) {
                // Verificar se é um voo (tipo 2) e se é do ano e mês desejados
                if (getTipo(q2) == 2) {
                    int anoVoo, mesVoo;
                    sscanf(getData(q2), "%d/%d", &anoVoo, &mesVoo);

                    if (anoVoo == ano && mesVoo == mes) {
                        viagensNoAnoMes += 1;
                        // Verificar se é a única viagem do usuário no ano e mês
                        if (viagensNoAnoMes == 1) {
                            // Incrementar o total de passageiros apenas uma vez por usuário
                            totalPassageiros += 1;  // Cada voo representa um passageiro
                        }
                    }
                }

                q2 = getNext(q2);
            }

            currentUser = currentUser->next;
        }
    }

    return totalPassageiros;
}

// Função que retorna o número total de passageiros para um determinado ano, mês e dia
int SomaPassageirosPorAnoMesDataUnica(hash_user h, int ano, int mes, int dia) {
    int totalPassageiros = 0;

    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            int viagensNaData = 0;  // Contador de viagens do usuário na data fornecida

            Q2 *q2 = currentUser->q2;

            while (q2 != NULL) {
                // Verificar se é um voo (tipo 2) e se é da data desejada
                if (getTipo(q2) == 2) {
                    int anoVoo, mesVoo, diaVoo;
                    sscanf(getData(q2), "%d/%d/%d", &anoVoo, &mesVoo, &diaVoo);

                    if (anoVoo == ano && mesVoo == mes && diaVoo == dia) {
                        viagensNaData += 1;
                        // Verificar se é a única viagem do usuário na data
                        if (viagensNaData == 1) {
                            // Incrementar o total de passageiros apenas uma vez por usuário
                            totalPassageiros += 1;  // Cada voo representa um passageiro
                        }
                    }
                }

                q2 = getNext(q2);
            }

            currentUser = currentUser->next;
        }
    }

    return totalPassageiros;
}

*/

// Função que imprime todos os voos de todos os usuários
void ImprimirTodosVoos(hash_user h) {
    for (int i = 0; i < HASHSIZEUSER; i++) {
        User *currentUser = h[i];

        while (currentUser != NULL) {
            printf("Voos do usuário %s:\n", currentUser->id);

            Q2 *q2 = currentUser->q2;

            while (q2 != NULL) {
                if (getTipo(q2) == 1) {
                    printf("   - ID do Voo: %s\n", getId(q2));
                    printf("     Data: %s\n", getData(q2));
                    printf("     Total Gasto: %.2f\n", getTotalGasto(q2));
                }

                q2 = getNext(q2);
            }

            currentUser = currentUser->next;
        }
    }
}


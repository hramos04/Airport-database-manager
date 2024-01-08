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
    return h % HASHSIZE;
}


/* Função que inicializa a tabela de hash User. */
void InitializeTable(hash_user h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que retorna o User pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
TreeNodeUser* RetrieveUser(hash_user h, KeyType k) {
    int i = Hash(k);
    TreeNodeUser *root = h[i];

    while (root != NULL) {
        int compare = strcmp(root->user->id, k);

        if (compare == 0) {
            return root;
        } else if (compare < 0) {
            root = root->right;
        } else {
            root = root->left;
        }
    }

    return NULL;
}

/* Função auxiliar que cria uma copia de um determinado User. */
User* copyUser(User *original) {
    User *copy = malloc(sizeof(User));
    copy->id = strdup(original->id);
    copy->nome = strdup(original->nome);
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
TreeNodeUser* insertNode(TreeNodeUser *root, User *user) {
    if (root == NULL) {
        TreeNodeUser *newNode = malloc(sizeof(TreeNodeUser));
        newNode->user = user;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    int compare = compareNamesWithoutHyphenIgnoreCase(user->nome, root->user->nome);
    if (compare < 0 || (compare == 0 && strcmp(user->id, root->user->id) < 0)) {
        root->left = insertNode(root->left, user);
    } else {
        root->right = insertNode(root->right, user);
    }

    return root;
}


/* Função auxiliar que percorre a tabela hash, procurando Users que apresentem o parametro 
"active" e cujos nomes começam com um determinado prefixo, retornando uma lista ordenada 
desses Users, com a ajuda das função addUserToList e a função copyUser. */
void getUsersWithPrefix(TreeNodeUser *root, const char *prefix, User **resultList) {
    if (root != NULL) {
        // Verifica se o usuário está ativo e o nome tem o prefixo
        if (strcasecmp(root->user->account_status, "active") == 0 && strncmp(root->user->nome, prefix, strlen(prefix)) == 0) {
            // Adiciona uma cópia do usuário à lista de resultados
            User *copy = copyUser(root->user);
            insertNode(root, copy);
        }

        // Recursivamente busca nos filhos
        getUsersWithPrefix(root->left, prefix, resultList);
        getUsersWithPrefix(root->right, prefix, resultList);
    }
}


User *GetUserPrefix(hash_user h, KeyType k) {
    User *res = NULL;
    int i = Hash(k);
    getUsersWithPrefix(h[i], k, &res);
    return res;
}

void InsertTable(hash_user h, KeyType k, User *user) {
    int i = Hash(k);
    h[i] = insertNode(h[i], user);
}

/*

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
*/













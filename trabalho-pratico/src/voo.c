#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"



/* Função de hash que converte uma chave num índice na tabela hash dos Aeroportos. */
int HashAeroportos(KeyType k) {
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


/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
int HashVoos(KeyType k) {
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


/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que inicializa a tabela de hash Voos. */
void InitializeTableVoos(hash_voos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Voo *RetrieveVoo(hash_voos h, KeyType k) {
    int i = HashVoos(k);
    Voo *root = h[i];

    while (root!=NULL){
        int compare = strcmp(k, root->id);
        if (compare == 0) {
            return root;
        } else if (compare < 0){
            return root->left;
        } else {
            return root->right;
        }
    }
    return NULL;
}



/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k) {
	 Voo *aux = RetrieveVoo(h, k);
	 if(aux) {
		 aux->total_passengers++;
		 return 1;
	 }
	 return 0;
}


/* Função que retorna o Aeroporto pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k) {
    int i = HashAeroportos(k);
    Aeroporto *root = h[i];

    while (root!=NULL){
        int compare = strcmp(k, root->name);
        if (compare == 0) {
            return root;
        } else if (compare < 0){
            return root->left;
        } else {
            return root->right;
        }
    }
    return NULL;
}

/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s) {
	for (int j = 0; s[j] != '\0'; j++) {
        s[j] = toupper(s[j]);
    }
}

// Função para inserir um novo VooResumo em uma árvore binária de VooResumo
VooResumo *InsertTreeNodeVooResumo(VooResumo *root, VooResumo *novo) {
    if (root == NULL) {
        // Encontrou o ponto de inserção
        novo->next_resumo = NULL;
        return novo;
    }

    int compare = strcmp(novo->schedule_departure_date, root->schedule_departure_date);
    if (compare < 0 || (compare == 0 && strcmp(novo->id, root->id) < 0)) {
        novo->next_resumo = root;
        return novo;
    } else {
        root->next_resumo = InsertTreeNodeVooResumo(root->next_resumo, novo);
        return root;
    }
}

// Função para inserir um novo Aeroporto em uma árvore binária de Aeroportos
Aeroporto *InsertTreeNodeAeroporto(Aeroporto *root, KeyType k, VooResumo *vooresumo) {
    if (root == NULL) {
        // Encontrou o ponto de inserção
        Aeroporto *novo = (Aeroporto *)malloc(sizeof(Aeroporto));
        novo->name = strdup(k);
        novo->next = NULL;
        novo->next_resumo = InsertTreeNodeVooResumo(NULL, vooresumo);
        return novo;
    }

    int compare = strcmp(k, root->name);
    if (compare < 0) {
        root->left = InsertTreeNodeAeroporto(root->left, k, vooresumo);
    } else if (compare > 0) {
        root->right = InsertTreeNodeAeroporto(root->right, k, vooresumo);
    } else {
        // Já existe um Aeroporto com o mesmo nome, insira na árvore de VooResumo
        root->next_resumo = InsertTreeNodeVooResumo(root->next_resumo, vooresumo);
    }

    return root;
}



/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo) {
    for (int j = 0; k[j] != '\0'; j++) {
        k[j] = toupper(k[j]);
    }

    int i = HashAeroportos(k);
    Aeroporto *root = h[i];

    convertToUpper(vooresumo->destination);

    if (!root) {
        // Se a árvore estiver vazia, cria um novo nó raiz
        Aeroporto *novo = (Aeroporto *)malloc(sizeof(Aeroporto));
        novo->name = strdup(k);
        novo->next = NULL;
        novo->next_resumo = InsertTreeNodeVooResumo(NULL, vooresumo);
        h[i] = novo;
    } else {
        // Caso contrário, insere na árvore existente
        Aeroporto *novoAeroporto = InsertTreeNodeAeroporto(root, k, vooresumo);
        if (root != novoAeroporto) {
            // Se o nó raiz foi alterado, atualiza-o
            h[i] = novoAeroporto;
        }
    }
}




/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo) {
    int i = HashVoos(k);
    Voo **root = &h[i];

    if (*root == NULL) {
        // Árvore está vazia, insere como raiz
        *root = (Voo *)malloc(sizeof(Voo));
        (*root)= voo;
        (*root)->left = (*root)->right = NULL;
    } else {
        Voo *current = *root;
        while (current != NULL) {
            int compare = strcmp(k, current->id);
            if (compare < 0) {
                if (current->left == NULL) {
                    current->left = (Voo *)malloc(sizeof(Voo));
                    current->left = voo;
                    current->left->left = current->left->right = NULL;
                    return;
                } else {
                    current = current->left;
                }
            } else if (compare > 0) {
                if (current->right == NULL) {
                    current->right = (Voo *)malloc(sizeof(Voo));
                    current->right = voo;
                    current->right->left = current->right->right = NULL;
                    return;
                } else {
                    current = current->right;
                }
            } else {
                return;
            }
        }
    }
}


/* Função que retorna uma lista de resumos de Voos entre as datas especificadas para um determinado 
Aeroporto. */
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date) {
    Aeroporto *aeroporto = RetrieveAeroporto(h, k);

	VooResumo *result = NULL;
    if (aeroporto) {
		VooResumo *vooResumo = aeroporto->next_resumo;

		while (vooResumo != NULL) {
			if (strcmp(vooResumo->schedule_departure_date, begin_date) >= 0 && strcmp(vooResumo->schedule_departure_date, end_date) <= 0) {
				// Cria uma cópia do VooResumo e adiciona à lista de resultados
				VooResumo *copia = malloc(sizeof(VooResumo));
				copia->id = strdup(vooResumo->id);
				copia->schedule_departure_date = strdup(vooResumo->schedule_departure_date);
				copia->destination = strdup(vooResumo->destination);
				copia->airline = strdup(vooResumo->airline);
				copia->plane_model = strdup(vooResumo->plane_model);
				copia->next_resumo = result;
				result = copia;
			}
			vooResumo = vooResumo->next_resumo;
		}	
	}
    return result;
}

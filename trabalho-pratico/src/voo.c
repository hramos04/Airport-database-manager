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
	 Voo *res;
	 for(res = h[i]; res; res = res->next_voo) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
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
	 Aeroporto *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->name, k) == 0) {
			 return res;
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


/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo) {
	for (int j = 0; k[j] != '\0'; j++) {
        k[j] = toupper(k[j]);
    }
    int i = HashAeroportos(k);
    Aeroporto *aux = RetrieveAeroporto(h, k);
    convertToUpper(vooresumo->destination);
    if(!aux) {
		Aeroporto *novo = (Aeroporto *)malloc(sizeof(Aeroporto));
		novo->name = strdup(k);
		novo->next = NULL;
		novo->next_resumo = vooresumo;
		aux = novo;
		if (h[i] == NULL) {
			h[i] = aux;
		}
		else {
			aux->next = h[i];
			h[i] = aux;
		}
	}
	else {
        VooResumo **atual = &aux->next_resumo;
        while (*atual != NULL &&
               (strcmp((*atual)->schedule_departure_date, vooresumo->schedule_departure_date) < 0 ||
                (strcmp((*atual)->schedule_departure_date, vooresumo->schedule_departure_date) == 0 &&
                 strcmp((*atual)->id, vooresumo->id) < 0))) {
            atual = &(*atual)->next_resumo;
        }

        vooresumo->next_resumo = *atual;
        *atual = vooresumo;
	}
}


/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo) {
    int i = HashVoos(k);
    if (h[i] == NULL) {
        h[i] = voo;
    }
    else {
        voo->next_voo = h[i];
        h[i] = voo;
    }
}

int diferencaEmSegundos(char *datetime1, char *datetime2) {
    struct {
        int ano, mes, dia, hora, minuto, segundo;
    } dt1, dt2;

    sscanf(datetime1, "%d/%d/%d %d:%d:%d", &dt1.ano, &dt1.mes, &dt1.dia, &dt1.hora, &dt1.minuto, &dt1.segundo);
    sscanf(datetime2, "%d/%d/%d %d:%d:%d", &dt2.ano, &dt2.mes, &dt2.dia, &dt2.hora, &dt2.minuto, &dt2.segundo);

    int diferenca = 0;

    diferenca += (dt1.ano - dt2.ano) * 31536000;
    diferenca += (dt1.mes - dt2.mes) * 2592000;
    diferenca += (dt1.dia - dt2.dia) * 86400;
    diferenca += (dt1.hora - dt2.hora) * 3600;
    diferenca += (dt1.minuto - dt2.minuto) * 60;
    diferenca += dt1.segundo - dt2.segundo;

    return diferenca < 0 ? -diferenca : diferenca;
}

void inserirAtraso(MedianaAeroporto *aeroporto, int valor) {
    if (aeroporto->tamanho == aeroporto->capacidade) {
        aeroporto->capacidade *= 2;
        aeroporto->atrasos = (int *)realloc(aeroporto->atrasos, aeroporto->capacidade * sizeof(int));
    }
    aeroporto->atrasos[aeroporto->tamanho++] = valor;
}

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h) {
	MedianaAeroporto *aux = NULL;
	int i = 0;
	for (i = 0; i < HASHSIZE; i++) {
		 if(h[i]) {
			 Aeroporto *ae = h[i];
			
			while(ae) {
				MedianaAeroporto *novo = (MedianaAeroporto*)malloc(sizeof(MedianaAeroporto));
				novo->name = strdup(ae->name);
				novo->tamanho = 0;
				novo->capacidade = 1;
				novo->mediana = 0;
				novo->next = NULL;
				novo->atrasos = (int *)malloc(sizeof(int));
				 
				 VooResumo *vooresumo = ae->next_resumo;
				 while(vooresumo) {
					 int segundos = diferencaEmSegundos(vooresumo->schedule_departure_date, vooresumo->real_departure_date);
					inserirAtraso(novo, segundos);
					 
					 vooresumo = vooresumo->next_resumo;
				 }
				 qsort(novo->atrasos, novo->tamanho, sizeof(int), comparar);
				 if(novo->tamanho % 2 != 0) {
					 novo->mediana = novo->atrasos[novo->tamanho/2];
				 }
				 else if(novo->tamanho >= 1) {
					 novo->mediana = (novo->atrasos[novo->tamanho/2] + novo->atrasos[(novo->tamanho/2) - 1]) / 2;
				 }
				 
				if (aux == NULL || (novo->mediana > aux->mediana) || (novo->mediana == aux->mediana && strcmp(novo->name, aux->name) < 0)) {
                    novo->next = aux;
                    aux = novo;
                }
                else {
                    MedianaAeroporto *temp = aux;
                    while (temp->next && (temp->next->mediana > novo->mediana || (temp->next->mediana == novo->mediana && strcmp(novo->name, temp->next->name) >= 0))) {
                        temp = temp->next;
                    }
                    novo->next = temp->next;
                    temp->next = novo;
                }
				 ae = ae->next;
				 
			 }
		 }
	}
	return aux;
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


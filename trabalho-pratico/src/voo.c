#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voo.h"

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

void InitializeTableAeroportos(hash_aeroportos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

void InitializeTableVoos(hash_voos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

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


int InsertPassengerVoo(hash_voos h, KeyType k) {
	 Voo *aux = RetrieveVoo(h, k);
	 if(aux) {
		 aux->total_passengers++;
		 return 1;
	 }
	 return 0;
}

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

void convertToUpper(char *s) {
	for (int j = 0; s[j] != '\0'; j++) {
        s[j] = toupper(s[j]);
    }
}

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
		// Insere ordenadamente na lista de voos baseada na data de partida
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

/*int InsertAeroportoPassenger(hash_aeroportos h, char *origin) {
	for (int j = 0; origin[j] != '\0'; j++) {
        origin[j] = toupper(origin[j]);
    }
    Aeroporto *aux = RetrieveAeroporto(h, origin);
    if(aux) {
		aux->total_passengers++;
		printf("Total: %s, %d\n",origin, aux->total_passengers);
		return 1;
	}
	return 0;
    
}*/


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


VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date) {
	int i = HashAeroportos(k);
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


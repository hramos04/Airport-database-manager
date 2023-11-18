#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*
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

void InsertTableAeroportos(hash_aeroportos h, KeyType k, Aeroporto *aeroporto, VooResumo *voo) {
    int i = HashAeroportos(k);
    
    Aeroporto *aux = RetrieveAeroporto(h, k);
    if(!aux) {
		Aeroporto*novo_aeroporto = (Aeroporto *)malloc(sizeof(Aeroporto));
		novo_aeroporto->name = strdup(k);
		novo_aeroporto->next = NULL;
		novo_aeroporto->next_resumo = NULL;
		aux = novo_aeroporto;
		if (h[i] == NULL) {
			h[i] = aux;
		}
		else {
			aux->next = h[i];
			h[i] = aux;
		}
	}
	voo->next_voo = aux->next_resumo;
	aux->next_resumo = voo;
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


void Printhash_voo(hash_voos h) {
	int total_voos = 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        Voo *aux = h[i];
        while(aux) {
			printf("ZZZ: %s\n",aux->id);
			aux = aux->next_voo;
			total_voos++;
		}
        
    }
    printf("Total Voos: %d\n",total_voos);
}

/*
void Printhash_aeroportos(hash_aeroportos h) {
	int total_aeroportos= 0;
    for (int i = 0; i < HASHSIZE; ++i) {
        Aeroporto *aux = h[i];
        while(aux) {
			printf("Aeroporto: %s\n", aux->name);
			aux = aux->next;
			total_aeroportos++;
		}
        
    }
    printf("Total Aeroportos: %d\n",total_aeroportos);
}
*/










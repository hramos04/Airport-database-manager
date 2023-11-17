#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"



int Hash( char *id) {
    int hash = 0;
    while (*id) {
        hash += *id;
        ++id;
    }
    return hash % HASHSIZE;
}

// Função para inicializar a tabela hash
void InitializeTable(hash_user h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

User *RetrieveUser(hash_user h, char *id) {
	 int i = Hash(id);
	 User *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->id, id) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

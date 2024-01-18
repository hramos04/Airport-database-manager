#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/q2.h"

struct Q2 {
	char *id;
	char *data;
	int tipo; //1-flight, 2-reserva
	double total_gasto;
	struct Q2 *next;
};


Q2 *create_q2(char *id, char *data, int tipo, double total_gasto) {
    Q2 *q2 = malloc(sizeof(struct Q2));

    q2->id = strdup(id);
    q2->data = strdup(data);
    q2->tipo = tipo;
    q2->total_gasto = total_gasto;
    q2->next = NULL;

    return q2;
}

Q2 *create_q2_without_totalGasto(char *id, char *data, int tipo) {
    Q2 *q2 = malloc(sizeof(struct Q2));

    q2->id = strdup(id);
    q2->data = strdup(data);
    q2->tipo = tipo;
    q2->total_gasto = 0.0;
    q2->next = NULL;

    return q2;
}


char* getId(Q2 *q2){ //já vi os memory leaks 
    return strdup(q2->id);
}

char* getData(Q2 *q2){
    return strdup(q2->data);
}

int getTipo(Q2 *q2){
    return q2->tipo;
}

double getTotalGasto(Q2 *q2){
    return q2->total_gasto;
}

Q2* getNext(Q2 *q2){
    return q2->next;
}

void setNext(Q2 *q2, Q2 *next){
    q2->next = next;
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

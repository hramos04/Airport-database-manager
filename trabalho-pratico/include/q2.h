#ifndef Q2_H
#define Q2_H


/* Definição de um nó da lista ligada Q2, onde é armazenada a informção de um flight, ou de uma 
reserva, dependedo do inteiro "tipo", que toma valor 1, caso se trate de um flight e toma valor 
2, caso se trate de uma reserva. */
typedef struct Q2 Q2;

Q2 *create_q2(char *id, char *data, int tipo, double total_gasto);

Q2 *create_q2_without_totalGasto(char *id, char *data, int tipo);

char* getId(Q2 *q2);

char* getData(Q2 *q2);

int getTipo(Q2 *q2);

double getTotalGasto(Q2 *q2);

Q2* getNext(Q2 *q2);

void setNext(Q2 *q2, Q2 *next);

void destroiQ2(Q2 *q2);

void freeQ2(Q2 *atual);

#endif

#ifndef Q2_H
#define Q2_H


/* Definição de um nó da lista ligada Q2, onde é armazenada a informção de um flight, ou de uma 
reserva, dependedo do inteiro "tipo", que toma valor 1, caso se trate de um flight e toma valor 
2, caso se trate de uma reserva. */
typedef struct Q2 Q2;


/* Cria e retorna uma estrutura Q2 com as informações fornecidas.*/
Q2 *create_q2(char *id, char *data, int tipo, double total_gasto);


/* Cria e retorna uma estrutura Q2 sem o valor total_gasto inicializado.*/
Q2 *create_q2_without_totalGasto(char *id, char *data, int tipo);


/*Obtém o identificador único associado à estrutura Q2.*/
char* getId(Q2 *q2);


/*Obtém a informação da data associada à estrutura Q2.*/
char* getData(Q2 *q2);


/*Obtém o tipo da estrutura Q2 (1 para voo, 2 para reserva).*/
int getTipo(Q2 *q2);


/*Obtém o valor total gasto associado à reserva ou ao voo.*/
double getTotalGasto(Q2 *q2);


/*Obtém o ponteiro para o próximo nó da lista ligada Q2.*/
Q2* getNext(Q2 *q2);


/*Define o ponteiro para o próximo nó da lista ligada Q2.*/
void setNext(Q2 *q2, Q2 *next);


/*Liberta a memória associada à estrutura Q2 e aos seus nós da lista ligada.*/
void destroiQ2(Q2 *q2);


/*Liberta a memória associada a um nó da lista ligada Q2.*/
void freeQ2(Q2 *atual);


#endif

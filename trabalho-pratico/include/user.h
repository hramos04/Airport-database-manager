#ifndef USER_H
#define USER_H
#define HASHSIZEUSER 81000 
#include "../include/q2.h"


/* Definição do KeyType*/
typedef char KeyType[300];



/* Definiçao da estrutura do User, que apresenta todos os dados relativos de cada user, 
sendo ainda acrescentado o número total de reservas, o número total de voos, o total gasto 
pelo mesmo e ainda apresentamos a lista ligada Q2 que armazena os dados relativos aos flights
e às reservas. */
typedef struct User User;


/* Definição da tabela hash que vai guardar todos os diferentes users. */
typedef User *hash_user[HASHSIZEUSER];

User *create_user(char *id, char *nome, char *email, char *phone, char *birth, char *sex, char *passport, char *country, char *address, char *account_creation, char *pay_method,char *account_status);

char* userGetId(User *user);

char* userGetNome(User *user);

char* userGetEmail(User *user);

char* userGetPhone(User *user);

char* userGetBirth(User *user);

char* userGetSex(User *user);

char* userGetPassport(User *user);

char* userGetCountry(User *user);

char* userGetAddress(User *user);

char* userGetAccountCreation(User *user);

char* userGetPayMethod(User *user);

char* userGetAccountStatus(User *user);

int userGetTotalReservas(User *user);

int userGetTotalVoos(User *user);

double userGetTotalGasto(User *user);

User* userGetNext(User *user);

void userSetNext(User *user, User *next);

Q2* userGetQ2(User *user);

void userSetQ2(User *user, Q2 *q2);

/* Função de hash que converte uma chave num índice na tabela hash. */
int Hash(KeyType k);

/* Função que inicializa a tabela de hash User. */
void InitializeTable(hash_user h);

void destroiTableUser(hash_user h);

void destroiQ2(Q2 *q2);




/* Função que retorna o User pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
User *RetrieveUser(hash_user h, KeyType k);


/* Função auxiliar que cria uma copia de um determinado User. */
User* copyUser(User *original);


/* Função auxiliar que compara duas strings, que neste caso em concreto, vai ser utilizada para
comparar nomes, com a particularidade de ignorar hífens nos mesmos. */
int compareNamesWithoutHyphenIgnoreCase(const char *str1, const char *str2);


/* Função auxiliar que adiciona um User a uma lista, que é ordenada pelos nomes dos diferentes
Users. */
void addUserToList(User **list, User *newUser);


/* Função auxiliar que percorre a tabela hash, procurando Users que apresentem o parametro 
"active" e cujos nomes começam com um determinado prefixo, retornando uma lista ordenada 
desses Users, com a ajuda das função addUserToList e a função copyUser. */
User *GetUserPrefix(hash_user h, KeyType k);


/* A fução InsertTable calcula o indice da chave, com o auxilio da função Hash, e coloca o User na 
tabela Hash. Caso a posição calculada estiver vazia, o User é adicionado diretamente, caso contrário, 
é adicionado ao início da lista nessa posição. */
void InsertTable(hash_user h, KeyType k, User *user);


/* A função verifica com o auxilio da funçao RetriveUser se o User se encontra na hash, caso este 
se encontre, incrementa o número total de reservas e o gasto total do user, em seguida insere a reserva
ordenamente na lista ligada Q2. */
void InsertReservaUser(hash_user h, KeyType k, Q2 *q2);


/* A função InsertVooUser segue a mesmo linha de pensamento que a função InsertReservaUser, inserindo os 
flights na lista ligada Q2, de forma ordenada. */
void InsertVooUser(hash_user h, KeyType k, Q2 *q2);


#endif


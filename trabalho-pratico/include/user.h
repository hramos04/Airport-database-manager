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


/*Função que cria e retorna uma estrutura User com as informações fornecidas.*/
User *create_user(char *id, char *nome, char *email, char *phone, char *birth, char *sex, char *passport, char *country, char *address, char *account_creation, char *pay_method,char *account_status);


/*Obtém o identificador único associado ao Utilizador.*/
char* userGetId(User *user);


/*Obtém o nome associado ao Utilizador.*/
char* userGetNome(User *user);


/*Obtém a data de nascimento associada ao Utilizador.*/
char* userGetBirth(User *user);


/*Obtém o gênero associado ao Utilizador.*/
char* userGetSex(User *user);


/*Obtém o número do passaporte associado ao Utilizador.*/
char* userGetPassport(User *user);


/*Obtém o país de origem associado ao Utilizador.*/
char* userGetCountry(User *user);


/* Obtém o status da conta associado ao Utilizador.*/
char* userGetAccountStatus(User *user);


/*Obtém o número total de reservas associado ao Utilizador.*/
int userGetTotalReservas(User *user);


/*Obtém o número total de voos associado ao Utilizador.*/
int userGetTotalVoos(User *user);


/*Obtém o valor total gasto associado ao Utilizador.*/
double userGetTotalGasto(User *user);


/*Obtém o ponteiro para o próximo nó da tabela hash de usuários.*/
User* userGetNext(User *user);


/*Define o ponteiro para o próximo nó da tabela hash de usuários.*/
void userSetNext(User *user, User *next);


/*Obtém o ponteiro para a lista ligada Q2 associada ao Utilizador.*/
Q2* userGetQ2(User *user);


/*Define o ponteiro para a lista ligada Q2 associada ao Utilizador.*/
void userSetQ2(User *user, Q2 *q2);


/* Função de hash que converte uma chave num índice na tabela hash. */
int Hash(KeyType k);


/* Função que inicializa a tabela de hash User. */
void InitializeTable(hash_user h);


/*Função que liberta a memória utilizada na hash dos users*/
void destroiTableUser(hash_user h);


/* Função que retorna o User pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
User *RetrieveUser(hash_user h, KeyType k);


/* Função auxiliar que cria uma copia de um determinado User. */
User* copyUser(User *original);


/*Função que liberta a memória alocada para um User*/
void freeUser(User *user);


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


/* Função que conta quantos utilizadores têm o ano de criação da conta igual ao ano fornecido. */
int CountUsersByYear(hash_user h, int year);


/* Função que conta o número de utilizadores que tem o determinado mês e o determinado ano de criaçao da conta. */
int CountUsersByMonth(hash_user h, int year, int month);


/* Função que conta o número de utilizadores que tem o determinado dia, o determinado mês e o determinado ano de 
criaçao da conta. */
int CountUsersByDate(hash_user h, int year, int month, int day);


/* Função que retorna o número total de passageiros para um determinado ano */
int SomaPassageirosPorAnoUnico(hash_user h, int ano);


/* Função que retorna o número total de passageiros para um determinado ano e mês*/
int SomaPassageirosPorAnoMesUnico(hash_user h, int ano, int mes);


/* Função que retorna o número total de passageiros para um determinado ano, mês e dia */
int SomaPassageirosPorAnoMesDataUnica(hash_user h, int ano, int mes, int dia);


#endif


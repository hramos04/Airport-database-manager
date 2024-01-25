#ifndef PARSING_H
#define PARSING_H
#include "../include/reserva.h"
#include "../include/user.h"
#include "../include/voo.h"
#include "../include/aeroporto.h"
#include "../include/hotel.h"



/* Função que verifica se um user se encontra na tabela de hash User, retornando 1 caso este se encontre,
ou retornando 0, caso o User não se encontre na tabela de hash. */ 
int valid_user(hash_user h, KeyType user_id);


/* Função que verifica se um flight se encontra na tabela de hash Voo, retornando 1 caso este se encontre,
ou retornando 0, caso o flight não se encontre na tabela de hash. */ 
int valid_flight(hash_voos h, KeyType flight_id);


/* Função que verifica se uma data cumpre todos os requisitos para ser considerada válida, retornando 1
caso esta seja válida, ou 0 caso contrário*/
int valid_date(char *string) ;


/* Função que verifica se uma data com horas cumpre todos os requisitos para ser considerada válida, 
retornando 1 caso esta seja válida, ou 0 caso contrário*/
int valid_date_hour(char *string);


/* Função que verifica se a data de nascimento é anterior à data de criação da conta, retornando 1 
caso seja verdade, ou 0 caso contrário. */
int compare_birth_with_account_cr(char *string1, char *string2);


/* Função que verifica se o email é válido, retornando 1 caso este seja válido, ou 0 caso contrário.*/
int valid_email(char *string);


/* Função que verifica se o código postal é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário. */
int valid_country_code(char *string);


/* Função que verifica se o status da conta é válido, retornando 1 caso esta seja válida, ou 
0 caso contrário. */
int valid_account_status(char *string);


/* Função que verifica se o método de pagamento é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário. */
int valid_pay_method(char *string);


/* Função que verifica se o nome do aeroporto é válido, retornando 1 caso este seja válido, ou 0 caso 
contrário. */
int valid_aeroport(char *string);


/* Função que verifica se o número de estrelas do hotel é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário. */
int valid_stars(char *string);

/*Função que verifica se o id fornecido é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário.*/
int valid_id(char *string);


/* Função que verifica se a data inicial é anterior à data final, retornando 1 caso seja verdade, 
ou 0 caso contrário. */
int compare_begin_with_end(char *string1, char *string2);


/* Função que verifica se um número de telefone é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário. */
int valid_phone_number(char *string);


/* Função que verifica se o sexo é válido, retornando 1 caso este seja válido, ou 0 caso contrário. */
int valid_sex(char *string);


/* Função que verifica se a data e hora de início são anterioes a data e hora final, retornando 1 
caso seja verdade, ou 0 caso contrário. */
int compare_datetime(char *datetime1, char *datetime2);


/* Função que verifica se o número de lugares de um avião é superior ao número de passageiros num 
determinado voo, retornando 1 caso seja verdade, ou 0 caso contrário. */
int valid_seat(char *string);


/* Função que calcula os dias ocorridos entre duas datas. */
int calcularDiasDatas(char *d1, char *d2);


/* Função que verifica se a opção de pequeno-almoço incluido/não incluido é válida, retornando 1 caso 
este seja válido, ou 0 caso contrário. */
int valid_breakfast(char *string);


/* Função que verifica se o imposto aplicado numa determinada cidade é válido, retornando 1 caso este 
seja válido, ou 0 caso contrário. */
int valid_tax(char *string);


/* Função que verifica se o preço por noite é válido, retornando 1 caso este seja válido, 
ou 0 caso contrário. */
int valid_price(char *string);


/* Função que calcula a diferença em segundos entre duas datas e horas. */
int calcularDiferencaSegundos(char *datetime1, char *datetime2);


/* Função que verifica se o rating é válido, retornando 1 caso este seja válido, ou 0 caso contrário. */
int valid_rating(char *string);


/* Função que verifica se determinados campos têm tamanho superior a zero, retornando 1 caso apresentem 
tamanho superior a zero, ou 0 caso contrário. */
int is_non_empty_string(char *string);


/* Função responsável por efetuar o parsing de todas as linhas do csv dos utilizadores e verificar se 
todos os campos são válidos, inserindo os valores na hash table. */
int process_users_csv(hash_user h, char *ficheiro);


/* Função responsável por efetuar o parsing de todas as linhas do csv das reservas e verificar se todos 
os campos são válidos, inserindo os valores nas hash tables. */
int process_reservas_csv(hash_user h, hash_hoteis h_hoteis, hash_reservas h_reservas, char *ficheiro);


/* Função responsável por efetuar o parsing de todas as linhas do csv dos passageiros e verificar 
se todos os campos são válidos, inserindo os valores nas hash tables. */
int process_passengers_csv(hash_user h, hash_voos h_voos, hash_aeroportos h_aeroportos, char *ficheiro);


/* Função responsável por efetuar o parsing de todas as linhas do csv dos voos e verificar se 
todos os campos são válidos, inserindo os valores nas hash tables. */
int process_voos_csv(hash_user h, hash_aeroportos h_aeroportos, hash_voos h_voos, char *ficheiro);


#endif  


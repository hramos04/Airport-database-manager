#ifndef HOTEL_H
#define HOTEL_H
#define HASHSIZERESERVA 41000 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];


/* Definiçao da estrutura ReservaResumo que apresenta um resumo dos dados relativos a uma reserva
num determinado hotel. */
typedef struct ReservaResumo ReservaResumo; 


/* Definiçao da estrutura do Hotel, que apresenta todos os dados relativos de cada hotel, 
como o seu id e a lista ligada reservaresumo, que apresenta um conjunto de informações de todas
as reservas que esse hotel tem. */
typedef struct Hotel Hotel;


/* Definição da tabela hash que vai guardar todos os diferentes Hoteis. */
typedef Hotel *hash_hoteis[HASHSIZERESERVA];


/*Função que cria e retorna uma estrutura ReservaResumo com as informações fornecidas*/
ReservaResumo *createReservaResumo(char *id, char *begin_date, char *end_date, char *user_id, char *price_per_night, double total_price, double rating);


/*Obtém o identificador único associado a uma determinada reserva nesse hotel.*/
char *reservaResumoGetId(ReservaResumo *reservaResumo);


/*Obtém a data de início da estadia associada a uma determinada reserva nesse hotel.*/
char *reservaResumoGetBeginDate(ReservaResumo *reservaResumo);


/*Obtém a data de término da estadia associada a uma determinada reserva nesse hotel.*/
char *reservaResumoGetEndDate(ReservaResumo *reservaResumo);


/*Obtém o identificador único do utilizador associado a uma determinada reserva nesse hotel.*/
char *reservaResumoGetUserId(ReservaResumo *reservaResumo);


/*Obtém o valor total gasto na reserva associada a esse hotel.*/
double reservaResumoGetTotalPrice(ReservaResumo *reservaResumo);


/*Obtém a avaliação dada pelo utilizador à estadia.*/
double reservaResumoGetRating(ReservaResumo *reservaResumo);


/*Obtém o apontador para a próxima reserva.*/
ReservaResumo *reservaResumoGetNext(ReservaResumo *reservaResumo);


/*Obtém o apontador para o próxima hotel da hash de Hoteis.*/
Hotel *hotelGetNext(Hotel *hotel);


/*Define o apontador para o próximo nó da estrutura Hotel.*/
void setNextHotel(Hotel *hotel, Hotel *next);


/*Obtém o apontador para a próxima reservaresumo associada a um Hotel.*/
ReservaResumo *hotelGetNextResumo(Hotel *hotel);


/*Define o apontador para a próxima reservaresumo associada a um Hotel.*/
void setNextHotelResumo(Hotel *hotel, Hotel *next);


/*Função de hash que converte uma chave num índice na tabela hash dos hoteis. */
int HashHoteis(KeyType k);


/*Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h);


/*A função verifica se um Hotel está presente na tabela hash. Caso não esteja, adiciona o novo Hotel 
à tabela. Posteriormente, insere ordenadamente um novo ReservaResumo associado a esse hotel, na 
lista ligada, vinculada a esse Hotel .*/
void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva);


/*Função que retorna o Hotel pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Hotel *RetrieveHotel(hash_hoteis h, KeyType k);


/*Liberta a memória alocada para a estrutura reservaResumo*/
void destroiReservaResumo(ReservaResumo *reservaResumo);


/*Liberta a memória alocada para a hash dos hoteis*/
void destroiTableHotel(hash_hoteis h);


/*Função que calcula a média das classificações de um hotel, percorrendo a lista ligada 
das reservas e somando os diferentes ratings em cada reserva. */
double GetRatingByHotel(hash_hoteis h, KeyType k);


/*Função que calcula o número de noites de uma reserva que ocorre entre duas datas considerando dias inteiros*/
int CalcularNumeroNoitesDias(char *start_date, char *end_date);


/*Função que calcula o número de noites de uma reserva, usando uma estimativa considerando meses */
int CalcularNumeroNoitesMes(char *start_date, char *end_date);


/*Função para obter o lucro de um hotel entre duas datas */
int GetLucro(hash_hoteis h, KeyType k, char *start_date, char *end_date);


#endif

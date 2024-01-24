#ifndef RESERVA_H
#define RESERVA_H
#define HASHSIZERESERVA 41000 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];


/* Definição da estrutura da Reserva, que apresenta todos os dados relativos a cada reserva, 
sendo ainda acrescentado o número total de noites, da respetiva reserva, e o total gasto . */
typedef struct Reserva Reserva;


/* Definição da tabela hash que vai guardar todas as diferentes Reservas. */
typedef Reserva *hash_reservas[HASHSIZERESERVA];

/*Função que cria e retorna uma estrutura Reserva com as informações fornecidas.*/
Reserva *createReserva(char *id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment, int total_noites, double total_gasto);


/*Função que liberta a memória alocada para uma Reserva*/
void freeReserva(Reserva *reserva);


/*Função de hash que converte uma chave num índice na tabela hash das reservas. */
int HashReservas(KeyType k);


/* Função que inicializa a tabela de hash reservas. */
void InitializeTableReservas(hash_reservas h);


/*Obtém o identificador único do hotel associado a uma reserva.*/
char *reservaGetHotelId(Reserva *reserva);


/*Obtém o nome do hotel associado a uma determinada reserva.*/
char *reservaGetHotelName(Reserva *reserva);


/*Obtém a classificação em estrelas do hotel associado a uma reserva.*/
char *reservaGetHotelStars(Reserva *reserva);


/*Obtém a data de início da estadia da reserva.*/
char *reservaGetBeginDate(Reserva *reserva);


/*Obtém a data de término da estadia da reserva.*/
char *reservaGetEndDate(Reserva *reserva);


/*Obtém a indicação se a reserva inclui pequeno almoço.*/
char *reservaGetIncludesBreakfast(Reserva *reserva);


/*Obtém o número total de noites da estadia da respetiva reserva.*/
int reservaGetTotalNoites(Reserva *reserva);


/*Obtém o valor total gasto na reserva.*/
double reservaGetTotalGasto(Reserva *reserva);


/*Obtém o ponteiro para o próximo nó da tabela hash de reservas*/
Reserva *reservaGetNext(Reserva *reserva);


/* Função que retorna a Reserva pretendida, caso esta se encontre na hash, através da sua respetiva 
chave. */
Reserva *RetrieveReserva(hash_reservas h, KeyType k);


/*Função que liberta a memória utilizada na hash das reservas. */
void destroiTableReserva(hash_reservas h);


/* A função insere uma Reserva na tabela hash das Reservas, caso a posição estiver livre coloca a 
Reserva nessa posição, caso a posição já estiver ocupada,diciona a reserva no início da lista 
encadeada dessa posição. */
void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva);


/* Função que conta o numero de reservas num determinado ano. */
int ContarReservasPorAno(hash_reservas h, int ano);


/* Função que conta o numero de reservas num determinado mes, de um determinado ano. */
int ContarReservasPorMes(hash_reservas h, int ano, int mes);


/* Função que conta o numero de reservas de um determinado dia, de um determinado mes, de um determinado ano. */
int ContarReservasPorData(hash_reservas h, int ano, int mes, int dia);


#endif


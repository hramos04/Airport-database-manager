#ifndef RESERVA_H
#define RESERVA_H
#define HASHSIZE 10050 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];


/* Definição da estrutura da Reserva, que apresenta todos os dados relativos a cada reserva, 
sendo ainda acrescentado o número total de noites, da respetiva reserva, e o total gasto . */
typedef struct Reserva {
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_tax;
    char *address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;
    int total_noites;
    double total_gasto;
    struct Reserva *next_reserva;
    struct Reserva *left;
    struct Reserva *right;
} Reserva;


/* Definição de um nó da lista ligada ReservaResumo, que apresenta dados filtrados e importantes 
de cada reserva. */
typedef struct ReservaResumo {
    char *id;
    char *begin_date;
    char *end_date;
    char *user_id;
    double total_price;
    double rating;
    struct ReservaResumo *next_resumo;
    struct ReservaResumo *left;
    struct ReservaResumo *right;
} ReservaResumo;


/* Definição da estrutura Hotel, que apresenta o respetivo id de cada hotel e a lista ligada 
ReservaResumo que apresenta então todas as reservas associadas ao determinado hotel. */
typedef struct Hotel {
	char *hotel_id;
	struct Hotel *next;
	struct ReservaResumo *next_resumo;
    struct Hotel *left;
    struct Hotel *right;
} Hotel;


/* Definição da tabela hash que vai guardar todos os diferentes Hoteis. */
typedef Hotel *hash_hoteis[HASHSIZE];


/* Definição da tabela hash que vai guardar todas as diferentes Reservas. */
typedef Reserva *hash_reservas[HASHSIZE];


/* Função de hash que converte uma chave num índice na tabela hash dos hoteis. */
int HashHoteis(KeyType k);


/* Função de hash que converte uma chave num índice na tabela hash das reservas. */
int HashReservas(KeyType k);


/* Função que inicializa a tabela de hash Hoteis. */
void InitializeTableHoteis(hash_hoteis h);


/* Função que inicializa a tabela de hash Reservas. */
void InitializeTableReservas(hash_reservas h);


/* Função que retorna a Reserva pretendida, caso esta se encontre na hash, através da sua respetiva 
chave. */
Reserva *RetrieveReserva(hash_reservas h, KeyType k);


/* Função que retorna o Hotel pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Hotel *RetrieveHotel(hash_hoteis h, KeyType k) ;


/* Função que calcula a média das classificações de um hotel, percorrendo a lista ligada 
das reservas e somando os diferentes ratings em cada reserva. */
double GetRatingByHotel(hash_hoteis h, KeyType k);


/* A função verifica se um Hotel está presente na tabela hash. Caso não esteja, adiciona o novo Hotel 
à tabela. Posteriormente, insere ordenadamente um novo ReservaResumo associado a esse hotel, na 
lista ligada, vinculada a esse Hotel .*/
void InsertTableHoteis(hash_hoteis h, KeyType k, ReservaResumo *reserva);


/* A função insere uma Reserva na tabela hash das Reservas, caso a posição estiver livre coloca a 
Reserva nessa posição, caso a posição já estiver ocupada,diciona a reserva no início da lista 
encadeada dessa posição. */
void InsertTableReservas(hash_reservas h, KeyType k, Reserva *reserva);

int HashHoteis(KeyType k);
int HashReservas(KeyType k);

#endif


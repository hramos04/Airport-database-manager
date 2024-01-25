#ifndef VOO_H
#define VOO_H
#define HASHSIZEVOO 10050 // Tamanho da tabela hash


/* Definição do KeyType*/
typedef char KeyType[300];


/* Definição da estrutura do Voo, que apresenta todos os dados relativos a cada voo, 
sendo ainda acrescentado o número total de passageiros, de cada voo, e o respetivo delay. */
typedef struct Voo Voo;

/*Definição da hash dos voos*/
typedef Voo *hash_voos[HASHSIZEVOO];
   

/*Função que cria e retorna uma estrutura Voo com as informações fornecidas.*/
Voo *createVoo(char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes, int delay);


/*Obtém o identificador único associado à estrutura Voo.*/
char *vooGetId(Voo *voo);


/*Obtém a companhia aérea responsável pelo voo.*/
char *vooGetAirline(Voo *voo);


/*Obtém o modelo da aeronave utilizada no voo.*/
char *vooGetPlaneModel(Voo *voo);


/*Obtém o aeroporto de origem do voo.*/
char *vooGetOrigin(Voo *voo);


/*Obtém o aeroporto de destino do voo.*/
char *vooGetDestination(Voo *voo);


/*Obtém a data programada para a partida do voo.*/
char *vooGetScheduleDepartureDate(Voo *voo);


/*Obtém a data programada para a chegada do voo. */
char *vooGetScheduleArrivalDate(Voo *voo);


/*Obtém o número total de passageiros no voo.*/
int vooGetTotalPassengers(Voo *voo);


/*Obtém o atraso em minutos do voo.*/
int vooGetDelay(Voo *voo);


/*Obtém o ponteiro para o próximo nó da lista ligada de voos.*/
Voo *vooGetNext(Voo *voo);


/*Define o ponteiro para o próximo nó da lista ligada de voos.*/
void setNextVoo(struct Voo *voo, struct Voo *next_voo);


/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
int HashVoos(KeyType k);


/* Função que inicializa a tabela de hash Voos. */
void InitializeTableVoos(hash_voos h);


/*Função que liberta a memória utilizada na hash dos voos*/
void destroiTableVoo(hash_voos h);


/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Voo *RetrieveVoo(hash_voos h, KeyType k);


/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k);


/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s);


/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo);


/* Função que retorna a soma do número total de passageiros para um voo num determinado ano*/
int SomaPassageirosPorAno(hash_voos h, int ano);


/* Função que retorna a soma do número total de passageiros para um voo num determinado mes, 
de um determinado ano*/
int SomaPassageirosPorMes(hash_voos h, int ano, int mes);


/* Função que retorna a soma do número total de passageiros para um voo num determinado dia, de um mes, 
de um determinado ano*/
int SomaPassageirosPorDia(hash_voos h, int ano, int mes, int dia);


/* Função que retorna o numero de voos num determinado ano*/
int SomaVoosPorAno(hash_voos h, int ano);


/* Função que retorna o numero de voos num determinado mes, de um determinado ano*/
int SomaVoosPorMes(hash_voos h, int ano, int mes);


/* Função que retorna o numero de voos de um determinado dia, num determinado mes, de um determinado ano*/
int SomaVoosPorDia(hash_voos h, int ano, int mes, int dia);


#endif


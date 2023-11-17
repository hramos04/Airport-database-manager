#ifndef USER_H
#define USER_H
#define HASHSIZE 10050 // Tamanho da tabela hash


//Estrutura da lista ligada 
typedef struct Reserva {
    char *reserva_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_tax;
    char *hotel_address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;
    struct Reserva *next;
} Reserva;

//Estrutura da lista ligada
typedef struct Voo {
    char *voo_id;
    struct Voo *next;
} Voo;



// Estrutura para representar usuários
typedef struct User {
    char *id;
    char *nome;
    char *email;
    char *phone_number;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_status;
    struct User *next;
    Reserva *reservas;
    Voo *voos;
} User;


// Tabela hash
typedef User *hash_user[HASHSIZE];


// Função hash
int Hash(char *id);


// Função para inicializar a tabela hash
void InitializeTable(hash_user h);


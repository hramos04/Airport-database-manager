#ifndef USER_H
#define USER_H
#define HASHSIZE 10050 // Tamanho da tabela hash

typedef char KeyType[300];


typedef struct Q2 {
	char *id;
	char *data;
	int tipo; //1-flight, 2-reserva
	double total_gasto;
	struct Q2 *next;
} Q2;

typedef struct User {
    char *id;
    char *nome;
    char *email;
    char *phone;
    char *birth;
    char *sex;
    char *passport;
    char *country;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_status;
    int total_reservas;
    int total_voos;
    double total_gasto;
    struct User *next;
    struct Q2 *q2;
} User;

// Tabela hash
typedef User *hash_user[HASHSIZE];

int Hash(KeyType k);
void InitializeTable(hash_user h);
void InsertTable(hash_user h, KeyType k, User *user);
void InsertReservaUser(hash_user h, KeyType k, Q2 *q2) ;
void InsertVooUser(hash_user h, KeyType k, Q2 *q2);
User *RetrieveUser(hash_user h, KeyType k);
User *GetUserPrefix(hash_user h, KeyType k);
User* copyUser(User *original);
int compareNamesWithoutHyphenIgnoreCase(const char *str1, const char *str2) ;
void addUserToList(User **list, User *newUser);
void Printhash_user(hash_user h);

#endif


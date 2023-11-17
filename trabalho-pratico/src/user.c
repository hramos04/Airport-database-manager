#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"



int Hash( char *id) {
    int hash = 0;
    while (*id) {
        hash += *id;
        ++id;
    }
    return hash % HASHSIZE;
}

// Função para inicializar a tabela hash
void InitializeTable(hash_user h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}

User *RetrieveUser(hash_user h, char *id) {
	 int i = Hash(id);
	 User *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->id, id) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

void InsertReserva(hash_user h, char *id, char *reserva_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *city_tax, char *hotel_address, char *begin_date, char *end_date, char *price_per_night, char *includes_breakfast, char *room_details, char *rating, char *comment) {
    // Encontrar o usuário na tabela hash
    User *user = RetrieveUser(h, id);

    if (user == NULL) {
        return;
    }

    // Criação da nova reserva
    Reserva *nova_reserva = (Reserva *)malloc(sizeof(Reserva));
    nova_reserva->reserva_id = strdup(reserva_id);
    nova_reserva->hotel_id = strdup(hotel_id);
    nova_reserva->hotel_name = strdup(hotel_name);
    nova_reserva->hotel_stars = strdup(hotel_stars);
    nova_reserva->city_tax = strdup(city_tax);
    nova_reserva->hotel_address = strdup(hotel_address);
    nova_reserva->begin_date = strdup(begin_date);
    nova_reserva->end_date = strdup(end_date);
    nova_reserva->price_per_night = strdup(price_per_night);
    nova_reserva->includes_breakfast = includes_breakfast;
    nova_reserva->room_details = strdup(room_details);
    nova_reserva->rating = strdup(rating);
    nova_reserva->comment = strdup(comment);
    nova_reserva->next = NULL;

    // Adiciona a nova reserva no início da lista de reservas do usuário
    nova_reserva->next = user->reservas;
    user->reservas = nova_reserva;
}

// Função para inserir na tabela hash usando encadeamento separado em caso de colisão
void InsertTable(hash_user h, char *id, char *nome, char *email, char *phone_number, char *birth_date, char *sex, char *passport, char *country_code, char *address, char *account_creation, char *pay_method, char *account_status) {
    
    
    
    int i = Hash(id);

    // Criar novo usuário
    User *novo_usuario = (User *)malloc(sizeof(User));
    novo_usuario->id = strdup(id);
    novo_usuario->nome = strdup(nome);
    novo_usuario->email = strdup(email);
    novo_usuario->phone_number = strdup(phone_number);
    novo_usuario->birth_date = strdup(birth_date);
    novo_usuario->sex = strdup(sex);
    novo_usuario->passport = strdup(passport);
    novo_usuario->country_code = strdup(country_code);
    novo_usuario->address = strdup(address);
    novo_usuario->account_creation = strdup(account_creation);
    novo_usuario->pay_method = strdup(pay_method);
    novo_usuario->account_status = strdup(account_status);
    novo_usuario->next = NULL;

    // Lidar com colisões usando encadeamento separado
    if (h[i] == NULL) {
        // Se o slot estiver vazio, apenas insira o novo usuário
        h[i] = novo_usuario;
        printf("inseri: %s\n",novo_usuario->id);
    } else {
        // Se houver colisão, adicione o novo usuário no início da lista
        novo_usuario->next = h[i];
        h[i] = novo_usuario;
    }
}


void InsertPassenger(hash_user h, char *id, char *voo_id) {
    // Encontrar o usuário na tabela hash
    User *user = RetrieveUser(h, id);

    if (user == NULL) {
        // Usuário não encontrado na tabela hash
        printf("Usuário com ID %s não encontrado.\n", id);
        return;
    }

    // Criação da nova reserva
    Voo *nova_voo = (Voo *)malloc(sizeof(Voo));
    nova_voo->voo_id = strdup(voo_id);
    nova_voo->next = NULL;

    // Adiciona a nova reserva no início da lista de reservas do usuário
    nova_voo->next = user->voos;
    user->voos = nova_voo;
}
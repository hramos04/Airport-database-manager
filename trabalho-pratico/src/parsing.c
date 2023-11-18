#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "parsing.h"
#define MAX_LINE_LENGTH 1024
#include "user.h"
#include "voo.h"

int valid_date(char *string) {
    if (strlen(string) != 10) {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            // Se estamos nas posições das barras, verifica se o caractere é '/'
            if (string[i] != '/') {
                return 0;
            }
        } else {
            // Se não estamos nas posições das barras, verifica se o caractere é um dígito entre '0' e '9'
            if (!isdigit(string[i])) {
                return 0;
            }
        }
    }

    int ano, mes, dia;
    if (sscanf(string, "%4d/%2d/%2d", &ano, &mes, &dia) != 3) {
        return 0;
    }
    if (ano < 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;
    }
    return 1;  // A data é válida
}

int valid_date_hour(char *string) {
    // Verifica se a string tem o comprimento correto
    if (strlen(string) != 19) {
        return 0; // A string não tem o comprimento correto
    }

    if (string[4] != '/' || string[7] != '/' || string[10] != ' ' ||
        string[13] != ':' || string[16] != ':') {
        return 0; // Formato incorreto
    }

    for (int i = 0; i < 19; i++) {
        if (i != 4 && i != 7 && i != 10 && i != 13 && i != 16) {
            if (!isdigit(string[i])) {
                return 0; // Caracteres inválidos
            }
        }
    }

    int year, month, day, hour, minute, second;
    if (sscanf(string, "%4d/%2d/%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0; // Falha ao analisar a data e hora
    }
    if (month < 1 || month > 12 || day < 1 || day > 31 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return 0; // Valores inválidos
    }

    return 1; // A data e hora são válidas
}

int compare_birth_with_account_cr(char *string1, char *string2) { //string1==birth e string2== account_creation
    // Verifica se as strings têm o comprimento correto
    if (strlen(string1) != 10 || strlen(string2) != 19) {
        return -1; // Comprimento incorreto
    }

    // Extrai os componentes do birth
    int year_date, month_date, day_date;
    if (sscanf(string1, "%4d/%2d/%2d", &year_date, &month_date, &day_date) != 3) {
        return -1; // Falha ao analisar o birth
    }

    // Extrai os componentes da acc
    int year_date_hour, month_date_hour, day_date_hour, hour_date_hour, minute_date_hour, second_date_hour;
    if (sscanf(string2, "%4d/%2d/%2d %2d:%2d:%2d", &year_date_hour, &month_date_hour, &day_date_hour, &hour_date_hour, &minute_date_hour, &second_date_hour) != 6) {
        return -1; // Falha ao analisar o acc
    }

    // Compara os anos, meses e dias
    if (year_date < year_date_hour || (year_date == year_date_hour && (month_date < month_date_hour || (month_date == month_date_hour && day_date < day_date_hour)))) {
        return 1; // birth é anterior a acc
    }

    return 0; // birth não é anterior a acc
}

int valid_email(char *string) {
    int i, atFound = 0, dotFound = 0;
    int usernameLength = 0, domainLength = 0, tldLength = 0;
    int emailLength = strlen(string);

    // Verificar se o email tem pelo menos tamanho 5 (x@y.z)
    if (emailLength < 5) {
        return 0;  // Formato inválido
    }

    for (i = 0; i < emailLength; i++) {
        if (string[i] == '@') {
            atFound = 1;
            usernameLength = i;  // Comprimento do <username>
        } else if (string[i] == '.') {
            dotFound = 1;
            domainLength = i - usernameLength - 1;  // Comprimento do <domain>
            tldLength = emailLength - i - 1;  // Comprimento do <TLD>
        }
    }

    // Verificar se '@' e '.' foram encontrados, e se os comprimentos são válidos
    if (atFound && dotFound && usernameLength > 0 && domainLength > 0 && tldLength >= 2) {
        return 1;  // Formato válido
    } else {
        return 0;  // Formato inválido
    }
}

int valid_country_code(char *string){
    if(strlen(string) == 2) return 1;
    else return 0;
}

int valid_account_status(char *string) {
    int result = (strcasecmp(string, "active") == 0 || strcasecmp(string, "inactive") == 0);
	
    return result;
}

int valid_pay_method(char *string) {
    return (strcasecmp(string, "CASH") == 0 || strcasecmp(string, "DEBIT_CARD") == 0 || strcasecmp(string, "CREDIT_CARD") == 0);
}

int valid_seat_numbers(char *string, char *string1){
    int n1 = atoi(string);
    int n2 = atoi(string1);

    // Verificar se o número de lugares é maior ou igual ao número de passageiros
    return n1 >= n2;
}

int valid_aeroport(char *string) {
    // Verificar se a string tem exatamente 3 caracteres
    if (strlen(string) != 3) {
        return 0;
    }

    // Verificar se todos os caracteres são letras
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isalpha(string[i])) {
            return 0;
        }
    }

    return 1;
}

int valid_stars(char *string) {
    if (isdigit(string[0]) && (string[0] >= '1' && string[0] <= '5') && string[1]=='\0') {
        return 1;
    }
    return 0;
}

int valid_id(char *string){
    if (string[0] == '\0') return 0;
    for (int i = 0; string[i] != '\0'; i++){
        if (isdigit(string[i]) == 0) return 0;
    }
    return 1;
}

int compare_begin_with_end(char *string1, char *string2) {
    // Verifica se as strings têm o comprimento correto
    if (strlen(string1) != 10 || strlen(string2) != 10) {
        return -1; // Comprimento incorreto
    }

    // Extrai os componentes do begin
    int year_date, month_date, day_date;
    if (sscanf(string1, "%4d/%2d/%2d", &year_date, &month_date, &day_date) != 3) {
        return -1; 
    }

    // Extrai os componentes do end
    int year_date_hour, month_date_hour, day_date_hour;
    if (sscanf(string2, "%4d/%2d/%2d", &year_date_hour, &month_date_hour, &day_date_hour) != 3) {
        return -1; 
    }

    // Compara os anos, meses e dias
    if (year_date < year_date_hour || (year_date == year_date_hour && (month_date < month_date_hour || (month_date == month_date_hour && day_date < day_date_hour)))) {
        return 1; // begin é anterior a end
    }

    return 0; // begin não é anterior a end
}

int valid_phone_number(char *string){
    if(string[0] == '\0') return 0;
    for (int i = 0; string[i] != '\0'; i++){
        if (isdigit(string[i]) == 0) return 0;
    }
    return 1;
}

///caso exista erros pode ser de esta só funcionar com maiusculas
int valid_sex(char *string){
    if (string[0] == 'M' || string[0] == 'F') return 1;
    else return 0;
}

int compare_datetime(char *datetime1, char *datetime2) {
    // Verifica se as strings têm o comprimento correto
    if (strlen(datetime1) != 19 || strlen(datetime2) != 19) {
        return 0; // Comprimento incorreto
    }

    // Extrai os componentes da data e hora
    int year_date, month_date, day_date, hour, minute, second;
    if (sscanf(datetime1, "%4d/%2d/%2d %2d:%2d:%2d", &year_date, &month_date, &day_date, &hour, &minute, &second) != 6) {
        return 0; // Formato inválido
    }

    // Extrai os componentes da outra data e hora
    int year_date_hour, month_date_hour, day_date_hour, hour_hour, minute_hour, second_hour;
    if (sscanf(datetime2, "%4d/%2d/%2d %2d:%2d:%2d", &year_date_hour, &month_date_hour, &day_date_hour, &hour_hour, &minute_hour, &second_hour) != 6) {
        return 0; // Formato inválido
    }

    // Compara os anos, meses, dias, horas, minutos e segundos
    if (year_date < year_date_hour || 
        (year_date == year_date_hour && (month_date < month_date_hour || 
        (month_date == month_date_hour && (day_date < day_date_hour || 
        (day_date == day_date_hour && (hour < hour_hour || 
        (hour == hour_hour && (minute < minute_hour || 
        (minute == minute_hour && second < second_hour)))))))))) {
        return 1; // datetime1 é anterior a datetime2
    }

    return 0; // datetime1 não é anterior a datetime2
}


int valid_aerport(char *string){
    if(strlen(string) == 3) return 1;
    else return 0;
}


int valid_seat(char *string) {
    for (size_t i = 0; i < strlen(string); ++i) {
        if (!isdigit((unsigned char)string[i])) {
            return 0; // Caracter não é um dígito
        }
    }

    return 1; // A string contém apenas números
}

int calcularDiasDatas(char *d1, char *d2) {
	int ano1, mes1,dia1;
	int ano2, mes2,dia2;
	sscanf(d1, "%d/%d/%d", &ano1, &mes1, &dia1);
	sscanf(d2, "%d/%d/%d", &ano2, &mes2, &dia2);
	
	return dia2 - dia1;
}



int valid_breakfast(char *string){
    if(!strcmp(string,"true") || !strcmp(string,"t") || !strcmp(string,"1") || !strcmp(string,"false") || !strcmp(string,"f") || !strcmp(string,"0") || !strcmp(string,"")) return 1;
    return 0;
}

int valid_tax(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return 0;  // Caracteres não numéricos encontrados
        }
    }
    int tax = atoi(string);  // Converte a string para um número inteiro
    // Verifica se o número é maior ou igual a 0
    if (tax >= 0) {
        return 1;
    }

    return 0;
}

int valid_price(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return 0;  // Caracteres não numéricos encontrados
        }
    }
    int tax = atoi(string);  // Converte a string para um número inteiro
    // Verifica se o número é maior ou igual a 0
    if (tax > 0) {
        return 1;
    }

    return 0;
}

int calcularDiferencaSegundos(char *datetime1, char *datetime2) {
    int ano1, mes1, dia1, hora1, minuto1, segundo1;
    int ano2, mes2, dia2, hora2, minuto2, segundo2;
    sscanf(datetime1, "%d/%d/%d %d:%d:%d", &ano1, &mes1, &dia1, &hora1, &minuto1, &segundo1);

    sscanf(datetime2, "%d/%d/%d %d:%d:%d", &ano2, &mes2, &dia2, &hora2, &minuto2, &segundo2);

    // Convertendo os componentes para segundos
    long segundos1 = ano1 * 31536000 + mes1 * 2592000 + dia1 * 86400 + hora1 * 3600 + minuto1 * 60 + segundo1;
    long segundos2 = ano2 * 31536000 + mes2 * 2592000 + dia2 * 86400 + hora2 * 3600 + minuto2 * 60 + segundo2;

    // Calculando a diferença em segundos
    int diferencaSegundos = abs((int)(segundos2 - segundos1));

    return diferencaSegundos;
}

int compare_date(){
    return 0;
}

int valid_rating(char *string) {
    if (string[0] == '\0') {
        return 1;  // String vazia
    }

    if (isdigit(string[0]) && (string[0] >= '1' && string[0] <= '5') && string[1] == '\0') {
        return 1;
    }

    return 0;
}

//para verificar que alguns critérios não são vazios 
int is_non_empty_string(char *string) {
    return (strlen(string) > 0);
}



void process_users_csv(hash_user h, char *ficheiro) {
	char linha[MAX_LINE_LENGTH];
	FILE *invalidFile = fopen("Resultados/users_errors.csv", "w");
	FILE *fp = fopen(ficheiro,"r");
	
	char id[MAX_LINE_LENGTH], nome[MAX_LINE_LENGTH], email[MAX_LINE_LENGTH], phone[MAX_LINE_LENGTH], birth[MAX_LINE_LENGTH], sex[MAX_LINE_LENGTH], passport[MAX_LINE_LENGTH];
	char country[MAX_LINE_LENGTH], address[MAX_LINE_LENGTH], account_creation[MAX_LINE_LENGTH], pay_method[MAX_LINE_LENGTH], account_status[MAX_LINE_LENGTH];
	while((fgets(linha, 1024, fp)) != NULL) {
		
		linha[strlen(linha)-1] = '\0';
		int i=0, j=0;
		for(j=0; linha[i] != ';'; i++, j++) {
			id[j] = linha[i];
		}
		id[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			nome[j] = linha[i];
		}
		nome[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			email[j] = linha[i];
		}
		email[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			phone[j] = linha[i];
		}
		phone[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			birth[j] = linha[i];
		}
		birth[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			sex[j] = linha[i];
		}
		sex[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			passport[j] = linha[i];
		}
		passport[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			country[j] = linha[i];
		}
		country[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			address[j] = linha[i];
		}
		address[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			account_creation[j] = linha[i];
		}
		account_creation[j] = '\0';
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			pay_method[j] = linha[i];
		}
		pay_method[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			account_status[j] = linha[i];
		}
		account_status[j-1] = '\0';
		
		
		if (valid_date_hour(account_creation) == 0 || valid_date(birth) == 0 || compare_birth_with_account_cr(birth,account_creation)==0 || valid_email(email)==0 ||is_non_empty_string(id) == 0 || is_non_empty_string(nome) == 0 || is_non_empty_string(phone) == 0 || is_non_empty_string(sex) == 0 ||valid_sex(sex)==0 ||is_non_empty_string(passport) == 0 || is_non_empty_string(address) == 0 || is_non_empty_string(pay_method) == 0 || valid_country_code(country) == 0 || valid_account_status(account_status) == 0) {
			if (invalidFile != NULL) {
				fprintf(invalidFile, "%s\n", linha);
			}
		}
		else {
			User *novo_user = (User *)malloc(sizeof(User));
			novo_user->id = strdup(id);
			novo_user->nome = strdup(nome);
			novo_user->email = strdup(email);
			novo_user->phone = strdup(phone);
			novo_user->birth = strdup(birth);
			novo_user->sex = strdup(sex);
			novo_user->passport = strdup(passport);
			novo_user->country = strdup(country);
			novo_user->address = strdup(address);
			novo_user->account_creation = strdup(account_creation);
			novo_user->pay_method = strdup(pay_method);
			novo_user->account_status = strdup(account_status);
			novo_user->total_reservas = 0;
			novo_user->total_voos = 0;
			novo_user->next = NULL;
			
			InsertTable(h, id, novo_user);
		}
	}
	
	
	fclose(invalidFile);
	fclose(fp);
}



void process_reservas_csv(hash_user h, hash_hoteis h_hoteis, hash_reservas h_reservas, char *ficheiro) {
	char linha[MAX_LINE_LENGTH];
	FILE *invalidFile = fopen("Resultados/reservations_errors.csv", "w");
	FILE *fp = fopen(ficheiro,"r");
	char id[MAX_LINE_LENGTH], user_id[MAX_LINE_LENGTH], hotel_id[MAX_LINE_LENGTH], hotel_name[MAX_LINE_LENGTH], hotel_stars[MAX_LINE_LENGTH], address[MAX_LINE_LENGTH], city_tax[MAX_LINE_LENGTH], begin_date[MAX_LINE_LENGTH];
	char end_date[MAX_LINE_LENGTH], price_per_night[MAX_LINE_LENGTH], includes_breakfast[MAX_LINE_LENGTH], room_details[MAX_LINE_LENGTH], rating[MAX_LINE_LENGTH], comment[MAX_LINE_LENGTH];
	char * endptr;
	while((fgets(linha, 1024, fp)) != NULL) {
		
		linha[strlen(linha)-1] = '\0';
		int i=0, j=0;
		for(j=0; linha[i] != ';'; i++, j++) {
			id[j] = linha[i];
		}
		id[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			user_id[j] = linha[i];
		}
		user_id[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			hotel_id[j] = linha[i];
		}
		hotel_id[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			hotel_name[j] = linha[i];
		}
		hotel_name[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			hotel_stars[j] = linha[i];
		}
		hotel_stars[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			city_tax[j] = linha[i];
		}
		city_tax[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			address[j] = linha[i];
		}
		address[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			begin_date[j] = linha[i];
		}
		begin_date[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			end_date[j] = linha[i];
		}
		end_date[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			price_per_night[j] = linha[i];
		}
		price_per_night[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			includes_breakfast[j] = linha[i];
		}
		includes_breakfast[j] = '\0';
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			room_details[j] = linha[i];
		}
		room_details[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			rating[j] = linha[i];
		}
		rating[j] = '\0';
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			comment[j] = linha[i];
		}
		comment[j-1] = '\0';
		
		  
		if(is_non_empty_string(id) == 0 || is_non_empty_string(user_id) == 0 || is_non_empty_string(hotel_id) == 0 ||is_non_empty_string(hotel_name) == 0 || is_non_empty_string(address) == 0 || valid_rating(rating)==0 || valid_breakfast(includes_breakfast)==0 || valid_price(price_per_night)==0 || valid_tax(city_tax)==0 || valid_stars(hotel_stars)==0 || compare_begin_with_end(begin_date, end_date)==0 || valid_date(begin_date)==0|| valid_date(end_date)==0){
			if (invalidFile != NULL) {
				fprintf(invalidFile, "%s\n", linha);
			}
		}
		else {
			User *k_user = RetrieveUser(h, user_id);
			if(k_user && (strcasecmp(k_user->account_status, "active") == 0 )) {
				Reserva *nova_reserva = (Reserva *)malloc(sizeof(Reserva));
			nova_reserva->id = strdup(id);
			nova_reserva->user_id = strdup(user_id);
			nova_reserva->hotel_id = strdup(hotel_id);
			nova_reserva->hotel_name = strdup(hotel_name);
			nova_reserva->hotel_stars = strdup(hotel_stars);
			nova_reserva->city_tax = strdup(city_tax);
			nova_reserva->address = strdup(address);
			nova_reserva->begin_date = strdup(begin_date);
			nova_reserva->end_date = strdup(end_date);
			nova_reserva->price_per_night = strdup(price_per_night);
			nova_reserva->includes_breakfast = strdup(includes_breakfast);
			nova_reserva->room_details = strdup(room_details);
			nova_reserva->rating = strdup(rating);
			nova_reserva->comment = strdup(comment);
			nova_reserva->total_noites = calcularDiasDatas(begin_date, end_date);
			nova_reserva->total_gasto =calcularDiasDatas(begin_date, end_date) * strtod(nova_reserva->price_per_night, &endptr) + ( ((calcularDiasDatas(begin_date, end_date) * strtod(nova_reserva->price_per_night, &endptr) / 100)* strtod(nova_reserva->city_tax, &endptr)));
			nova_reserva->next_reserva = NULL;
			
			ReservaResumo *novo_resumo = (ReservaResumo *)malloc(sizeof(ReservaResumo));
			novo_resumo->id = strdup(id);
			novo_resumo->begin_date = strdup(begin_date);
			novo_resumo->end_date = strdup(end_date);
			novo_resumo->user_id = strdup(user_id);
			novo_resumo->rating = strtod(rating, &endptr);
			novo_resumo->total_price = 1;
			novo_resumo->next_resumo = NULL;

			
			InsertTableHoteis(h_hoteis, hotel_id, novo_resumo);
			InsertTableReservas(h_reservas, id, nova_reserva);
			
			Q2 *q2 = (Q2*)malloc(sizeof(Q2));
			q2->data = strdup(begin_date);
			
			//printf("Total gasto: %f",calcularDiasDatas(begin_date, end_date) * strtod(nova_reserva->price_per_night, &endptr));
			q2->total_gasto = calcularDiasDatas(begin_date, end_date) * strtod(nova_reserva->price_per_night, &endptr) + ( ((calcularDiasDatas(begin_date, end_date) * strtod(nova_reserva->price_per_night, &endptr) / 100)* strtod(nova_reserva->city_tax, &endptr)));
			
			
			q2->tipo = 1; //reserva
			q2->id = strdup(id);
			
			InsertReservaUser(h, user_id, q2);
			}
			
			
			
		}
	}
	
	
	fclose(invalidFile);
	fclose(fp);
}


void process_passengers_csv(hash_user h, hash_voos h_voos, char *ficheiro) {
	char linha[MAX_LINE_LENGTH];
	FILE *invalidFile = fopen("Resultados/passengers_errors.csv", "w");
	FILE *fp = fopen(ficheiro,"r");
	char flight[MAX_LINE_LENGTH], user[MAX_LINE_LENGTH];
	
	while((fgets(linha, 1024, fp)) != NULL) {
		
		linha[strlen(linha)-1] = '\0';
		int i=0, j=0;
		for(j=0; linha[i] != ';'; i++, j++) {
			flight[j] = linha[i];
		}
		flight[j] = '\0';
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			user[j] = linha[i];
		}
		user[j-1] = '\0';
			Voo *voo = RetrieveVoo(h_voos, flight);
		  User *aux = RetrieveUser(h, user);
		  
		  if(voo && aux) {
			  //printf("%s, %s\n",aux->id, aux->account_status);
			Q2 *q2 = (Q2*)malloc(sizeof(Q2));
			q2->data = strdup(voo->schedule_departure_date);
			q2->tipo = 2; //voo
			q2->id = strdup(voo->id);
			InsertVooUser(h, user, q2);
			InsertPassengerVoo(h_voos, voo->id);
		  }
		
		  
		  
	}
	
	
	fclose(invalidFile);
	fclose(fp);
}

void process_voos_csv(hash_user h, hash_aeroportos h_aeroportos, hash_voos h_voos, char *ficheiro) {
	char linha[MAX_LINE_LENGTH];
	FILE *invalidFile = fopen("Resultados/flights_errors.csv", "w");
	FILE *fp = fopen(ficheiro,"r");
	char id[MAX_LINE_LENGTH], airline[MAX_LINE_LENGTH], plane_model[MAX_LINE_LENGTH], total_seats[MAX_LINE_LENGTH], origin[MAX_LINE_LENGTH], destination[MAX_LINE_LENGTH];
	char schedule_departure_date[MAX_LINE_LENGTH], schedule_arrival_date[MAX_LINE_LENGTH];
	char real_departure_date[MAX_LINE_LENGTH], real_arrival_date[MAX_LINE_LENGTH], pilot[MAX_LINE_LENGTH], copilot[MAX_LINE_LENGTH], notes[MAX_LINE_LENGTH];
	if(h_aeroportos && h) {
		
	}
	
	while((fgets(linha, 1024, fp)) != NULL) {
		
		linha[strlen(linha)-1] = '\0';
		int i=0, j=0;
		for(j=0; linha[i] != ';'; i++, j++) {
			id[j] = linha[i];
		}
		id[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			airline[j] = linha[i];
		}
		airline[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			plane_model[j] = linha[i];
		}
		plane_model[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			total_seats[j] = linha[i];
		}
		total_seats[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			origin[j] = linha[i];
		}
		origin[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			destination[j] = linha[i];
		}
		destination[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			schedule_departure_date[j] = linha[i];
		}
		schedule_departure_date[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			schedule_arrival_date[j] = linha[i];
		}
		schedule_arrival_date[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			real_departure_date[j] = linha[i];
		}
		real_departure_date[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			real_arrival_date[j] = linha[i];
		}
		real_arrival_date[j] = '\0';
		
		for(j=0, i++; linha[i] != ';'; i++, j++) {
			pilot[j] = linha[i];
		}
		pilot[j] = '\0';
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			copilot[j] = linha[i];
		}
		copilot[j] = '\0';
		
		
		for(j=0, i++; linha[i] != ';' && linha[i] != '\0'; i++, j++) {
			notes[j] = linha[i];
		}
		notes[j-1] = '\0';
		
		  if (is_non_empty_string(id)==0 || is_non_empty_string(airline)==0 || is_non_empty_string(plane_model)==0 || is_non_empty_string(pilot)==0 || is_non_empty_string(copilot)==0|| valid_aerport(origin)==0||valid_aerport(destination)==0|| compare_datetime(schedule_departure_date,schedule_arrival_date)==0 || compare_datetime(real_departure_date,real_arrival_date)==0 || valid_seat(total_seats)==0) {
			  if (invalidFile != NULL) {
				fprintf(invalidFile, "%s\n", linha);
				}
		  }
		  else {
			  Voo *novo_voo = (Voo *)malloc(sizeof(Voo));
			novo_voo->id = strdup(id);
			novo_voo->airline = strdup(airline);
			novo_voo->plane_model = strdup(plane_model);
			novo_voo->total_seats = strdup(total_seats);
			novo_voo->origin = strdup(origin);
			novo_voo->destination = strdup(destination);
			novo_voo->schedule_departure_date = strdup(schedule_departure_date);
			novo_voo->schedule_arrival_date = strdup(schedule_arrival_date);
			novo_voo->real_departure_date = strdup(real_departure_date);
			novo_voo->real_arrival_date = strdup(real_arrival_date);
			novo_voo->pilot = strdup(pilot);
			novo_voo->copilot = strdup(copilot);
			novo_voo->notes = strdup(notes);
			novo_voo->delay = calcularDiferencaSegundos(schedule_departure_date, real_departure_date);
			novo_voo->next_voo = NULL;
			
			/*ReservaResumo *novo_resumo = (ReservaResumo *)malloc(sizeof(ReservaResumo));
			novo_resumo->id = strdup(id);
			novo_resumo->begin_date = strdup(begin_date);
			novo_resumo->end_date = strdup(end_date);
			novo_resumo->user_id = strdup(user_id);
			novo_resumo->rating = strdup(rating);
			novo_resumo->total_price = 1;
			novo_resumo->next_resumo = NULL;*/
			//InsertTableHoteis(h_hoteis, hotel_id, novo_resumo);
			InsertTableVoos(h_voos, id, novo_voo);
			
			/*Q2 *q2 = (Q2*)malloc(sizeof(Q2));
			q2->data = strdup(schedule_departure_date);
			q2->tipo = 2; //voo
			q2->id = strdup(id);
			
			InsertVooUser(h, user_id, q2);*/
		  }
			
			

			
			
			
			
			
		//}
	}
	
	
	fclose(invalidFile);
	fclose(fp);
}





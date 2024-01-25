#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../include/user.h"
#include "../include/reserva.h"
#include "../include/voo.h"
#include "../include/interpreter.h"
#include "../include/aeroporto.h"
#include "../include/hotel.h"
#include "../include/queries.h"
#include <time.h>
#include <locale.h>
#define MAX_ARGS 5
#define MAX_LINE_LENGTH 1024


void remove_quotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        str[len - 1] = '\0';
    }
}


void split(char *line, int *arg_count, char *args[MAX_ARGS]) {
    *arg_count = 0;
    char buffer[MAX_LINE_LENGTH];
    int in_quotes = 0;
    size_t buffer_index = 0;

    for (size_t i = 0; i < strlen(line) && *arg_count < MAX_ARGS; i++) {
        char current_char = line[i];

        if (current_char == ' ' && !in_quotes) {
            buffer[buffer_index] = '\0';
            args[(*arg_count)++] = strdup(buffer);
            buffer_index = 0;
        } else if (current_char == '\"') {
            in_quotes = 1 - in_quotes;
        } else {
            buffer[buffer_index++] = current_char;
        }
    }
    if (buffer_index > 0 && *arg_count < MAX_ARGS) {
        buffer[buffer_index] = '\0';
        args[(*arg_count)++] = strdup(buffer);
    }
    for (int i = 0; i < *arg_count; i++) {
        remove_quotes(args[i]);
    }
}



int comando(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos, FILE *fp_output) {
    int argc = 0;
    char *args[MAX_ARGS];
    split(linha, &argc, args);
    int f = 0;
    int i = 0;
    while (isdigit(linha[i])) {
        i++;
    }

    if (linha[i] == 'F') {
        f = 1;
    }

    if (strcmp(args[0], "1") == 0 || strcmp(args[0], "1F") == 0) {
        q1(h_users, h_voos, h_reservas, args[1], f, fp_output);
    } else if (strcmp(args[0], "2") == 0 || strcmp(args[0], "2F") == 0) {
        q2(h_users, args, argc, f, fp_output);
    } else if (strcmp(args[0], "3") == 0 || strcmp(args[0], "3F") == 0) {
        q3(h_hoteis, args[1], f, fp_output);
    } else if (strcmp(args[0], "4") == 0 || strcmp(args[0], "4F") == 0) {
        q4(h_hoteis, args[1], f, fp_output);
    } else if (strcmp(args[0], "5") == 0 || strcmp(args[0], "5F") == 0) {
        q5(h_aeroportos, args[1], args[2], args[3], f, fp_output);
    } else if (strcmp(args[0], "6") == 0 || strcmp(args[0], "6F") == 0) {
        q6(h_voos, args[1], args[2], f, fp_output);
    } else if (strcmp(args[0], "7") == 0 || strcmp(args[0], "7F") == 0) {
        q7(h_aeroportos, atoi(args[1]), f, fp_output);
    } else if (strcmp(args[0], "8") == 0 || strcmp(args[0], "8F") == 0) {
        q8(h_hoteis, args[1], args[2], args[3], f, fp_output);
    } else if (strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) {
        q9(h_users, args[1], f, fp_output);
    } else if (strcmp(args[0], "10") == 0 || strcmp(args[0], "10F") == 0) {
        q10(h_users, h_voos, h_reservas, args, argc, f, fp_output);
    } 

    for (int i = 0; i < argc; i++) {
        free(args[i]);
    }

    return 1;
}

int comando_interativo(char *linha, hash_user h_users, hash_voos h_voos, hash_reservas h_reservas, hash_hoteis h_hoteis, hash_aeroportos h_aeroportos){
    int argc = 0;
    char *args[MAX_ARGS];
    split(linha, &argc, args);
    int f = 0;

	if (linha[1] != ' ' && linha[1] != 'F' && linha[1] != '0') return 1;

    if(chdir("Resultados/") != 0){
        printf("Error");
    }

    FILE *fp_output = fopen("comando_output.txt", "w");
    if (fp_output == NULL) {
        return 1;
    }

	if (strstr(linha, "F") != NULL) {
		f = 1;
	}
	if(strcmp(args[0], "1") == 0 || strcmp(args[0], "1F") == 0) {
		q1(h_users, h_voos, h_reservas, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "2") == 0 || strcmp(args[0], "2F") == 0) {
		q2(h_users, args, argc, f, fp_output);
	}
	else if(strcmp(args[0], "3") == 0 || strcmp(args[0], "3F") == 0) {
		q3(h_hoteis, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "4") == 0 || strcmp(args[0], "4F") == 0) {
		q4(h_hoteis, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "5") == 0 || strcmp(args[0], "5F") == 0) {
		q5(h_aeroportos, args[1], args[2], args[3], f, fp_output);
	}
	else if(strcmp(args[0], "6") == 0 || strcmp(args[0], "6F") == 0) {
		q6(h_voos, args[1], args[2], f, fp_output);
	}
	else if(strcmp(args[0], "7") == 0 || strcmp(args[0], "7F") == 0) {
		q7(h_aeroportos, atoi(args[1]), f, fp_output);
	}
	else if(strcmp(args[0], "8") == 0 || strcmp(args[0], "8F") == 0) {
		q8(h_hoteis, args[1], args[2],args[3], f, fp_output);
	}
	else if(strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) {
		q9(h_users, args[1], f, fp_output);
	}
	else if(strcmp(args[0], "10") == 0 || strcmp(args[0], "10F") == 0) {
		q10(h_users, h_voos, h_reservas, args, argc,f, fp_output);
	}

    if (chdir("trabalho-pratico") != 0){
		printf("Error");
	}
    fclose(fp_output);

    return 0;
}

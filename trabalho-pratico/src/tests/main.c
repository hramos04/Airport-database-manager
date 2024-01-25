#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/parsing.h"
#include "../include/user.h"
#include "../include/reserva.h"
#include "../include/voo.h"
#include "../include/aeroporto.h"
#include "../include/interpreter.h"
#include "../include/hotel.h"
#include "../include/interativo.h"
#include <locale.h>
#include "time.h"
#include <sys/resource.h>


int comparaOutputs(FILE *expected, FILE *real) {
    char linha1[1024];
    char linha2[1024];
    int i = 0;
    
    while (fgets(linha1, 1024, expected) != NULL && fgets(linha2, 1024, real) != NULL) {
        if (strcmp(linha1, linha2) != 0) {
            printf("Diferença na linha %d\n", i);
            printf("Esperado: %s\n", linha1);
            printf("Obtido: %s\n", linha2);
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2 && argv[0]) {
        return 0;
    }

    float total_q1 = 0.0;
    float total_q2 = 0.0;
    float total_q3 = 0.0;
    float total_q4 = 0.0;
    float total_q5 = 0.0;
    float total_q6 = 0.0;
    float total_q7 = 0.0;
    float total_q8 = 0.0;
    float total_q9 = 0.0;
    float total_q10 = 0.0;

    // Iniciar o relógio para medir o tempo de execução
    clock_t start, end, duration, start_users_p, end_users_p, start_users_proc,end_users_proc, start_reservas_p, end_reservas_p, start_reservas_proc, end_reservas_proc, start_voos_p, end_voos_p, start_voos_proc, end_voos_proc, start_passageiros_p, end_passageiros_p,start_passageiros_proc, end_passageiros_proc;
    double time_users, time_reservas, time_voos, time_passageiros;
    start = clock();

    setlocale(LC_COLLATE, "en_US.UTF-8");

    // Verificação do número de argumentos do input
    char linha[1024];

    // Inicialização das tabelas hash
    hash_user h_users;
    hash_hoteis h_hoteis;
    hash_reservas h_reservas;
    hash_voos h_voos;
    hash_aeroportos h_aeroportos;

    InitializeTable(h_users);
    InitializeTableHoteis(h_hoteis);
    InitializeTableReservas(h_reservas);
    InitializeTableVoos(h_voos);
    InitializeTableAeroportos(h_aeroportos);

    // Leitura e parsing dos ficheiros
    start_users_p = clock();
    char *csv_users = (char *)malloc(256);
    strcpy(csv_users, argv[1]);
    strcat(csv_users, "/users.csv");
    end_users_p = clock();

    start_reservas_p = clock();
    char *csv_reservas = (char *)malloc(256);
    strcpy(csv_reservas, argv[1]);
    strcat(csv_reservas, "/reservations.csv");
    end_reservas_p = clock();

    start_voos_p = clock();
    char *csv_voos = (char *)malloc(256);
    strcpy(csv_voos, argv[1]);
    strcat(csv_voos, "/flights.csv");
    end_voos_p = clock();

    start_passageiros_p = clock();
    char *csv_passengers = (char *)malloc(256);
    strcpy(csv_passengers, argv[1]);
    strcat(csv_passengers, "/passengers.csv");
    end_passageiros_p = clock();

    // Processamento dos arquivos e tempo
    start_users_proc = clock();
    int users = process_users_csv(h_users, csv_users);
    end_users_proc = clock();
    time_users = ((double) ((end_users_p - start_users_p) + (end_users_proc - start_users_proc))) / CLOCKS_PER_SEC;
    
    start_reservas_proc = clock();
    int reservas = process_reservas_csv(h_users, h_hoteis, h_reservas, csv_reservas);
    end_reservas_proc = clock();
    time_reservas = ((double) ((end_reservas_p - start_reservas_p) + (end_reservas_proc - start_reservas_proc))) / CLOCKS_PER_SEC;

    start_voos_proc = clock();
    int voos = process_voos_csv(h_users, h_aeroportos, h_voos, csv_voos);
    end_voos_proc = clock();
    time_voos = ((double) ((end_voos_p - start_voos_p) + (end_voos_proc - start_voos_proc))) / CLOCKS_PER_SEC;

    start_passageiros_proc = clock();
    int passageiros = process_passengers_csv(h_users, h_voos, h_aeroportos, csv_passengers);
    end_passageiros_proc = clock();
    time_passageiros = ((double) ((end_passageiros_p - start_passageiros_p) +(end_passageiros_proc - start_passageiros_proc))) / CLOCKS_PER_SEC;

    printf("Tempo de processamento users: %f segundos\n", time_users);      
    printf("Tempo de processamento reservas: %f segundos\n", time_reservas);    
    printf("Tempo de processamento voos: %f segundos\n", time_voos);            
    printf("Tempo de processamento passageiros: %f segundos\n", time_passageiros); 

    if (users || reservas || voos || passageiros) {
        printf("ERRO NO CAMINHO DOS FICHEIROS\n");
        return 1;
    }

    // Leitura do ficheiro de input e execução dos comandos
    FILE *fp = fopen(argv[2], "r");
    FILE *fp_output = NULL;
    int i = 1;
    char str_i[100];
    char destination_folder[1024];
    double total = 0.0;
    if (fp) {
        while (fgets(linha, sizeof(linha), fp) != NULL) {
            size_t comp = strlen(linha);
            if (comp > 0 && linha[comp - 1] == '\n') {
                linha[comp - 1] = '\0';
            }
            if (comp > 1 && linha[comp - 2] == '\r') {
                linha[comp - 2] = '\0';
            }

            char *args[MAX_ARGS];
            split(linha, &argc, args);

            // Path do ficheiro de saída
            strcpy(destination_folder, "Resultados/command");
            sprintf(str_i, "%d", i);
            strcat(destination_folder, str_i);
            strcat(destination_folder, "_output.txt");

            // Abertura do ficheiro de saída
            fp_output = fopen(destination_folder, "w");

            clock_t start, end;
            start = clock();
            // Execução dos comandos
            comando(linha, h_users, h_voos, h_reservas, h_hoteis, h_aeroportos, fp_output);

            end=clock();

            if (strcmp(args[0], "1") == 0 || strcmp(args[0], "1F") == 0) total_q1 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "2") == 0 || strcmp(args[0], "2F") == 0) total_q2 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "3") == 0 || strcmp(args[0], "3F") == 0) total_q3 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "4") == 0 || strcmp(args[0], "4F") == 0) total_q4 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "5") == 0 || strcmp(args[0], "5F") == 0) total_q5 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "6") == 0 || strcmp(args[0], "6F") == 0) total_q6 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "7") == 0 || strcmp(args[0], "7F") == 0) total_q7 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "8") == 0 || strcmp(args[0], "8F") == 0) total_q8 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "9") == 0 || strcmp(args[0], "9F") == 0) total_q9 += (float) (end-start) / CLOCKS_PER_SEC;
            if (strcmp(args[0], "10") == 0 || strcmp(args[0], "10F") == 0) total_q10 += (float) (end-start) / CLOCKS_PER_SEC;
            
            double duration = (double) (end-start) / CLOCKS_PER_SEC;
            total += duration;

            // Fechar o ficheiro
            fclose(fp_output);
            i++;
        }

        end = clock();
        printf("Tempo execucao query 1: %f segundos\n", total_q1);
        printf("Tempo execucao query 2: %f segundos\n", total_q2);
        printf("Tempo execucao query 3: %f segundos\n", total_q3);
        printf("Tempo execucao query 4: %f segundos\n", total_q4);
        printf("Tempo execucao query 5: %f segundos\n", total_q5);
        printf("Tempo execucao query 6: %f segundos\n", total_q6);
        printf("Tempo execucao query 7: %f segundos\n", total_q7);
        printf("Tempo execucao query 8: %f segundos\n", total_q8);
        printf("Tempo execucao query 9: %f segundos\n", total_q9);
        printf("Tempo execucao query 10: %f segundos\n", total_q10);
        printf("Tempo execucao todas as queries: %f segundos\n", total);
        fclose(fp);
    }


    
    // Medir memória máxima do programa
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memoria Utilizada: %ld KB\n", r_usage.ru_maxrss);

    // Terminar o relógio e calcular
    end = clock();

    duration = (end - start);

    printf("Ciclos execucao programa: %f ciclos\n", (float)duration);
    printf("Tempo execucao programa: %f segundos\n", (float)duration / CLOCKS_PER_SEC);

    free(csv_passengers);
    free(csv_reservas);
    free(csv_users);
    free(csv_voos);
    destroiTableUser(h_users);
    destroiTableVoo(h_voos);
    destroiTableAeroporto(h_aeroportos);
    destroiTableReserva(h_reservas);
    destroiTableHotel(h_hoteis);
    return 0;
}

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

int main(int argc, char *argv[]) {
    if (argc < 2 && argv[0]) {
        return 0;
    }

    // Iniciar o relógio para medir o tempo de execução
    clock_t start, end, duration;
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
    char *csv_users = (char *)malloc(256);
    strcpy(csv_users, argv[1]);
    strcat(csv_users, "/users.csv");

    char *csv_reservas = (char *)malloc(256);
    strcpy(csv_reservas, argv[1]);
    strcat(csv_reservas, "/reservations.csv");

    char *csv_voos = (char *)malloc(256);
    strcpy(csv_voos, argv[1]);
    strcat(csv_voos, "/flights.csv");

    char *csv_passengers = (char *)malloc(256);
    strcpy(csv_passengers, argv[1]);
    strcat(csv_passengers, "/passengers.csv");

    // Processamento dos arquivos
    int users = process_users_csv(h_users, csv_users);
    int reservas = process_reservas_csv(h_users, h_hoteis, h_reservas, csv_reservas);
    int voos = process_voos_csv(h_users, h_aeroportos, h_voos, csv_voos);
    int passageiros = process_passengers_csv(h_users, h_voos, h_aeroportos, csv_passengers);
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
    if (fp) {
        while (fgets(linha, sizeof(linha), fp) != NULL) {
            size_t comp = strlen(linha);
            if (comp > 0 && linha[comp - 1] == '\n') {
                linha[comp - 1] = '\0';
            }
            if (comp > 1 && linha[comp - 2] == '\r') {
                linha[comp - 2] = '\0';
            }

            // Path do ficheiro de saída
            strcpy(destination_folder, "Resultados/command");
            sprintf(str_i, "%d", i);
            strcat(destination_folder, str_i);
            strcat(destination_folder, "_output.txt");

            // Abertura do ficheiro de saída
            fp_output = fopen(destination_folder, "w");

            // Execução dos comandos
            comando(linha, h_users, h_voos, h_reservas, h_hoteis, h_aeroportos, fp_output, 1);

            // Fechar o ficheiro
            fclose(fp_output);
            i++;
        }
        fclose(fp);
    }

    // Medir memória máxima do programa
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memoria Utilizada: %ld KB\n", r_usage.ru_maxrss);

    // Terminar o relógio e calcular
    end = clock();

    duration = (end - start);

    printf("Processor cycles taken: %f cycles\n", (float)duration);
    printf("Processor time taken: %f seconds\n", (float)duration / CLOCKS_PER_SEC);

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

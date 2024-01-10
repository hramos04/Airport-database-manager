#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"



/* Função de hash que converte uma chave num índice na tabela hash dos Aeroportos. */
int HashAeroportos(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZE;
}


/* Função de hash que converte uma chave num índice na tabela hash dos Voos. */
int HashVoos(KeyType k) {
    int i = 0;
    unsigned h = 0;
    while (k[i] != '\0') {
        h += k[i];
        h += (h << 10);
        h ^= (h >> 6);
        i++;
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHSIZE;
}


/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que inicializa a tabela de hash Voos. */
void InitializeTableVoos(hash_voos h) {
    int i;
    for (i = 0; i < HASHSIZE; ++i)
        h[i] = NULL;
}


/* Função que retorna o Voo pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Voo *RetrieveVoo(hash_voos h, KeyType k) {
	 int i = HashVoos(k);
	 Voo *res;
	 for(res = h[i]; res; res = res->next_voo) {
		 if(strcmp(res->id, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}


/* Função auxiliar que incrementa o número total de passageiros, caso o voo exista na tabela hash dos
voos*/
int InsertPassengerVoo(hash_voos h, KeyType k) {
	 Voo *aux = RetrieveVoo(h, k);
	 if(aux) {
		 aux->total_passengers++;
		 return 1;
	 }
	 return 0;
}


/* Função que retorna o Aeroporto pretendido, caso este se encontre na hash, através da sua respetiva 
chave. */
Aeroporto *RetrieveAeroporto(hash_aeroportos h, KeyType k) {
	 int i = HashAeroportos(k);
	 Aeroporto *res;
	 for(res = h[i]; res; res = res->next) {
		 if(strcmp(res->name, k) == 0) {
			 return res;
		 }
	 }
	 return NULL;
}

/* Função para incrementar o número total de passageiros na lista ligada VooResumo de um Aeroporto */
int InsertPassengerVooResumo(hash_aeroportos h_aeroportos, KeyType voo_id) {
    for (int i = 0; i < HASHSIZE; i++) {
        Aeroporto *aeroporto = h_aeroportos[i];

        while (aeroporto != NULL) {
            VooResumo *vooResumo = aeroporto->next_resumo;

            while (vooResumo != NULL) {
                // Verifica se o ID do voo corresponde ao desejado
                if (strcmp(vooResumo->id, voo_id) == 0) {
                    vooResumo->total_passengers++;
                    return 1;  // Operação bem-sucedida
                }

                vooResumo = vooResumo->next_resumo;
            }

            aeroporto = aeroporto->next;
        }
    }

    return 0;  // Falha ao encontrar o voo na lista ligada do Aeroporto
}


/* Função auxiliar que converte todas as letras de uma string para maiúsculas. */
void convertToUpper(char *s) {
	for (int j = 0; s[j] != '\0'; j++) {
        s[j] = toupper(s[j]);
    }
}


/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo) {
	for (int j = 0; k[j] != '\0'; j++) {
        k[j] = toupper(k[j]);
    }
    int i = HashAeroportos(k);
    Aeroporto *aux = RetrieveAeroporto(h, k);
    convertToUpper(vooresumo->destination);
    if(!aux) {
		Aeroporto *novo = (Aeroporto *)malloc(sizeof(Aeroporto));
		novo->name = strdup(k);
		novo->next = NULL;
		novo->next_resumo = vooresumo;
		aux = novo;
		if (h[i] == NULL) {
			h[i] = aux;
		}
		else {
			aux->next = h[i];
			h[i] = aux;
		}
	}
	else {
        VooResumo **atual = &aux->next_resumo;
        while (*atual != NULL &&
               (strcmp((*atual)->schedule_departure_date, vooresumo->schedule_departure_date) < 0 ||
                (strcmp((*atual)->schedule_departure_date, vooresumo->schedule_departure_date) == 0 &&
                 strcmp((*atual)->id, vooresumo->id) < 0))) {
            atual = &(*atual)->next_resumo;
        }

        vooresumo->next_resumo = *atual;
        *atual = vooresumo;
	}
}






/* A função InsertTableVoos insere um novo Voo na tabela hash de Voos, caso a posição estiver livre 
coloca o Voo nessa posição, caso a posição já estiver ocupada, adiciona o voo no início da lista 
encadeada dessa posição. */
void InsertTableVoos(hash_voos h, KeyType k, Voo *voo) {
    int i = HashVoos(k);
    if (h[i] == NULL) {
        h[i] = voo;
    }
    else {
        voo->next_voo = h[i];
        h[i] = voo;
    }
}

int diferencaEmSegundos(char *datetime1, char *datetime2) {
    struct {
        int ano, mes, dia, hora, minuto, segundo;
    } dt1, dt2;

    sscanf(datetime1, "%d/%d/%d %d:%d:%d", &dt1.ano, &dt1.mes, &dt1.dia, &dt1.hora, &dt1.minuto, &dt1.segundo);
    sscanf(datetime2, "%d/%d/%d %d:%d:%d", &dt2.ano, &dt2.mes, &dt2.dia, &dt2.hora, &dt2.minuto, &dt2.segundo);

    int diferenca = 0;

    diferenca += (dt1.ano - dt2.ano) * 31536000;
    diferenca += (dt1.mes - dt2.mes) * 2592000;
    diferenca += (dt1.dia - dt2.dia) * 86400;
    diferenca += (dt1.hora - dt2.hora) * 3600;
    diferenca += (dt1.minuto - dt2.minuto) * 60;
    diferenca += dt1.segundo - dt2.segundo;

    return diferenca < 0 ? -diferenca : diferenca;
}

void inserirAtraso(MedianaAeroporto *aeroporto, int valor) {
    if (aeroporto->tamanho == aeroporto->capacidade) {
        aeroporto->capacidade *= 2;
        aeroporto->atrasos = (int *)realloc(aeroporto->atrasos, aeroporto->capacidade * sizeof(int));
    }
    aeroporto->atrasos[aeroporto->tamanho++] = valor;
}

int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h) {
	MedianaAeroporto *aux = NULL;
	int i = 0;
	for (i = 0; i < HASHSIZE; i++) {
		 if(h[i]) {
			 Aeroporto *ae = h[i];
			
			while(ae) {
				MedianaAeroporto *novo = (MedianaAeroporto*)malloc(sizeof(MedianaAeroporto));
				novo->name = strdup(ae->name);
				novo->tamanho = 0;
				novo->capacidade = 1;
				novo->mediana = 0;
				novo->next = NULL;
				novo->atrasos = (int *)malloc(sizeof(int));
				 
				 VooResumo *vooresumo = ae->next_resumo;
				 while(vooresumo) {
					 int segundos = diferencaEmSegundos(vooresumo->schedule_departure_date, vooresumo->real_departure_date);
					inserirAtraso(novo, segundos);
					 
					 vooresumo = vooresumo->next_resumo;
				 }
				 qsort(novo->atrasos, novo->tamanho, sizeof(int), comparar);
				 if(novo->tamanho % 2 != 0) {
					 novo->mediana = novo->atrasos[novo->tamanho/2];
				 }
				 else if(novo->tamanho >= 1) {
					 novo->mediana = (novo->atrasos[novo->tamanho/2] + novo->atrasos[(novo->tamanho/2) - 1]) / 2;
				 }
				 
				if (aux == NULL || (novo->mediana > aux->mediana) || (novo->mediana == aux->mediana && strcmp(novo->name, aux->name) < 0)) {
                    novo->next = aux;
                    aux = novo;
                }
                else {
                    MedianaAeroporto *temp = aux;
                    while (temp->next && (temp->next->mediana > novo->mediana || (temp->next->mediana == novo->mediana && strcmp(novo->name, temp->next->name) >= 0))) {
                        temp = temp->next;
                    }
                    novo->next = temp->next;
                    temp->next = novo;
                }
				 ae = ae->next;
				 
			 }
		 }
	}
	return aux;
}

/* Função que retorna uma lista de resumos de Voos entre as datas especificadas para um determinado 
Aeroporto. */
VooResumo *GetVoosAeroportoEntreDatas(hash_aeroportos h, KeyType k, char *begin_date, char *end_date) {
    Aeroporto *aeroporto = RetrieveAeroporto(h, k);

	VooResumo *result = NULL;
    if (aeroporto) {
		VooResumo *vooResumo = aeroporto->next_resumo;

		while (vooResumo != NULL) {
			if (strcmp(vooResumo->schedule_departure_date, begin_date) >= 0 && strcmp(vooResumo->schedule_departure_date, end_date) <= 0) {
				// Cria uma cópia do VooResumo e adiciona à lista de resultados
				VooResumo *copia = malloc(sizeof(VooResumo));
				copia->id = strdup(vooResumo->id);
				copia->schedule_departure_date = strdup(vooResumo->schedule_departure_date);
				copia->destination = strdup(vooResumo->destination);
				copia->airline = strdup(vooResumo->airline);
				copia->plane_model = strdup(vooResumo->plane_model);
				copia->next_resumo = result;
				result = copia;
			}
			vooResumo = vooResumo->next_resumo;
		}	
	}
    return result;
}

// Função para dividir a lista e encontrar o pivô (usada no quicksort)
SomaPassageirosAno* dividir(SomaPassageirosAno* head, SomaPassageirosAno** pivot) {
    SomaPassageirosAno* slow = head;
    SomaPassageirosAno* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *pivot = slow->next;
    slow->next = NULL;

    return head;
}

// Função para  duas listas ordenadas
SomaPassageirosAno* mesclar(SomaPassageirosAno* lista1, SomaPassageirosAno* lista2) {
    if (lista1 == NULL) return lista2;
    if (lista2 == NULL) return lista1;

    if (lista1->totalPassageiros >= lista2->totalPassageiros) {
        lista1->next = mesclar(lista1->next, lista2);
        return lista1;
    } else {
        lista2->next = mesclar(lista1, lista2->next);
        return lista2;
    }
}

// Função principal do quicksort para listas ligadas
SomaPassageirosAno* quicksort(SomaPassageirosAno* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    SomaPassageirosAno* pivot = NULL;
    head = dividir(head, &pivot);

    head = quicksort(head);
    pivot = quicksort(pivot);

    return mesclar(head, pivot);
}

// Função para ordenar a lista ligada por total de passageiros decrescente
void ordenarListaDecrescente(SomaPassageirosAno** head) {
    *head = quicksort(*head);
}



SomaPassageirosAno *criarListaSomaPassageirosAno(hash_aeroportos h_aeroportos, int ano, int n) {
    SomaPassageirosAno *head = NULL;
    
    for (int i = 0; i < HASHSIZE; i++) {
        Aeroporto *aeroporto = h_aeroportos[i];
        
        while (aeroporto != NULL) {
            VooResumo *vooResumo = aeroporto->next_resumo;
            int totalPassageirosAeroporto = 0;
            
            // Somar passageiros para voos com origem no aeroporto
            while (vooResumo != NULL) {
                if (atoi(strtok(vooResumo->schedule_departure_date, "/")) == ano) {
                    totalPassageirosAeroporto += vooResumo->total_passengers;
                }
                vooResumo = vooResumo->next_resumo;
            }

            // Somar passageiros para voos com destino no aeroporto
            for (int j = 0; j < HASHSIZE; j++) {
                Aeroporto *origemAeroporto = h_aeroportos[j];
                
                while (origemAeroporto != NULL) {
                    VooResumo *vooResumoDestino = origemAeroporto->next_resumo;
                    
                    while (vooResumoDestino != NULL) {
                        if (atoi(strtok(vooResumoDestino->schedule_departure_date, "/")) == ano &&
                            strcmp(vooResumoDestino->destination, aeroporto->name) == 0) {
                            totalPassageirosAeroporto += vooResumoDestino->total_passengers;
                        }
                        vooResumoDestino = vooResumoDestino->next_resumo;
                    }

                    origemAeroporto = origemAeroporto->next;
                }
            }
            
            // Criar nó para a lista ligada de soma de passageiros por ano
            SomaPassageirosAno *novo = (SomaPassageirosAno *)malloc(sizeof(SomaPassageirosAno));
            novo->nomeAeroporto = strdup(aeroporto->name);
            novo->totalPassageiros = totalPassageirosAeroporto;
            novo->next = head;
            head = novo;
            
            aeroporto = aeroporto->next;
        }
    }

    // Ordenar a lista por total de passageiros decrescente
    ordenarListaDecrescente(&head);

    // Manter apenas as N primeiras posições
    SomaPassageirosAno *current = head;
    SomaPassageirosAno *prev = NULL;
    int count = 0;
    while (current != NULL && count < n) {
        prev = current;
        current = current->next;
        count++;
    }

    // Liberar os elementos além das N primeiras posições
    while (current != NULL) {
        SomaPassageirosAno *temp = current;
        current = current->next;
        free(temp->nomeAeroporto);
        free(temp);
    }

    // Atualizar o próximo do último elemento mantido para NULL
    if (prev != NULL) {
        prev->next = NULL;
    }

    return head;
}



// Função para libertar a memória da lista ligada SomaPassageirosAno
void liberarListaSomaPassageirosAno(SomaPassageirosAno *head) {
    SomaPassageirosAno *current = head;
    while (current != NULL) {
        SomaPassageirosAno *temp = current;
        current = current->next;
        free(temp->nomeAeroporto);
        free(temp);
    }
}

// Função para imprimir a lista ligada SomaPassageirosAno
void imprimirListaSomaPassageirosAno(SomaPassageirosAno *head) {
    SomaPassageirosAno *current = head;
    while (current != NULL) {
        printf("%s, %d\n", current->nomeAeroporto, current->totalPassageiros);
        current = current->next;
    }
}


/* Função auxiliar para obter o ano a partir de uma data no formato "YYYY/MM/DD HH:mm:ss" */
int getYearFromDatetime(char *datetime) {
    int year;
    sscanf(datetime, "%d", &year);
    return year;
}



/* Função para imprimir a tabela hash de aeroportos */
void PrintHashAeroportos(hash_aeroportos h_aeroportos) {
    for (int i = 0; i < HASHSIZE; i++) {
        Aeroporto *aeroporto = h_aeroportos[i];
        
        while (aeroporto != NULL) {
            printf("Aeroporto: %s\n", aeroporto->name);

            VooResumo *vooResumo = aeroporto->next_resumo;
            while (vooResumo != NULL) {
                printf("  - VooResumo ID: %s, Schedule Departure Date: %s, Real Departure Date: %s, Destination: %s, Airline: %s, Plane Model: %s, Total Passengers: %d\n",
                       vooResumo->id, vooResumo->schedule_departure_date, vooResumo->real_departure_date,
                       vooResumo->destination, vooResumo->airline, vooResumo->plane_model, vooResumo->total_passengers);

                vooResumo = vooResumo->next_resumo;
            }

            aeroporto = aeroporto->next;
        }
    }
}

/* Função para imprimir a tabela hash de voos */
void PrintHashVoos(hash_voos h_voos) {
    for (int i = 0; i < HASHSIZE; i++) {
        Voo *voo = h_voos[i];
        
        while (voo != NULL) {
            printf("Voo ID: %s\n", voo->id);
            printf("  - Airline: %s, Plane Model: %s, Total Seats: %s, Origin: %s, Destination: %s\n",
                   voo->airline, voo->plane_model, voo->total_seats, voo->origin, voo->destination);
            printf("  - Schedule Departure Date: %s, Schedule Arrival Date: %s\n", voo->schedule_departure_date, voo->schedule_arrival_date);
            printf("  - Real Departure Date: %s, Real Arrival Date: %s\n", voo->real_departure_date, voo->real_arrival_date);
            printf("  - Pilot: %s, Copilot: %s, Notes: %s\n", voo->pilot, voo->copilot, voo->notes);
            printf("  - Total Passengers: %d, Delay: %d\n", voo->total_passengers, voo->delay);

            voo = voo->next_voo;
        }
    }
}

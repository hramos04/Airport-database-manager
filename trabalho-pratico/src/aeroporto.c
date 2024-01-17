#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"
#include "../include/aeroporto.h"



struct Aeroporto {
	char *name;
	struct Aeroporto *next;
	struct VooResumo *next_resumo;
};

struct VooResumo {
    char *id;
    char *schedule_departure_date;
    char *real_departure_date;
    char *destination;
    char *airline;
    char *plane_model;
    int total_passengers;
    struct VooResumo *next_resumo;
};

struct AeroportoNode {
    char *nomeAeroporto;
    struct AeroportoNode *next;
};


// Estrutura para a lista de aeroportos
struct ListaAeroportos {
    AeroportoNode *head;
};


struct SomaPassageirosAno {
    char *nomeAeroporto;
    int totalPassageiros;
    struct SomaPassageirosAno *next;
};

struct MedianaAeroporto {
	char *name;
	int *atrasos;
	int tamanho;
    int capacidade;
    int mediana;
    struct MedianaAeroporto *next;
};


Aeroporto *createAeroporto(char *name){
    Aeroporto *aeroporto = malloc(sizeof(struct Aeroporto));
    aeroporto->name = strdup(name);
    
    aeroporto->next = NULL;
    aeroporto->next_resumo = NULL;
    
    return aeroporto;
}


char *aeroportoGetName(Aeroporto *aeroporto){
    return strdup(aeroporto->name);
}

Aeroporto *aeroportoGetNext(Aeroporto *aeroporto){
    return aeroporto->next;
}

void setNextAeroporto(Aeroporto *aeroporto, Aeroporto *next){
    aeroporto->next = next;
}

VooResumo *aeroportoGetNextResumo(Aeroporto *aeroporto){
    return aeroporto->next_resumo;
}


void setNextVooResumoAeroporto(Aeroporto *aeroporto, VooResumo *next){
    aeroporto->next_resumo = next;
}


char *somaGetNomeAeroporto(SomaPassageirosAno *somaPassageirosAno){
    return strdup(somaPassageirosAno->nomeAeroporto);
}

int somaGetTotalPassageiros(SomaPassageirosAno *somaPassageirosAno){
    return somaPassageirosAno->totalPassageiros;
}

SomaPassageirosAno *somaGetNext (SomaPassageirosAno *somaPassageirosAno){
    return somaPassageirosAno->next;
}

char *medianaGetNome(MedianaAeroporto *medianaAeroporto){
    return strdup(medianaAeroporto->name);
}

int medianaGetMediana(MedianaAeroporto *medianaAeroporto){
    return medianaAeroporto->mediana;
}

MedianaAeroporto *medianaGetNext (MedianaAeroporto *medianaAeroporto){
    return medianaAeroporto->next;
}





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
    return h %HASHSIZEVOO;
}

/* Função que inicializa a tabela de hash Aeroportos. */
void InitializeTableAeroportos(hash_aeroportos h) {
    int i;
    for (i = 0; i <HASHSIZEVOO; ++i)
        h[i] = NULL;
}


void destroiTableAeroporto(hash_aeroportos h){
    	
        for(int i = 0; i<HASHSIZEVOO; i++){
            Aeroporto *atual = h[i];
            while(atual!=NULL){
                Aeroporto *position = atual;
                atual = atual->next;
                free(position->name);
                destroiVooResumo(position->next_resumo);
            }
        free(h[i]);
	}
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

/* Função que insere ordenadamente um novo resumo de voo, associado a um determinado Aeroporto, 
na lista ligada, no caso do Aeroporto não existir ainda na tabela, insere esse novo Aeroporto. */
void InsertTableAeroporto(hash_aeroportos h, KeyType k, VooResumo *vooresumo) {
	for (int j = 0; k[j] != '\0'; j++) {
        k[j] = toupper(k[j]);
    }
    int i = HashAeroportos(k);
    Aeroporto *aux = RetrieveAeroporto(h, k);
    convertToUpper(vooResumoGetDestination(vooresumo));
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


/* Função para imprimir a tabela hash de aeroportos */
void PrintHashAeroportos(hash_aeroportos h_aeroportos) {
    for (int i = 0; i <HASHSIZEVOO; i++) {
        Aeroporto *aeroporto = h_aeroportos[i];
        
        while (aeroporto != NULL) {
            printf("Aeroporto: %s\n", aeroporto->name);

        
            aeroporto = aeroporto->next;
        }
    }
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



int obterAno(const char *data) {
    // Esta função auxiliar irá extrair o ano da string de data
    // Certifique-se de adicionar a devida validação para a estrutura real do schedule_departure_date
    // Esta implementação assume que o ano está no formato "YYYY/MM/DD HH:MM:SS"
    char ano_str[5];
    strncpy(ano_str, data, 4);
    ano_str[4] = '\0';
    return atoi(ano_str);
}


// Função para criar uma lista de aeroportos vazia
ListaAeroportos *criarListaAeroportos(void) {
    ListaAeroportos *novaLista = (ListaAeroportos *)malloc(sizeof(ListaAeroportos));
    if (novaLista != NULL) {
        novaLista->head = NULL;
    }
    return novaLista;
}

// Função para adicionar um aeroporto à lista (não adiciona se já existir), ignorando maiúsculas e minúsculas
void adicionarAeroporto(ListaAeroportos *lista, const char *nomeAeroporto) {
    if (lista == NULL || nomeAeroporto == NULL) {
        return;
    }

    // Verificar se o aeroporto já existe na lista (ignorando maiúsculas e minúsculas)
    AeroportoNode *atual = lista->head;
    while (atual != NULL) {
        if (strcasecmp(atual->nomeAeroporto, nomeAeroporto) == 0) {
            return;  // Aeroporto já existe, não adiciona novamente
        }
        atual = atual->next;
    }

    // Criar novo nó para o aeroporto
    AeroportoNode *novoAeroporto = (AeroportoNode *)malloc(sizeof(AeroportoNode));
    if (novoAeroporto != NULL) {
        novoAeroporto->nomeAeroporto = (char *)malloc(strlen(nomeAeroporto) + 1);
        strcpy(novoAeroporto->nomeAeroporto, nomeAeroporto);
        novoAeroporto->next = lista->head;
        lista->head = novoAeroporto;
    }
}


// Função para destruir a lista de aeroportos e liberar a memória
void destruirListaAeroportos(ListaAeroportos *lista) {
    if (lista == NULL) {
        return;
    }

    AeroportoNode *atual = lista->head;
    while (atual != NULL) {
        AeroportoNode *proximo = atual->next;
        free(atual->nomeAeroporto);
        free(atual);
        atual = proximo;
    }

    free(lista);
}

SomaPassageirosAno *criarListaSomaPassageirosAno(hash_voos h, int ano, int n) {
    // Lista de aeroportos
    ListaAeroportos *listaAeroportos = criarListaAeroportos();

    // Percorrer a hash dos voos para coletar origens e destinos
    for (int i = 0; i <HASHSIZEVOO; i++) {
        Voo *voo = h[i];
        
        while (voo != NULL) {
            // Adicionar origem à lista de aeroportos
            adicionarAeroporto(listaAeroportos,vooGetOrigin(voo));
            
            // Adicionar destino à lista de aeroportos
            adicionarAeroporto(listaAeroportos, vooGetDestination(voo));
            
            voo = vooGetNext(voo);
        }
    }

    // Lista de passageiros por ano
    SomaPassageirosAno *head = NULL;

    // Percorrer a lista de aeroportos
    AeroportoNode *aeroportoNode = listaAeroportos->head;
    while (aeroportoNode != NULL) {
        // Inicializar total de passageiros para o aeroporto
        int totalPassageirosAeroporto = 0;

        // Somar passageiros para voos com origem ou destino no aeroporto no ano especificado
        for (int i = 0; i <HASHSIZEVOO; i++) {
            Voo *voo = h[i];

            while (voo != NULL) {
                int anoVoo = obterAno(vooGetScheduleDepartureDate(voo));

                if (anoVoo == ano && (strcasecmp(vooGetOrigin(voo), aeroportoNode->nomeAeroporto) == 0 ||
                                      strcasecmp(vooGetDestination(voo), aeroportoNode->nomeAeroporto) == 0)) {
                    totalPassageirosAeroporto += vooGetTotalPassengers(voo);
                }

                voo = vooGetNext(voo);
            }
        }

        // Criar nó para a lista ligada de soma de passageiros por ano
        SomaPassageirosAno *novo = (SomaPassageirosAno *)malloc(sizeof(SomaPassageirosAno));
        novo->nomeAeroporto = (char *)malloc(strlen(aeroportoNode->nomeAeroporto) + 1);
        strcpy(novo->nomeAeroporto, aeroportoNode->nomeAeroporto);
        novo->totalPassageiros = totalPassageirosAeroporto;
        novo->next = head;
        head = novo;

        // Avançar para o próximo aeroporto
        aeroportoNode = aeroportoNode->next;
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

    // Liberar a lista de aeroportos
    destruirListaAeroportos(listaAeroportos);

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


// Função para imprimir a lista de soma de passageiros por ano
void imprimirListaSomaPassageirosAno(SomaPassageirosAno *lista) {
    if (lista == NULL) {
        printf("Lista de soma de passageiros por ano vazia.\n");
        return;
    }

    printf("Lista de Soma de Passageiros por Ano:\n");

    SomaPassageirosAno *atual = lista;
    while (atual != NULL) {
        printf("Aeroporto: %s, Total de Passageiros: %d\n", atual->nomeAeroporto, atual->totalPassageiros);
        atual = atual->next;
    }
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


MedianaAeroporto * GetMedianaAeroportos(hash_aeroportos h) {
	MedianaAeroporto *aux = NULL;
	int i = 0;
	for (i = 0; i <HASHSIZEVOO; i++) {
		 if(h[i]) {
			 Aeroporto *ae = h[i];
			
			while(ae) {
				MedianaAeroporto *novo = (MedianaAeroporto*)malloc(sizeof(MedianaAeroporto));
				novo->name = aeroportoGetName(ae);
				novo->tamanho = 0;
				novo->capacidade = 1;
				novo->mediana = 0;
				novo->next = NULL;
				novo->atrasos = (int *)malloc(sizeof(int));
				 
				 VooResumo *vooresumo = aeroportoGetNextResumo(ae);
				 while(vooresumo) {
					 int segundos = diferencaEmSegundos(vooResumoGetScheduleDepartureDate(vooresumo), vooResumoGetRealDepartureDate(vooresumo));
					inserirAtraso(novo, segundos);
					 
					 vooresumo = vooResumoGetNext(vooresumo);
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
				 ae = aeroportoGetNext(ae);
				 
			 }
		 }
	}
	return aux;
}





VooResumo *createVooResumo(char *id, char *schedule_departure_date, char *real_departure_date, char *destination, char *airline, char *plane_model) {
    VooResumo *voo_resumo = malloc(sizeof(struct VooResumo));

    voo_resumo->id = strdup(id);
    voo_resumo->schedule_departure_date = strdup(schedule_departure_date);
    voo_resumo->real_departure_date = strdup(real_departure_date);
    voo_resumo->destination = strdup(destination);
    voo_resumo->airline = strdup(airline);
    voo_resumo->plane_model = strdup(plane_model);
    voo_resumo->total_passengers = 0;
    voo_resumo->next_resumo = NULL;

    return voo_resumo;
}

char *vooResumoGetId(VooResumo *voo_resumo) {
    return strdup(voo_resumo->id);
}

char *vooResumoGetScheduleDepartureDate(VooResumo *voo_resumo) {
    return strdup(voo_resumo->schedule_departure_date);
}

char *vooResumoGetRealDepartureDate(VooResumo *voo_resumo) {
    return strdup(voo_resumo->real_departure_date);
}

char *vooResumoGetDestination(VooResumo *voo_resumo) {
    return strdup(voo_resumo->destination);
}

char *vooResumoGetAirline(VooResumo *voo_resumo) {
    return strdup(voo_resumo->airline);
}

char *vooResumoGetPlaneModel(VooResumo *voo_resumo) {
    return strdup(voo_resumo->plane_model);
}

int vooResumoGetTotalPassengers(VooResumo *voo_resumo) {
    return voo_resumo->total_passengers;
}

VooResumo *vooResumoGetNext(VooResumo *voo_resumo) {
    return voo_resumo->next_resumo;
}

void setNextVooResumo(struct VooResumo *voo_resumo, struct VooResumo *next_voo_resumo) {
    voo_resumo->next_resumo = next_voo_resumo;
}

void destroiVooResumo(VooResumo *vooResumo){

	while(vooResumo!=NULL){
		VooResumo *atual = vooResumo;
		vooResumo = vooResumo->next_resumo;
		free(atual->id);
		free(atual->schedule_departure_date);
        free(atual->real_departure_date);
		free(atual->destination);
        free(atual->airline);
        free(atual->plane_model);
        free(atual);
	}
	free(vooResumo);
}

/* Função para incrementar o número total de passageiros na lista ligada VooResumo de um Aeroporto */
int InsertPassengerVooResumo(hash_aeroportos h_aeroportos, KeyType voo_id) {
    for (int i = 0; i <HASHSIZEVOO; i++) {
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


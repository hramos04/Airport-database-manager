#ifndef CATALOG_VOO_H
#define CATALOG_VOO_H
#define HASHSIZEVOO 10050 // Tamanho da tabela hash

/* Definição do KeyType*/
typedef char KeyType[300];

typedef Voo *hash_voos[HASHSIZEVOO];

typedef struct Catalog_voo Catalog_voo;

#endif
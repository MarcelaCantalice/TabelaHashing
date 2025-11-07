#include <stdio.h>
#include <stdlib.h>

typedef struct hash{
    int qtd;
    int size;
    int **itens;
}Hash;

Hash* cria_hash(int size){
    Hash *ha = malloc(sizeof(Hash));
    if(ha != NULL){
        ha->size = size;
        ha->qtd = 0;
        ha->itens = malloc(size * sizeof(int*));
        if(ha->itens == NULL){
            free(ha);
            return NULL;
        }
        for(int i = 0; i < size; i++){
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

int insere_hash_semColisao(Hash *ha, int valor){
    if(ha == NULL || ha->qtd == ha->size)
        return 0;
    int pos = funcao_hash(valor, ha->size);
    if(ha->itens[pos] != NULL)
        return 0;
    int *novo = malloc(sizeof(int));
    if(novo == NULL)
        return 0;
    *novo = valor;
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

int busca_hash_semColisao(Hash *ha, int chave, int *out){
    if(ha == NULL)
        return 0;
    int pos = funcao_hash(chave, ha->size);
    if(ha->itens[pos] == NULL)
        return 0;
    *out = *(ha->itens[pos]);
    return 1;
}

int chaveDivisao(int chave, int size){
    return chave % size;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario {
    char username[15];
    int hashSenha;
    struct usuario *prox; 
} Usuario;

typedef struct {
    int tamanho;
    Usuario **tabela; 
} Hash;


int valorString(char *str){
    int i, valor = 7;
    int tam = strlen(str);
    for(i = 0; i < tam; i++)
        valor = 31 * valor + (int) str[i];
    return valor;
}

int chaveDivisao(int chave, int TABLE_SIZE) {
    return (chave % TABLE_SIZE);
}

int hashSenha(char *senha) {
    int hash = 0;
    for (int i = 0; senha[i] != '\0'; i++) {
        hash = (hash * 37 + senha[i]) % 100000;
    }
    return hash;
}

Hash* criaHash(int tamanho) {
    Hash *h = (Hash*) malloc(sizeof(Hash));
    if (h != NULL) {
        h->tamanho = tamanho;
        h->tabela = (Usuario**) malloc(tamanho * sizeof(Usuario*));
        if (h->tabela == NULL) {
            free(h);
            return NULL;
        }
        for (int i = 0; i < tamanho; i++)
            h->tabela[i] = NULL;
    }
    return h;
}

int insereHash(Hash *h, char *username, char *senha) {
    if (h == NULL) return 0;

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    if (novo == NULL) return 0;

    strcpy(novo->username, username);
    novo->hashSenha = hashSenha(senha);
    novo->prox = h->tabela[pos];
    h->tabela[pos] = novo;

    printf("Usuario '%s' cadastrado na posicao %d.\n", username, pos);
    return 1;
}

Usuario* buscaHash(Hash *h, char *username, char *senha) {
    if (h == NULL) return NULL;

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *atual = h->tabela[pos];
    int hashDigitado = hashSenha(senha);

    while (atual != NULL) {
        if (strcmp(atual->username, username) == 0 && atual->hashSenha == hashDigitado) {
            printf("Login bem-sucedido! Bem-vindo(a), %s!\n", username);
            return atual;
        }
        atual = atual->prox;
    }

    printf("Usuario ou senha incorretos.\n");
    return NULL;
}

int removeHash(Hash *h, char *username) {
    if (h == NULL) return 0;

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *atual = h->tabela[pos];
    Usuario *anterior = NULL;

    while (atual != NULL && strcmp(atual->username, username) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0; 

    if (anterior == NULL)
        h->tabela[pos] = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual);
    printf("Usuario '%s' removido com sucesso.\n", username);
    return 1;
}

void imprimeHash(Hash *h) {
    if (h == NULL) return;

    printf("\n----- TABELA HASH -----\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("[%d] -> ", i);
        Usuario *aux = h->tabela[i];
        while (aux != NULL) {
            printf("(%s, %d) -> ", aux->username, aux->hashSenha);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
    printf("------------------------\n");
}

void liberaHash(Hash *h) {
    if (h != NULL) {
        for (int i = 0; i < h->tamanho; i++) {
            Usuario *atual = h->tabela[i];
            while (atual != NULL) {
                Usuario *aux = atual->prox;
                free(atual);
                atual = aux;
            }
        }
        free(h->tabela);
        free(h);
    }
}

int main() {
    Hash *tabela = criaHash(7); 
    int opcao;
    char user[15], senha[10];

    do {
        printf("\n1 - Cadastrar usuario\n2 - Login\n3 - Remover usuario\n4 - Imprimir tabela\n0 - Sair\n> ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Username: ");
                fgets(user, 15, stdin); user[strcspn(user, "\n")] = '\0';
                printf("Senha: ");
                fgets(senha, 10, stdin); senha[strcspn(senha, "\n")] = '\0';
                insereHash(tabela, user, senha);
                break;

            case 2:
                printf("Username: ");
                fgets(user, 15, stdin); user[strcspn(user, "\n")] = '\0';
                printf("Senha: ");
                fgets(senha, 10, stdin); senha[strcspn(senha, "\n")] = '\0';
                buscaHash(tabela, user, senha);
                break;

            case 3:
                printf("Username: ");
                fgets(user, 15, stdin); user[strcspn(user, "\n")] = '\0';
                removeHash(tabela, user);
                break;

            case 4:
                imprimeHash(tabela);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberaHash(tabela);
    return 0;
}
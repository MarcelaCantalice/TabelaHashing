#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct usuario {
    char username[40];
    int hashSenha;
    struct usuario *prox;
} Usuario;

typedef struct {
    int tamanho;
    int numElementos;
    Usuario **tabela;
} Hash;


int valorString(char *str) {
    int i, valor = 7;
    int tam = strlen(str);
    for (i = 0; i < tam; i++) {
        
        valor = (valor % (INT_MAX / 31)) * 31 + (int)str[i];
    }
    return abs(valor);
}


int chaveDivisao(int chave, int TABLE_SIZE) {
    return (abs(chave) % TABLE_SIZE);
}


int hashSenha(char *senha) {
    int hash = 0;
    for (int i = 0; senha[i] != '\0'; i++) {
        hash = (hash * 37 + senha[i]) % 100000;
    }
    return abs(hash);
}


Hash* criaHash(int tamanho) {
    if (tamanho <= 0) {
        printf("Erro: Tamanho invalido para tabela hash.\n");
        return NULL;
    }

    Hash *h = malloc(sizeof(Hash));
    if (h == NULL) {
        printf("Erro: Falha ao alocar memoria para Hash.\n");
        return NULL;
    }

    h->tamanho = tamanho;
    h->numElementos = 0;
    h->tabela = malloc(tamanho * sizeof(Usuario*));
    
    if (h->tabela == NULL) {
        printf("Erro: Falha ao alocar memoria para tabela.\n");
        free(h);
        return NULL;
    }

    for (int i = 0; i < tamanho; i++) {
        h->tabela[i] = NULL;
    }

    return h;
}


int usuarioExiste(Hash *h, char *username) {
    if (h == NULL || username == NULL) return 0;

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *atual = h->tabela[pos];

    while (atual != NULL) {
        if (strcmp(atual->username, username) == 0) {
            return 1; 
        }
        atual = atual->prox;
    }

    return 0; 
}


int insereHash(Hash *h, char *username, char *senha) {
    if (h == NULL) {
        printf("Erro: Tabela hash nao inicializada.\n");
        return 0;
    }

    if (username == NULL || strlen(username) == 0) {
        printf("Erro: Username nao pode ser vazio.\n");
        return 0;
    }

    if (senha == NULL || strlen(senha) == 0) {
        printf("Erro: Senha nao pode ser vazia.\n");
        return 0;
    }

    
    if (usuarioExiste(h, username)) {
        printf("Erro: Usuario '%s' ja existe!\n", username);
        return 0;
    }

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *novo = malloc(sizeof(Usuario));
    
    if (novo == NULL) {
        printf("Erro: Falha ao alocar memoria para novo usuario.\n");
        return 0;
    }

    strcpy(novo->username, username);
    novo->hashSenha = hashSenha(senha);
    novo->prox = h->tabela[pos];
    h->tabela[pos] = novo;
    h->numElementos++;

    printf("Usuario '%s' cadastrado na posicao %d.\n", username, pos);
    return 1;
}


Usuario* buscaHash(Hash *h, char *username, char *senha) {
    if (h == NULL) {
        printf("Erro: Tabela hash nao inicializada.\n");
        return NULL;
    }

    if (username == NULL || strlen(username) == 0) {
        printf("Erro: Username nao pode ser vazio.\n");
        return NULL;
    }

    if (senha == NULL || strlen(senha) == 0) {
        printf("Erro: Senha nao pode ser vazia.\n");
        return NULL;
    }

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
    if (h == NULL) {
        printf("Erro: Tabela hash nao inicializada.\n");
        return 0;
    }

    if (username == NULL || strlen(username) == 0) {
        printf("Erro: Username nao pode ser vazio.\n");
        return 0;
    }

    int pos = chaveDivisao(valorString(username), h->tamanho);
    Usuario *atual = h->tabela[pos];
    Usuario *anterior = NULL;

    while (atual != NULL && strcmp(atual->username, username) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        h->tabela[pos] = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    h->numElementos--;
    printf("Usuario '%s' removido com sucesso.\n", username);
    return 1;
}


void imprimeHash(Hash *h) {
    if (h == NULL) {
        printf("Erro: Tabela hash nao inicializada.\n");
        return;
    }

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


void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    Hash *tabela = criaHash(7);
    if (tabela == NULL) {
        printf("Erro critico: Nao foi possivel criar a tabela hash.\n");
        return 1;
    }

    int opcao;
    char user[40], senha[50];

    do {
        printf("\n1 - Cadastrar usuario\n2 - Login\n3 - Remover usuario\n4 - Imprimir tabela\n0 - Sair\n> ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limpaBuffer();
            continue;
        }
        limpaBuffer();

        switch (opcao) {
            case 1:
                printf("Username: ");
                if (fgets(user, sizeof(user), stdin) != NULL) {
                    user[strcspn(user, "\n")] = '\0';
                }
                printf("Senha: ");
                if (fgets(senha, sizeof(senha), stdin) != NULL) {
                    senha[strcspn(senha, "\n")] = '\0';
                }
                insereHash(tabela, user, senha);
                break;

            case 2:
                printf("Username: ");
                if (fgets(user, sizeof(user), stdin) != NULL) {
                    user[strcspn(user, "\n")] = '\0';
                }
                printf("Senha: ");
                if (fgets(senha, sizeof(senha), stdin) != NULL) {
                    senha[strcspn(senha, "\n")] = '\0';
                }
                buscaHash(tabela, user, senha);
                break;

            case 3:
                printf("Username: ");
                if (fgets(user, sizeof(user), stdin) != NULL) {
                    user[strcspn(user, "\n")] = '\0';
                }
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ALFABETO 26

typedef struct Digital {
    struct Digital *letra[TAMANHO_ALFABETO];
    int fim_palavra; // 1 se é fim de palavra, 0 caso contrário
} digital;

digital *criando_arvore() {
    digital *node = (digital *)malloc(sizeof(digital));
    node->fim_palavra = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        node->letra[i] = NULL;
    }
    return node;
}

void inserir(digital *raiz, const char *nome) {
    digital *atual = raiz;
    for (int i = 0; nome[i] != '\0'; i++) {
        int index = nome[i] - 'a';
        if (index < 0 || index >= TAMANHO_ALFABETO) {
            printf("Caractere invalido: %c\n", nome[i]);
            return;
        }
        if (atual->letra[index] == NULL) {
            atual->letra[index] = criando_arvore();
        }
        atual = atual->letra[index];
    }
    atual->fim_palavra = 1;
}

int busca_palavra(digital *raiz, const char *nome) {
    digital *atual = raiz;
    for (int i = 0; nome[i] != '\0'; i++) {
        int index = nome[i] - 'a';
        if (index < 0 || index >= TAMANHO_ALFABETO) {
            return 0; // caractere invalido
        }
        if (atual->letra[index] == NULL) {
            return 0; // palavra nao encontrada
        }
        atual = atual->letra[index];
    }
    return atual->fim_palavra;
}

int busca_prefixo(digital *raiz, const char *prefixo) {
    digital *atual = raiz;
    for (int i = 0; prefixo[i] != '\0'; i++) {
        int index = prefixo[i] - 'a';
        if (index < 0 || index >= TAMANHO_ALFABETO) {
            return 0; // caractere invalido
        }
        if (atual->letra[index] == NULL) {
            return 0; // prefixo nao encontrado
        }
        atual = atual->letra[index];
    }
    return 1; // prefixo encontrado
}

int main() {
    digital *mae = criando_arvore();
    int menu = 0;
    char nome[100];

    do {
        printf("MENU:\n");
        printf("1) Inserir palavra\n");
        printf("2) Procurar palavra completa\n");
        printf("3) Procurar prefixo\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        getchar(); // consumir '\n' do scanf

        switch (menu) {
            case 1:
                printf("Digite a palavra para inserir (somente letras minusculas):\n");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // remove '\n'
                inserir(mae, nome);
                printf("Palavra inserida com sucesso.\n");
                break;
            case 2:
                printf("Digite a palavra para buscar (somente letras minusculas):\n");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                if (busca_palavra(mae, nome)) {
                    printf("PALAVRA ENCONTRADA: %s\n", nome);
                } else {
                    printf("PALAVRA NAO ENCONTRADA.\n");
                }
                break;
            case 3:
                printf("Digite o prefixo para buscar (somente letras minusculas):\n");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                if (busca_prefixo(mae, nome)) {
                    printf("Prefixo encontrado na Trie.\n");
                } else {
                    printf("Prefixo nao encontrado.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("\n");
    } while (menu != 0);

    // Aqui você pode implementar uma função para liberar a memória da Trie, se desejar.

    return 0;
}

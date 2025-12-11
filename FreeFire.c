#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int unidade;
} Item;

typedef struct {
    Item itens[MAX_ITENS];
    int quantidade;
} Mochila;

// Função de limpar buffer
void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para alocar memória para a mochila
void alocMemoria(Mochila **itensNaMochila) {
    *itensNaMochila = calloc(1, sizeof(Mochila));
    if (*itensNaMochila == NULL) {
        printf("Error: Falha ao alocar memória.\n");
        exit(1);
    }
}

// Função de listar itens
void listarItens(Mochila *itensNaMochila) {
    printf("\n=====================================================\n");
    printf("============== ITENS NA MOCHILA (%d/10) ==============\n", itensNaMochila->quantidade);
    printf("=====================================================\n");

    if (itensNaMochila->quantidade == 0) {
        printf("A mochila está vazia \n");
        return;
    }

    printf("         NOME          |     TIPO     |  QUANTIDADE  \n");
    printf("=====================================================\n");

    for (int i = 0; i < itensNaMochila->quantidade; i++) {
        printf("%-20s | %-12s | %5d\n",
            itensNaMochila->itens[i].nome,
            itensNaMochila->itens[i].tipo,
            itensNaMochila->itens[i].unidade
        );
    }
}

// Inserir item — versão corrigida, lendo direto no struct!
void inserirItem(Mochila *itensNaMochila) {

    if (itensNaMochila->quantidade == MAX_ITENS) {
        printf("ERRO: Mochila cheia! Não é possível inserir novo item.\n");
        return;
    }

    int index = itensNaMochila->quantidade;

    printf("=====================================================\n");
    printf("===============  ADICIONAR NOVO ITEM  ===============\n");
    printf("=====================================================\n");

    // NOME
    printf("Nome do item: ");
    fgets(itensNaMochila->itens[index].nome,
          sizeof(itensNaMochila->itens[index].nome),
          stdin);
    itensNaMochila->itens[index].nome[
        strcspn(itensNaMochila->itens[index].nome, "\n")
    ] = '\0';

    // TIPO
    printf("Tipo do item: ");
    fgets(itensNaMochila->itens[index].tipo,
          sizeof(itensNaMochila->itens[index].tipo),
          stdin);
    itensNaMochila->itens[index].tipo[
        strcspn(itensNaMochila->itens[index].tipo, "\n")
    ] = '\0';

    // QUANTIDADE
    printf("Quantidade: ");
    scanf("%d", &itensNaMochila->itens[index].unidade);
    cleanBuffer();

    itensNaMochila->quantidade++;

    printf("\nItem '%s' adicionado com sucesso!\n",
        itensNaMochila->itens[index].nome);

    listarItens(itensNaMochila);
}

// Remover item
void removerItem(Mochila *itensNaMochila) {
    char input[50];
    int pos = -1;

    printf("=====================================================\n");
    printf("==================  REMOVER ITEM  ==================\n");
    printf("=====================================================\n");
    printf("Digite o nome do item a ser removido: ");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; i < itensNaMochila->quantidade; i++) {
        if (strcmp(itensNaMochila->itens[i].nome, input) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("ERRO : ITEM '%s' NÃO ENCONTRADO NA LISTA \n", input);
        return;
    }

    for (int i = pos; i < itensNaMochila->quantidade - 1; i++) {
        itensNaMochila->itens[i] = itensNaMochila->itens[i + 1];
    }

    itensNaMochila->quantidade--;

    printf("Item removido com sucesso!\n");

    listarItens(itensNaMochila);
}

// Menu
void menu(Mochila *itensNaMochila) {
    int escolha;

    do {
        printf("\n=====================================================\n");
        printf("===== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA =====\n");
        printf("=====================================================\n");
        printf("Itens na Mochila: %d/10\n", itensNaMochila->quantidade);

        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar Itens na mochila\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------------------\n");
        printf("Escolha uma opção: ");

        scanf("%d", &escolha);
        cleanBuffer();

        switch (escolha) {
            case 1: inserirItem(itensNaMochila); break;
            case 2: removerItem(itensNaMochila); break;
            case 3: listarItens(itensNaMochila); break;
            case 0: printf("\nSaindo do jogo...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

    } while (escolha != 0);
}

int main() {
    Mochila *itensNaMochila = NULL;

    alocMemoria(&itensNaMochila);

    itensNaMochila->quantidade = 0;

    menu(itensNaMochila);

    free(itensNaMochila);

    return 0;
}

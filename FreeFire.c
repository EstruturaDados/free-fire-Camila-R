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

// Limpa buffer do teclado
void cleanBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Aloca memória para a mochila
void alocMemoria(Mochila **itensNaMochila){
    *itensNaMochila = calloc(1, sizeof(Mochila));
    if (*itensNaMochila == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        exit(1);
    }
}

// Função de listar itens (com colunas alinhadas)
void listarItens(Mochila *itensNaMochila){
    printf("\n=====================================================\n");
    printf("============== ITENS NA MOCHILA (%d/10) ==============\n", itensNaMochila->quantidade);
    printf("=====================================================\n");

    if (itensNaMochila->quantidade == 0){
        printf("A mochila está vazia.\n");
        return;
    }

    printf("%-20s | %-12s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < itensNaMochila->quantidade; i++){
        printf("%-20s | %-12s | %-10d\n",
            itensNaMochila->itens[i].nome,
            itensNaMochila->itens[i].tipo,
            itensNaMochila->itens[i].unidade
        );
    }

    printf("=====================================================\n");
}

// Função de buscar item na mochila
void buscarItemNaMochila(Mochila *itensNaMochila){

    char nomeItem[30];
    // int tamanho = sizeof(itensNaMochila) / sizeof(itensNaMochila[0]);
    int tamanho = itensNaMochila->quantidade;

    printf("=====================================================\n");
    printf("==============  BUSCAR ITEM NA MOCHILA ==============\n");
    printf("=====================================================\n");

    printf("Digite o nome do item a ser encontrado: ");
    fgets(nomeItem, sizeof(nomeItem), stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';

    // busca sequencial iterativa
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(itensNaMochila->itens[i].nome, nomeItem) == 0) {

            printf("==============  ITEM ENCONTRADO! ==============\n");
            printf("Nome: %-20s \nTipo: %-12s \nQuantidade: %-10d\n",
                itensNaMochila->itens[i].nome,
                itensNaMochila->itens[i].tipo,
                itensNaMochila->itens[i].unidade
            );
            printf("=====================================================\n");

            return i;
        }
    }
    printf("==============  ITEM NÃO ENCONTRADO! ==============\n");
    printf("O Item '%s' NÃO foi encontrado na mochila\n", nomeItem);
    printf("=====================================================\n");
    return -1;

}

// Função de inserir item (100% fgets, 0% strcpy)
void inserirItem(Mochila *itensNaMochila){
    if (itensNaMochila->quantidade == MAX_ITENS){
        printf("ERRO: Mochila cheia! Não é possível inserir novo item.\n");
        return;
    }

    int index = itensNaMochila->quantidade;

    printf("=====================================================\n");
    printf("===============  ADICIONAR NOVO ITEM  ===============\n");
    printf("=====================================================\n");

    printf("Nome do item: ");
    fgets(itensNaMochila->itens[index].nome,
          sizeof(itensNaMochila->itens[index].nome),
          stdin);
    itensNaMochila->itens[index].nome[
        strcspn(itensNaMochila->itens[index].nome, "\n")
    ] = '\0';

    printf("Tipo do item: ");
    fgets(itensNaMochila->itens[index].tipo,
          sizeof(itensNaMochila->itens[index].tipo),
          stdin);
    itensNaMochila->itens[index].tipo[
        strcspn(itensNaMochila->itens[index].tipo, "\n")
    ] = '\0';

    printf("Quantidade: ");
    scanf("%d", &itensNaMochila->itens[index].unidade);
    cleanBuffer();

    itensNaMochila->quantidade++;

    printf("Item '%s' adicionado com sucesso!\n",
        itensNaMochila->itens[index].nome);

    listarItens(itensNaMochila);
}

// Função de remover item
void removerItem(Mochila *itensNaMochila){
    if (itensNaMochila->quantidade == 0){
        printf("A mochila já está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("=====================================================\n");
    printf("==================  REMOVER ITEM  ==================\n");
    printf("=====================================================\n");

    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int pos = -1;

    for (int i = 0; i < itensNaMochila->quantidade; i++){
        if (strcmp(itensNaMochila->itens[i].nome, nomeRemover) == 0){
            pos = i;
            break;
        }
    }

    if (pos == -1){
        printf("ERRO: Item '%s' não encontrado.\n", nomeRemover);
        return;
    }

    for (int i = pos; i < itensNaMochila->quantidade - 1; i++){
        itensNaMochila->itens[i] = itensNaMochila->itens[i + 1];
    }

    itensNaMochila->quantidade--;

    printf("Item removido com sucesso!\n");
    listarItens(itensNaMochila);
}

// Menu principal
void menu(Mochila *itensNaMochila){
    int escolha;

    do {
        printf("\n=====================================================\n");
        printf("===== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA =====\n");
        printf("=====================================================\n");
        printf("Itens na Mochila: %d/10\n", itensNaMochila->quantidade);

        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item na mochila\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &escolha) != 1){
            printf("Entrada inválida! Digite um número.\n");
            cleanBuffer();
            continue;
        }

        cleanBuffer();

        switch (escolha){
            case 1: inserirItem(itensNaMochila); break;
            case 2: removerItem(itensNaMochila); break;
            case 3: listarItens(itensNaMochila); break;
            case 4: buscarItemNaMochila(itensNaMochila); break;
            case 0: printf("\nSaindo do jogo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (escolha != 0);
}

int main(){
    Mochila *itensNaMochila = NULL;
    alocMemoria(&itensNaMochila);

    itensNaMochila->quantidade = 0;

    menu(itensNaMochila);

    return 0;
}

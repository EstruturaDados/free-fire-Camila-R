#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int unidade;
    int prioridade;
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
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n=====================================================\n");
    printf("============== ITENS NA MOCHILA (%d/10) ==============\n", itensNaMochila->quantidade);
    printf("=====================================================\n");

    if (itensNaMochila->quantidade == 0){
        printf("A mochila está vazia.\n");
        return;
    }

    printf("%-20s | %-12s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < itensNaMochila->quantidade; i++){
        printf("%-20s | %-12s | %-10d | %-10d\n",
            itensNaMochila->itens[i].nome,
            itensNaMochila->itens[i].tipo,
            itensNaMochila->itens[i].unidade,
            itensNaMochila->itens[i].prioridade
        );
    }

    printf("=====================================================\n");
}
// Função de ordenar por nome por Insertion Sort
void ordenarItensNaMochilaPorNome(Mochila *itensNaMochila){

    Item *lista = itensNaMochila->itens;
    int tamanho = itensNaMochila->quantidade;

    for (int i = 1; i < tamanho; i++) {

        Item chave = lista[i];
        int j = i - 1;

        // Move os elementos em ordem alfabética uma posição à frente
        while (j >= 0 && strcmp(lista[j].nome, chave.nome) > 0) {
            lista[j + 1] = lista[j];
            j--;
        }

        lista[j + 1] = chave;
    }

    listarItens(itensNaMochila);

}

// Função auxiliar para o selection sort
void trocar(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Função de ordenar por nome por Selection Sort
void ordenarItensNaMochilaPorPrioridade(Mochila *itensNaMochila){

    Item *lista = itensNaMochila->itens;
    int tamanho = itensNaMochila->quantidade;
    
    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = i;

        for (int j = i + 1; j < tamanho; j++) {
            if (lista[j].prioridade < lista[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            trocar(&lista[i], &lista[indiceMenor]);
        }
        
    }

    listarItens(itensNaMochila);

}

// Função de buscar item na mochila por Busca Binária
void buscarItemNaMochila(Mochila *itensNaMochila){

    char nomeItem[30];
    int tamanho = itensNaMochila->quantidade;
    Item *lista = itensNaMochila->itens;
    int inicio = 0;
    int fim = tamanho - 1;

    printf("=====================================================\n");
    printf("==============  BUSCAR ITEM NA MOCHILA ==============\n");
    printf("=====================================================\n");

    printf("Digite o nome do item a ser encontrado: ");
    fgets(nomeItem, sizeof(nomeItem), stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';

    // busca binária
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(lista[meio].nome, nomeItem);

        if (cmp == 0){
            printf("==============  ITEM ENCONTRADO! ==============\n");
            printf("Nome: %-20s \nTipo: %-12s \nQuantidade: %-10d \nPrioridade: %-10d\n",
                itensNaMochila->itens[meio].nome,
                itensNaMochila->itens[meio].tipo,
                itensNaMochila->itens[meio].unidade,
                itensNaMochila->itens[meio].prioridade
            );
            printf("=====================================================\n");
            return meio;
        }
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
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

    printf("Prioridade: ");
    scanf("%d", &itensNaMochila->itens[index].prioridade);
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
        printf("4 - Ordenar itens na mochila por nome\n");
        printf("5 - Ordenar itens na mochila por prioridade\n");
        printf("6 - Buscar item na mochila\n");
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
            case 4: ordenarItensNaMochilaPorNome(itensNaMochila); break;
            case 5: ordenarItensNaMochilaPorPrioridade(itensNaMochila); break;
            case 6: buscarItemNaMochila(itensNaMochila); break;
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
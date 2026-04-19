#include "labirinto.h"

int main() {
    srand(time(NULL));

    Labirinto lab;
    Mochila mochila;
    Pilha caminho;

    char entrada[100], saida[100];

    printf("Arquivo entrada: ");
    scanf("%s", entrada);

    printf("Arquivo saida: ");
    scanf("%s", saida);

    if (!carregar_labirinto(&lab, entrada)) {
        printf("Erro ao carregar arquivo\n");
        return 1;
    }

    iniciar_mochila(&mochila);
    iniciar_pilha(&caminho);

    FILE *out = fopen(saida, "w");
    if (!out) {
        printf("Erro ao criar arquivo\n");
        return 1;
    }

    int achou = backtracking(
        &lab,
        lab.ini_linha,
        lab.ini_coluna,
        &mochila,
        &caminho,
        out
    );

    fclose(out);

    if (achou)
        printf("\nSAIDA ENCONTRADA!\n");
    else
        printf("\nSEM SAIDA\n");

    liberar_mochila(&mochila);
    liberar_pilha(&caminho);

    return 0;
}
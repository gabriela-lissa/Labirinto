#include <stdlib.h>
#include "pilha.h"

void iniciar_pilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void empilhar(Pilha *p, int linha, int coluna) {
    NoPilha *novo = malloc(sizeof(NoPilha));

    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = p->topo;

    p->topo = novo;
    p->tamanho++;
}

int desempilhar(Pilha *p, int *linha, int *coluna) {
    if (!p->topo) return 0;

    NoPilha *temp = p->topo;

    *linha = temp->linha;
    *coluna = temp->coluna;

    p->topo = temp->prox;
    free(temp);

    p->tamanho--;
    return 1;
}

int pilha_vazia(const Pilha *p) {
    return p->topo == NULL;
}

void liberar_pilha(Pilha *p) {
    int l, c;
    while (desempilhar(p, &l, &c));
}
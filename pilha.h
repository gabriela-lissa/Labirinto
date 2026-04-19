#ifndef PILHA_H
#define PILHA_H

typedef struct NoPilha {
    int linha;
    int coluna;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tamanho;
} Pilha;

void iniciar_pilha(Pilha *p);
void empilhar(Pilha *p, int linha, int coluna);
int desempilhar(Pilha *p, int *linha, int *coluna);
int pilha_vazia(const Pilha *p);
void liberar_pilha(Pilha *p);

#endif
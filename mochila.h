#ifndef MOCHILA_H
#define MOCHILA_H

typedef struct NoMochila {
    int valor;
    struct NoMochila *prox;
} NoMochila;

typedef struct {
    NoMochila *inicio;
    int total_moedas;
    int quantidade;
} Mochila;

void iniciar_mochila(Mochila *m);
void inserir_tesouro(Mochila *m, int valor);
int remover_menor_tesouro(Mochila *m);
void imprimir_mochila(const Mochila *m);
void liberar_mochila(Mochila *m);

#endif
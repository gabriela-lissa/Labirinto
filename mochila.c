#include "configs.h"
#include "mochila.h"

void iniciar_mochila(Mochila *m) {
    m->inicio = NULL;
    m->total_moedas = 0;
    m->quantidade = 0;
}

void inserir_tesouro(Mochila *m, int valor) {
    NoMochila *novo = malloc(sizeof(NoMochila));
    if (!novo) {
        printf("Erro de memoria\n");
        exit(1);
    }

    novo->valor = valor;
    novo->prox = NULL;

    if (!m->inicio || valor <= m->inicio->valor) {
        novo->prox = m->inicio;
        m->inicio = novo;
    } else {
        NoMochila *atual = m->inicio;
        while (atual->prox && atual->prox->valor < valor)
            atual = atual->prox;

        novo->prox = atual->prox;
        atual->prox = novo;
    }

    m->total_moedas += valor;
    m->quantidade++;
}

int remover_menor_tesouro(Mochila *m) {
    if (!m->inicio) return -1;

    NoMochila *temp = m->inicio;
    int valor = temp->valor;

    m->inicio = temp->prox;
    free(temp);

    m->total_moedas -= valor;
    m->quantidade--;

    return valor;
}

void imprimir_mochila(const Mochila *m) {
    printf("\n=== MOCHILA ===\n");

    if (!m->inicio) {
        printf("(vazia)\n");
    } else {
        NoMochila *atual = m->inicio;
        while (atual) {
            printf("Tesouro: %d\n", atual->valor);
            atual = atual->prox;
        }
    }

    printf("Total: %d\n", m->total_moedas);
}

void liberar_mochila(Mochila *m) {
    NoMochila *atual = m->inicio;
    while (atual) {
        NoMochila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    m->inicio = NULL;
}
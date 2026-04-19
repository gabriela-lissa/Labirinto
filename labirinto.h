#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "configs.h"
#include "mochila.h"
#include "pilha.h"

typedef struct {
    char mapa[MAX_LINHAS][MAX_COLUNAS + 1];
    char original[MAX_LINHAS][MAX_COLUNAS + 1];
    int linhas;
    int colunas;
    int ini_linha;
    int ini_coluna;
} Labirinto;

int carregar_labirinto(Labirinto *lab, const char *arquivo);
void imprimir_labirinto(const Labirinto *lab, int lin, int col, const Mochila *m);
int backtracking(Labirinto *lab, int lin, int col, Mochila *m, Pilha *caminho, FILE *saida);
int sortear_tesouro(void);

#endif
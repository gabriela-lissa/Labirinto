#include "labirinto.h"

/* ============================================================
 *  CARREGAR LABIRINTO
 * ============================================================ */
int carregar_labirinto(Labirinto *lab, const char *arquivo)
{
    FILE *fp = fopen(arquivo, "r");
    if (!fp) return 0;

    int linhas = 0, colunas = 0;

    if (fscanf(fp, "%dx%d\n", &linhas, &colunas) != 2) {
        rewind(fp);
        if (fscanf(fp, "%d %d\n", &linhas, &colunas) != 2) {
            fclose(fp);
            return 0;
        }
    }

    if (linhas <= 0 || linhas > MAX_LINHAS ||
        colunas <= 0 || colunas > MAX_COLUNAS) {
        fclose(fp);
        return 0;
    }

    lab->linhas = linhas;
    lab->colunas = colunas;
    lab->ini_linha = -1;
    lab->ini_coluna = -1;

    for (int i = 0; i < linhas; i++) {

        if (!fgets(lab->mapa[i], MAX_COLUNAS + 2, fp)) {
            memset(lab->mapa[i], '#', colunas);
            lab->mapa[i][colunas] = '\0';
        } else {
            int len = strlen(lab->mapa[i]);

            while (len > 0 && (lab->mapa[i][len-1] == '\n' ||
                               lab->mapa[i][len-1] == '\r')) {
                lab->mapa[i][--len] = '\0';
            }

            while (len < colunas) {
                lab->mapa[i][len++] = ' ';
            }

            lab->mapa[i][colunas] = '\0';
        }

        strcpy(lab->original[i], lab->mapa[i]);

        for (int j = 0; j < colunas; j++) {
            if (lab->mapa[i][j] == 'P') {
                lab->ini_linha = i;
                lab->ini_coluna = j;
            }
        }
    }

    fclose(fp);

    if (lab->ini_linha == -1) {
        printf("Erro: P nao encontrado\n");
        return 0;
    }

    return 1;
}

/* ============================================================
 *  IMPRIMIR LABIRINTO
 * ============================================================ */
void imprimir_labirinto(const Labirinto *lab, int lin, int col, const Mochila *m)
{
    LIMPAR_TELA;

    printf("=== LABIRINTO ===\n\n");

    for (int i = 0; i < lab->linhas; i++) {
        for (int j = 0; j < lab->colunas; j++) {

            if (i == lin && j == col) {
                printf("@");
            } else {
                printf("%c", lab->mapa[i][j]);
            }
        }
        printf("\n");
    }

    imprimir_mochila(m);

    printf("\nLegenda: # Parede | @ Player | T Tesouro | A Armadilha | S Saida | . Visitado\n");
}

/* ============================================================
 *  BACKTRACKING
 * ============================================================ */
int backtracking(Labirinto *lab, int lin, int col,
                 Mochila *m, Pilha *caminho,
                 FILE *saida)
{
    if (lin < 0 || lin >= lab->linhas ||
        col < 0 || col >= lab->colunas)
        return 0;

    char celula = lab->mapa[lin][col];

    if (celula == '#' || celula == '.')
        return 0;

    imprimir_labirinto(lab, lin, col, m);

    fprintf(saida, "Posicao: (%d,%d) | Moedas: %d\n",
            lin, col, m->total_moedas);

    DORMIR(DELAY_MS);

    int coletado = -1;
    int perdido = -1;

    if (celula == 'T') {
        coletado = sortear_tesouro();
        inserir_tesouro(m, coletado);

        printf("\n+%d moedas!\n", coletado);
        DORMIR(DELAY_MS);
    }

    else if (celula == 'A') {
        perdido = remover_menor_tesouro(m);

        if (perdido >= 0)
            printf("\nPerdeu %d moedas!\n", perdido);
        else
            printf("\nNada a perder!\n");

        DORMIR(DELAY_MS);
    }

    else if (celula == 'S') {
        empilhar(caminho, lin, col);
        printf("\nSAIDA ENCONTRADA!\n");
        return 1;
    }

    lab->mapa[lin][col] = '.';

    int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

    for (int i = 0; i < 4; i++) {
        if (backtracking(
            lab,
            lin + dirs[i][0],
            col + dirs[i][1],
            m,
            caminho,
            saida)) {

            empilhar(caminho, lin, col);
            return 1;
        }
    }

    /* BACKTRACK */
    lab->mapa[lin][col] = lab->original[lin][col];

    if (celula == 'T' && coletado >= 0) {
        NoMochila *ant = NULL, *atual = m->inicio;

        while (atual) {
            if (atual->valor == coletado) {

                if (ant) ant->prox = atual->prox;
                else m->inicio = atual->prox;

                m->total_moedas -= atual->valor;
                m->quantidade--;

                free(atual);
                break;
            }

            ant = atual;
            atual = atual->prox;
        }
    }

    else if (celula == 'A' && perdido >= 0) {
        inserir_tesouro(m, perdido);
    }

    return 0;
}

/* ============================================================
 *  TESOURO ALEATORIO
 * ============================================================ */
int sortear_tesouro(void)
{
    return (rand() % 100) + 1;
}
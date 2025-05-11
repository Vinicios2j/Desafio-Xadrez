#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para representar uma posição no tabuleiro
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Converte a notação (ex: e2) para linha e coluna (ex: linha 6, coluna 4)
Posicao converter_posicao(char *entrada) {
    Posicao p;
    p.coluna = tolower(entrada[0]) - 'a';
    p.linha = 8 - (entrada[1] - '0');
    return p;
}

// Verifica se a posição está dentro do tabuleiro
int posicao_valida(Posicao p) {
    return (p.linha >= 0 && p.linha < 8 && p.coluna >= 0 && p.coluna < 8);
}

// Funções para verificar movimentos válidos por peça
int movimento_torre(Posicao ini, Posicao fim) {
    return ini.linha == fim.linha || ini.coluna == fim.coluna;
}

int movimento_bispo(Posicao ini, Posicao fim) {
    return abs(ini.linha - fim.linha) == abs(ini.coluna - fim.coluna);
}

int movimento_cavalo(Posicao ini, Posicao fim) {
    int dx = abs(ini.coluna - fim.coluna);
    int dy = abs(ini.linha - fim.linha);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

int movimento_rei(Posicao ini, Posicao fim) {
    return abs(ini.linha - fim.linha) <= 1 && abs(ini.coluna - fim.coluna) <= 1;
}

int movimento_rainha(Posicao ini, Posicao fim) {
    return movimento_torre(ini, fim) || movimento_bispo(ini, fim);
}

int movimento_peao(Posicao ini, Posicao fim) {
    return fim.coluna == ini.coluna && fim.linha == ini.linha - 1;
}

int main() {
    char peca[10], origem[3], destino[3];
    printf("Digite a peça (rei, dama, torre, bispo, cavalo, peao): ");
    scanf("%s", peca);
    printf("Digite a posição inicial (ex: e2): ");
    scanf("%s", origem);
    printf("Digite a posição final (ex: e4): ");
    scanf("%s", destino);

    Posicao ini = converter_posicao(origem);
    Posicao fim = converter_posicao(destino);

    if (!posicao_valida(ini) || !posicao_valida(fim)) {
        printf("Posição inválida no tabuleiro.\n");
        return 1;
    }

    int valido = 0;
    if (strcmp(peca, "rei") == 0)
        valido = movimento_rei(ini, fim);
    else if (strcmp(peca, "dama") == 0)
        valido = movimento_rainha(ini, fim);
    else if (strcmp(peca, "torre") == 0)
        valido = movimento_torre(ini, fim);
    else if (strcmp(peca, "bispo") == 0)
        valido = movimento_bispo(ini, fim);
    else if (strcmp(peca, "cavalo") == 0)
        valido = movimento_cavalo(ini, fim);
    else if (strcmp(peca, "peao") == 0)
        valido = movimento_peao(ini, fim);
    else {
        printf("Peça desconhecida.\n");
        return 1;
    }

    if (valido)
        printf("Movimento válido!\n");
    else
        printf("Movimento inválido!\n");

    return 0;
}
    
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 15
#define NAVIO1_TAMANHO 4
#define NAVIO2_TAMANHO 3
#define NAVIO3_TAMANHO 3

char tabuleiroJogador[TAMANHO][TAMANHO];
char tabuleiroComputador[TAMANHO][TAMANHO];
int naviosJogador = NAVIO1_TAMANHO + NAVIO2_TAMANHO + NAVIO3_TAMANHO;
int naviosComputador = NAVIO1_TAMANHO + NAVIO2_TAMANHO + NAVIO3_TAMANHO;

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = '0';
}

void mostrarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) printf("%2d ", i + 1);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void converterCoordenada(char letra, int numero, int *x, int *y) {
    *x = letra - 'A';
    *y = numero - 1;
}

void posicionarNavios(char tabuleiro[TAMANHO][TAMANHO]) {
    srand(time(NULL));
    int x, y;

    x = rand() % (TAMANHO - NAVIO1_TAMANHO);
    y = rand() % TAMANHO;
    for (int i = 0; i < NAVIO1_TAMANHO; i++) tabuleiro[x][y + i] = '3';

    x = rand() % TAMANHO;
    y = rand() % (TAMANHO - NAVIO2_TAMANHO);
    for (int i = 0; i < NAVIO2_TAMANHO; i++) tabuleiro[x + i][y] = '3';

    x = rand() % (TAMANHO - NAVIO3_TAMANHO);
    y = rand() % (TAMANHO - NAVIO3_TAMANHO);
    for (int i = 0; i < NAVIO3_TAMANHO; i++) tabuleiro[x + i][y + i] = '3';
}

void atacarCelula(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int *navios) {
    if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO) {
        if (tabuleiro[x][y] == '3') {
            printf("Acertou em %c%d!\n", 'A' + x, y + 1);
            tabuleiro[x][y] = 'X';
            (*navios)--;
        } else if (tabuleiro[x][y] == '0') {
            printf("Errou em %c%d!\n", 'A' + x, y + 1);
            tabuleiro[x][y] = 'O';
        }
    }
}

void ataqueJogador() {
    char letra;
    int x, y, numero;

    printf("Digite a coordenada do ataque (ex: D6): ");
    scanf(" %c%d", &letra, &numero);
    converterCoordenada(letra, numero, &x, &y);
    atacarCelula(tabuleiroComputador, x, y, &naviosComputador);
}

void ataqueComputador() {
    int x = rand() % TAMANHO;
    int y = rand() % TAMANHO;
    atacarCelula(tabuleiroJogador, x, y, &naviosJogador);
}

int main() {
    inicializarTabuleiro(tabuleiroJogador);
    inicializarTabuleiro(tabuleiroComputador);

    printf("Posicionando navios...\n");
    posicionarNavios(tabuleiroJogador);
    posicionarNavios(tabuleiroComputador);

    while (naviosJogador > 0 && naviosComputador > 0) {
        printf("\nSeu Tabuleiro:\n");
        mostrarTabuleiro(tabuleiroJogador);
        
        printf("\nTabuleiro do Computador:\n");
        mostrarTabuleiro(tabuleiroComputador);

        ataqueJogador();
        if (naviosComputador == 0) break;
        ataqueComputador();
    }

    printf("\n%s venceu!\n", naviosJogador > 0 ? "Você" : "O Computador");
    return 0;
}

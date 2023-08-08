/*
A ordem de complexidade do algoritmo de rasterização de círculos usando o algoritmo de Bresenham é aproximadamente O(n), onde n é o número de pixels na circunferência. No pior caso, todos os pontos na circunferência devem ser desenhados.

O algoritmo de Bresenham utiliza uma abordagem incremental para determinar os pontos a serem desenhados, evitando cálculos de ponto flutuante e tornando-o eficiente para rasterização em implementações de hardware e software.

No código, os comentários explicam o cálculo da função de decisão (d) que guia a escolha entre mover-se na direção diagonal ou horizontal para o próximo ponto a ser desenhado. Os pontos simétricos nas oitantes do círculo são calculados e desenhados na tela.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

void drawCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        // Desenhar os pontos simétricos em todas as oitantes do círculo
        // (xc + x, yc + y), (xc - x, yc + y), (xc + x, yc - y), (xc - x, yc - y)
        // (xc + y, yc + x), (xc - y, yc + x), (xc + y, yc - x), (xc - y, yc - x)
        printf("(%d, %d) ", xc + x, yc + y);
        printf("(%d, %d) ", xc - x, yc + y);
        printf("(%d, %d) ", xc + x, yc - y);
        printf("(%d, %d) ", xc - x, yc - y);
        printf("(%d, %d) ", xc + y, yc + x);
        printf("(%d, %d) ", xc - y, yc + x);
        printf("(%d, %d) ", xc + y, yc - x);
        printf("(%d, %d) ", xc - y, yc - x);

        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    int xc = 5; // Coordenada x do centro da circunferência
    int yc = 5; // Coordenada y do centro da circunferência
    int r = 4;  // Raio da circunferência

    drawCircle(xc, yc, r);

    return 0;
}


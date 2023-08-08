/*
Neste exemplo, a função drawLine recebe os pontos de início e fim da linha e itera através dos pixels para desenhar a linha usando o algoritmo de Bresenham. A saída é impressa no console, mas em um ambiente gráfico real, você substituiria a impressão por uma função que definisse os pixels na tela.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para representar um ponto 2D
typedef struct {
    int x, y;
} Point;

// Função para desenhar uma linha utilizando o algoritmo de Bresenham
void drawLine(Point start, Point end) {
    // Calcula as diferenças entre as coordenadas x e y
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    
    // Determina a direção dos passos na horizontal e vertical
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;

    // Inicializa o erro inicial
    int err = dx - dy;

    // Loop para percorrer os pixels da linha
    while (1) {
        // Desenha o pixel atual (substitua por uma função para definir o pixel na tela)
        printf("(%d, %d)\n", start.x, start.y);

        // Verifica se o ponto final foi alcançado
        if (start.x == end.x && start.y == end.y) {
            break;
        }

        // Calcula o dobro do erro
        int e2 = 2 * err;
        
        // Atualiza o erro e a coordenada x
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        
        // Atualiza o erro e a coordenada y
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

int main() {
    // Ponto de início e ponto final da linha
    Point start = {1, 1};
    Point end = {10, 5};

    // Chama a função para desenhar a linha
    drawLine(start, end);

    return 0;
}


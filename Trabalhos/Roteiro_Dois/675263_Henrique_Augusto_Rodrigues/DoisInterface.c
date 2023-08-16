/*
Este código em C desenha uma linha usando o algoritmo DDA e aplica transformações geométricas ao ponto inicial da linha. Utiliza a biblioteca gráfica graphics.h. Lembre-se de configurar um ambiente que suporte essa biblioteca para executar o código.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>  // Biblioteca gráfica para desenho em C

// Estrutura para armazenar um ponto
struct Point {
    int x;
    int y;
};

// Função para aplicar transformações geométricas a um ponto
void applyTransformations(struct Point *point, float angle, float dx, float dy, float sx, float sy, float shx, float shy) {
    // Aplicar rotação
    float angle_rad = angle * M_PI / 180.0;
    int tempX = point->x;
    point->x = round(point->x * cos(angle_rad) - point->y * sin(angle_rad));
    point->y = round(tempX * sin(angle_rad) + point->y * cos(angle_rad));

    // Aplicar translação
    point->x += round(dx);
    point->y += round(dy);

    // Aplicar escala
    point->x = round(point->x * sx);
    point->y = round(point->y * sy);

    // Aplicar cisalhamento
    point->x += round(point->y * shx);
    point->y += round(point->x * shy);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");  // Inicialização do modo gráfico

    struct Point start_point = {100, 100};  // Ponto inicial da linha

    int x1 = start_point.x, y1 = start_point.y, x2, y2;
    int drawing = 0;  // Indicador de desenho ativado

    while (!kbhit()) {
        // Obter posição do mouse
        int mx, my;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (!drawing) {
                x1 = mx;
                y1 = my;
                start_point.x = x1;
                start_point.y = y1;
                drawing = 1;  // Ativar desenho
            }
        }
        if (ismouseclick(WM_LBUTTONUP)) {
            getmouseclick(WM_LBUTTONUP, mx, my);
            x2 = mx;
            y2 = my;
            drawing = 0;  // Desativar desenho

            // Desenhar linha usando o algoritmo DDA
            int dx = abs(x2 - x1), dy = abs(y2 - y1);
            int steps = dx > dy ? dx : dy;

            float xIncrement = (float)(x2 - x1) / steps;
            float yIncrement = (float)(y2 - y1) / steps;

            float x = x1, y = y1;

            for (int i = 0; i <= steps; i++) {
                putpixel((int)x, (int)y, WHITE);
                x += xIncrement;
                y += yIncrement;
            }

            // Aplicar transformações geométricas ao ponto inicial da linha
            float angle = 0.0, dx = 0.0, dy = 0.0, sx = 1.0, sy = 1.0, shx = 0.0, shy = 0.0;
            applyTransformations(&start_point, angle, dx, dy, sx, sy, shx, shy);

            printf("Original: (%d, %d)\n", x1, y1);
            printf("Transformado: (%d, %d)\n", start_point.x, start_point.y);

            delay(2000);  // Aguardar por 2 segundos antes de fechar a janela
            cleardevice();  // Limpar a tela
        }
    }

    closegraph();  // Fechar a janela gráfica

    return 0;
}


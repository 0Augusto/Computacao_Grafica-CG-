#include <stdio.h>

typedef struct {
    float x, y;
} Point;

// Função para calcular o valor de t (parâmetro de interseção) usando o algoritmo de Liang-Barsky
int liangBarsky(Point p1, Point p2, float *t1, float *t2, float xmin, float xmax, float ymin, float ymax) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float p[4], q[4];
    float tEnter = 0, tExit = 1;

    p[0] = -dx;
    q[0] = p1.x - xmin;
    p[1] = dx;
    q[1] = xmax - p1.x;
    p[2] = -dy;
    q[2] = p1.y - ymin;
    p[3] = dy;
    q[3] = ymax - p1.y;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            return 0; // O segmento de reta está fora da janela de recorte
        }

        if (p[i] != 0) {
            float r = q[i] / p[i];
            if (p[i] < 0) {
                if (r > tExit) {
                    return 0; // O segmento de reta está fora da janela de recorte
                } else if (r > tEnter) {
                    tEnter = r;
                }
            } else {
                if (r < tEnter) {
                    return 0; // O segmento de reta está fora da janela de recorte
                } else if (r < tExit) {
                    tExit = r;
                }
            }
        }
    }

    if (tEnter < tExit) {
        *t1 = tEnter;
        *t2 = tExit;
        return 1; // O segmento de reta está dentro da janela de recorte
    }

    return 0; // O segmento de reta está fora da janela de recorte
}

int main() {
    Point p1 = {1, 1};
    Point p2 = {5, 5};
    float t1, t2;

    float xmin = 2, xmax = 4, ymin = 2, ymax = 4;

    if (liangBarsky(p1, p2, &t1, &t2, xmin, xmax, ymin, ymax)) {
        // O segmento de reta está dentro da janela de recorte
        printf("Segmento de reta recortado:\n");
        printf("P1(%.2f, %.2f) -> P2(%.2f, %.2f)\n", p1.x + t1 * (p2.x - p1.x), p1.y + t1 * (p2.y - p1.y),
               p1.x + t2 * (p2.x - p1.x), p1.y + t2 * (p2.y - p1.y));
    } else {
        printf("O segmento de reta está fora da janela de recorte.\n");
    }

    return 0;
}

#include <stdio.h>

typedef struct {
    float x, y = 0.0;
} Point;

// Função para verificar se um ponto está à esquerda de uma linha definida por dois pontos
int isLeft(Point a, Point b, Point c) {
    return ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) > 0;
}

// Algoritmo de Sutherland-Hodgman para recorte de polígonos
void sutherlandHodgman(Point polygon[], int n, Point clip[], int m) {
    Point output[100]; // Suponha que o tamanho máximo do polígono de saída seja 100
    int outputSize = 0;

    for (int i = 0; i < m; i++) {
        Point edgeStart = clip[i];
        Point edgeEnd = clip[(i + 1) % m];

        for (int j = 0; j < n; j++) {
            Point current = polygon[j];
            Point next = polygon[(j + 1) % n];

            if (isLeft(edgeStart, edgeEnd, current)) {
                if (!isLeft(edgeStart, edgeEnd, next)) {
                    // Calcula o ponto de interseção e adiciona-o ao polígono de saída
                    float dx = next.x - current.x;
                    float dy = next.y - current.y;
                    float t = ((edgeStart.x - current.x) * dx + (edgeStart.y - current.y) * dy) / (dx * dx + dy * dy);
                    Point intersection = {current.x + t * dx, current.y + t * dy};
                    output[outputSize++] = intersection;
                }
                output[outputSize++] = next;
            } else if (isLeft(edgeStart, edgeEnd, next)) {
                // Calcula o ponto de interseção e adiciona-o ao polígono de saída
                float dx = next.x - current.x;
                float dy = next.y - current.y;
                float t = ((edgeStart.x - current.x) * dx + (edgeStart.y - current.y) * dy) / (dx * dx + dy * dy);
                Point intersection = {current.x + t * dx, current.y + t * dy};
                output[outputSize++] = intersection;
            }
        }

        // Atualiza o polígono de entrada com o polígono de saída
        n = outputSize;
        for (int k = 0; k < outputSize; k++) {
            polygon[k] = output[k];
        }
        outputSize = 0;
    }

    // A saída final é armazenada em 'polygon'
    printf("Polígono recortado:\n");
    for (int i = 0; i < n; i++) {
        printf("(%.2f, %.2f)\n", polygon[i].x, polygon[i].y);
    }
}

int main() {
    // Defina o polígono de entrada (n vértices) e a janela de recorte (m vértices)
    Point polygon[] = {{0, 0}, {2, 4}, {4, 0}, {2, -2}};
    int n = sizeof(polygon) / sizeof(polygon[0]);

    Point clip[] = {{1, 1}, {3, 1}, {3, -1}, {1, -1}};
    int m = sizeof(clip) / sizeof(clip[0]);

    // Chame o algoritmo de recorte
    sutherlandHodgman(polygon, n, clip, m);

    return 0;
}


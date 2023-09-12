#include <stdio.h>

// Função para calcular a interseção entre dois números
float clip(float p, float q, float *t1, float *t2) {
    float r;
    if (p < 0) {
        r = q / (q - p);
        if (r > *t1) *t1 = r;
        if (r > *t2) return 0; // A linha está completamente fora
    } else if (p > 0) {
        r = q / (q - p);
        if (r < *t2) *t2 = r;
        if (r < *t1) return 0; // A linha está completamente fora
    } else {
        if (q < 0) return 0; // A linha é paralela e está fora da janela
    }
    return 1; // A linha pode cruzar a janela
}

void liangBarsky(float x1, float y1, float x2, float y2, float xmin, float ymin, float xmax, float ymax) {
    float t1 = 0, t2 = 1; // Inicializa os valores de t1 e t2

    // Calcula as diferenças entre os pontos inicial e final da linha
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Chama a função clip para cada lado da janela de recorte
    if (clip(-dx, x1 - xmin, &t1, &t2) && clip(dx, xmax - x1, &t1, &t2) &&
        clip(-dy, y1 - ymin, &t1, &t2) && clip(dy, ymax - y1, &t1, &t2)) {
        // A linha cruza a janela de recorte, então desenhe a parte visível
        float x1_clip = x1 + t1 * dx;
        float y1_clip = y1 + t1 * dy;
        float x2_clip = x1 + t2 * dx;
        float y2_clip = y1 + t2 * dy;

        printf("Linha recortada: (%.2f, %.2f) - (%.2f, %.2f)\n", x1_clip, y1_clip, x2_clip, y2_clip);
    } else {
        // A linha está completamente fora da janela de recorte
        printf("A linha está completamente fora da janela de recorte.\n");
    }
}

int main() {
    float x1 = 50, y1 = 20, x2 = 100, y2 = 80; // Pontos inicial e final da linha
    float xmin = 30, ymin = 40, xmax = 90, ymax = 60; // Janela de recorte

    printf("Pontos da linha: (%.2f, %.2f) - (%.2f, %.2f)\n", x1, y1, x2, y2);
    printf("Janela de recorte: (%.2f, %.2f) - (%.2f, %.2f)\n", xmin, ymin, xmax, ymax);

    liangBarsky(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    return 0;
}


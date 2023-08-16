/*
Este código implementa o algoritmo DDA para rasterização de uma linha, seguindo os passos fornecidos. Certifique-se de substituir a impressão dos pontos intermediários pela lógica apropriada para definir os pixels na tela em um ambiente gráfico real.

O algoritmo DDA é bastante simples e eficiente para rasterização de linhas, mas é importante notar que ele pode sofrer perda de precisão em algumas situações. Em ambientes gráficos modernos, outros algoritmos, como o algoritmo de Bresenham ou algoritmos de ponto médio, são frequentemente preferidos devido à sua robustez e desempenho.
*/

#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y;
} Point;

void drawLineDDA(Point start, Point end) {
    // Passo 2: Cálculo das diferenças dx e dy
    float dx = end.x - start.x;
    float dy = end.y - start.y;

    // Passo 3: Determinação do número de passos
    int steps = (int)fabs(dx) > (int)fabs(dy) ? (int)fabs(dx) : (int)fabs(dy);

    // Passo 4: Cálculo dos incrementos xIncrement e yIncrement
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    // Inicializa as coordenadas x e y com os valores iniciais
    float x = start.x;
    float y = start.y;

    // Passo 5: Desenho dos pontos intermediários
    for (int i = 0; i <= steps; i++) {
        // Desenhar o pixel aqui (substituir por lógica para definir o pixel na tela)
        printf("(%f, %f)\n", x, y);

        // Atualiza as coordenadas x e y usando os incrementos calculados
        x += xIncrement;
        y += yIncrement;
    }
    printf("(%f, %f)\n", x, y);//Para gerar o último ponto
    // Passo 6: Rasterização completa
    printf("Rasterização completa.\n");
}

int main() {
    // Defina os pontos de início e fim da linha
    Point start = {1.0, 1.0};
    Point end = {10.0, 5.0};

    // Chama a função para rasterizar a linha usando o algoritmo DDA
    drawLineDDA(start, end);

    return 0;
}


/*

exemplo de código em C para aplicar rotação, translação e reflexão em um ponto 2D. Neste exemplo, usaremos matrizes de transformação para realizar as operações.

Neste exemplo, criamos funções para rotação, translação e reflexão, cada uma delas retornando um novo ponto 2D resultante da operação. Na função main, definimos um ponto original, um ângulo de rotação e os componentes da translação (dx e dy).

A rotação é aplicada primeiro, seguida pela translação e, por fim, a reflexão. Note que para a reflexão, apenas invertemos os sinais das coordenadas do ponto, o que é equivalente a refletir em relação à origem.

O programa imprime na tela os pontos original, rotacionado, transladado e refletido, demonstrando o resultado de cada operação. Lembre-se de que a ordem das operações pode afetar o resultado final, dependendo do comportamento desejado.

*/

#include <stdio.h>
#include <math.h>

// Estrutura para representar um ponto 2D
typedef struct {
    float x, y;
} Point2D;

// Função para rotacionar um ponto 2D em torno da origem
Point2D rotate(Point2D point, float angle) {
    Point2D result;
    float rad = angle * M_PI / 180.0; // Convertendo o ângulo para radianos
    result.x = point.x * cos(rad) - point.y * sin(rad);
    result.y = point.x * sin(rad) + point.y * cos(rad);
    return result;
}

// Função para transladar um ponto 2D
Point2D translate(Point2D point, float dx, float dy) {
    Point2D result;
    result.x = point.x + dx;
    result.y = point.y + dy;
    return result;
}

// Função para refletir um ponto 2D em relação à origem
Point2D reflect(Point2D point) {
    Point2D result;
    result.x = -point.x;
    result.y = -point.y;
    return result;
}

int main() {
    Point2D originalPoint = {1.0, 1.0};
    float angle = 45.0; // Ângulo de rotação em graus
    float dx = 2.0;    // Componente x da translação
    float dy = 3.0;    // Componente y da translação

    // Aplicando a rotação
    Point2D rotatedPoint = rotate(originalPoint, angle);

    // Aplicando a translação
    Point2D translatedPoint = translate(rotatedPoint, dx, dy);

    // Aplicando a reflexão
    Point2D reflectedPoint = reflect(translatedPoint);

    // Imprimindo os resultados
    printf("Ponto original: (%f, %f)\n", originalPoint.x, originalPoint.y);
    printf("Ponto rotacionado: (%f, %f)\n", rotatedPoint.x, rotatedPoint.y);
    printf("Ponto transladado: (%f, %f)\n", translatedPoint.x, translatedPoint.y);
    printf("Ponto refletido: (%f, %f)\n", reflectedPoint.x, reflectedPoint.y);

    return 0;
}


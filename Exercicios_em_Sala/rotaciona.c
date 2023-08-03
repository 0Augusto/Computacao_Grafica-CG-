/*
A rotação nos eixos X, Y e Z é uma operação comum na computação gráfica para modificar a orientação de um objeto 3D. Cada eixo de rotação representa uma direção específica: X representa o eixo horizontal, Y representa o eixo vertical e Z representa o eixo perpendicular à tela. Vou explicar brevemente como cada rotação funciona e, em seguida, fornecer um exemplo de código em C para aplicar rotações em um ponto 3D.
1. Rotação em torno do eixo X:
Essa rotação ocorre no plano YZ e permite girar o objeto ao redor do eixo X, alterando sua inclinação.

2. Rotação em torno do eixo Y:
Essa rotação ocorre no plano XZ e permite girar o objeto ao redor do eixo Y, alterando sua orientação horizontal.

3. Rotação em torno do eixo Z:
Essa rotação ocorre no plano XY e permite girar o objeto ao redor do eixo Z, alterando sua orientação perpendicular à tela.

O exemplo é um programa simples que define uma estrutura para representar um ponto 3D e implementa funções para realizar as rotações nos eixos X, Y e Z. A função main define um ponto 3D original e três ângulos de rotação (em graus) ao longo dos eixos X, Y e Z. As rotações são aplicadas em sequência e o resultado final é impresso na tela.
*/


#include <stdio.h>
#include <math.h>

// Estrutura para representar um ponto 3D
typedef struct {
    float x, y, z;
} Point3D;

// Função para rotacionar um ponto 3D em torno do eixo X
Point3D rotateX(Point3D point, float angle) {
    Point3D result;
    float rad = angle * M_PI / 180.0; // Convertendo o ângulo para radianos
    result.x = point.x;
    result.y = point.y * cos(rad) - point.z * sin(rad);
    result.z = point.y * sin(rad) + point.z * cos(rad);
    return result;
}

// Função para rotacionar um ponto 3D em torno do eixo Y
Point3D rotateY(Point3D point, float angle) {
    Point3D result;
    float rad = angle * M_PI / 180.0; // Convertendo o ângulo para radianos
    result.x = point.x * cos(rad) + point.z * sin(rad);
    result.y = point.y;
    result.z = -point.x * sin(rad) + point.z * cos(rad);
    return result;
}

// Função para rotacionar um ponto 3D em torno do eixo Z
Point3D rotateZ(Point3D point, float angle) {
    Point3D result;
    float rad = angle * M_PI / 180.0; // Convertendo o ângulo para radianos
    result.x = point.x * cos(rad) - point.y * sin(rad);
    result.y = point.x * sin(rad) + point.y * cos(rad);
    result.z = point.z;
    return result;
}

int main() {
    Point3D originalPoint = {1.0, 0.0, 0.0};
    float angleX = 30.0;
    float angleY = 45.0;
    float angleZ = 60.0;

    // Aplicando as rotações em sequência
    Point3D rotatedX = rotateX(originalPoint, angleX);
    Point3D rotatedXY = rotateY(rotatedX, angleY);
    Point3D finalRotatedPoint = rotateZ(rotatedXY, angleZ);

    // Imprimindo o resultado
    printf("Ponto original: (%f, %f, %f)\n", originalPoint.x, originalPoint.y, originalPoint.z);
    printf("Ponto rotacionado: (%f, %f, %f)\n", finalRotatedPoint.x, finalRotatedPoint.y, finalRotatedPoint.z);

    return 0;
}


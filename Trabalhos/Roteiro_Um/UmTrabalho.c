//---------------------------------------------------------------------
// TransformacoesGeometricas - Aplicação para demonstrar transformações geométricas em um ambiente gráfico.
// Autor: Henrique Augusto Rodrigues
// Versão: 1.3
// Data: 09/08/2023
//---------------------------------------------------------------------
/*
Para compilar em terminal (janela de comandos):    
    Linux      : gcc  UmTrabalho.c -o UmTrabalho  
    MacBook    : gcc  UmTrabalho.c -o UmTrabalho    
    Windows    : gcc -o UmTrabalho.exe  UmTrabalho 
 
   Para executar em terminal (janela de comandos):   
  Linux      :  ./UmTrabalho  
  MacBook    :  ./UmTrabalho   
  Windows    :    UmTrabalho
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para representar um ponto 2D
typedef struct {
    double x, y;
} Point2D;

// Função para rotacionar um ponto 2D em torno da origem
Point2D rotate(Point2D point, double angle_deg) {
    Point2D result;
    double angle_rad = angle_deg * M_PI / 180.0;
    result.x = point.x * cos(angle_rad) - point.y * sin(angle_rad);
    result.y = point.x * sin(angle_rad) + point.y * cos(angle_rad);
    return result;
}

// Função para transladar um ponto 2D
Point2D translate(Point2D point, double dx, double dy) {
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
    // Ponto original
    Point2D originalPoint = {1.0, 1.0};

    // Parâmetros inseridos pelo usuário
    double angle, dx, dy, sx, sy, shx, shy;
    printf("Insira o ângulo de rotação (em graus): ");
    scanf("%lf", &angle);
    printf("Insira o componente x da translação: ");
    scanf("%lf", &dx);
    printf("Insira o componente y da translação: ");
    scanf("%lf", &dy);
    printf("Insira o fator de escala em x: ");
    scanf("%lf", &sx);
    printf("Insira o fator de escala em y: ");
    scanf("%lf", &sy);
    printf("Insira o fator de cisalhamento em x: ");
    scanf("%lf", &shx);
    printf("Insira o fator de cisalhamento em y: ");
    scanf("%lf", &shy);

    // Aplicando as transformações
    Point2D rotatedPoint = rotate(originalPoint, angle);
    Point2D translatedPoint = translate(rotatedPoint, dx, dy);
    Point2D reflectedPoint = reflect(translatedPoint);

    // Aplicando escala
    Point2D scaledPoint = {translatedPoint.x * sx, translatedPoint.y * sy};

    // Aplicando cisalhamento
    Point2D shearedPoint = {scaledPoint.x + scaledPoint.y * shx, scaledPoint.y + scaledPoint.x * shy};

    // Plot dos gráficos usando gnuplot
    FILE *gnuplot = popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set multiplot layout 1, 4\n");

    // Gráfico do ponto original
    fprintf(gnuplot, "plot '-' with points title 'Original'\n");
    fprintf(gnuplot, "%f %f\n", originalPoint.x, originalPoint.y);
    fprintf(gnuplot, "e\n");

    // Gráfico do ponto rotacionado
    fprintf(gnuplot, "plot '-' with points title 'Rotacionado'\n");
    fprintf(gnuplot, "%f %f\n", rotatedPoint.x, rotatedPoint.y);
    fprintf(gnuplot, "e\n");

    // Gráfico do ponto transladado
    fprintf(gnuplot, "plot '-' with points title 'Transladado'\n");
    fprintf(gnuplot, "%f %f\n", translatedPoint.x, translatedPoint.y);
    fprintf(gnuplot, "e\n");

    // Gráfico do ponto escalado
    fprintf(gnuplot, "plot '-' with points title 'Escalado'\n");
    fprintf(gnuplot, "%f %f\n", scaledPoint.x, scaledPoint.y);
    fprintf(gnuplot, "e\n");

    // Gráfico do ponto cisalhado
    fprintf(gnuplot, "plot '-' with points title 'Cisalhado'\n");
    fprintf(gnuplot, "%f %f\n", shearedPoint.x, shearedPoint.y);
    fprintf(gnuplot, "e\n");

    fclose(gnuplot);

    return 0;
}


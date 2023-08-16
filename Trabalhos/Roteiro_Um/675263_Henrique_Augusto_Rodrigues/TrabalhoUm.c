/*
@author: Henrique Augusto Rodrigues
@V1.2
Professor(a): Rosilane
Data: 09/08/2023
Curso: Ciencia da Computação
Turno: Tarde

Para compilar em terminal (janela de comandos):    
    Linux      : gcc  TrabalhoUm.c -o TrabalhoUm  
    MacBook    : gcc  TrabalhoUm.c -o TrabalhoUm    
    Windows    : gcc -o TrabalhoUm.exe  TrabalhoUm 
 
   Para executar em terminal (janela de comandos):   
  Linux      :  ./TrabalhoUm  
  MacBook    :  ./TrabalhoUm   
  Windows    :    TrabalhoUm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h> // Incluindo a biblioteca SDL

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
    // Inicializando o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erro ao inicializar o SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Criando uma janela para exibir o gráfico
    SDL_Window* window = SDL_CreateWindow("TransformacoesGeometricas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Erro ao criar a janela: %s\n", SDL_GetError());
        return 1;
    }

    // Criando um renderizador para a janela
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erro ao criar o renderizador: %s\n", SDL_GetError());
        return 1;
    }

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

    // Aguardando eventos do SDL
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Limpando a tela
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Desenhando os pontos
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, (int)originalPoint.x, (int)originalPoint.y);
        SDL_RenderDrawPoint(renderer, (int)rotatedPoint.x, (int)rotatedPoint.y);
        SDL_RenderDrawPoint(renderer, (int)translatedPoint.x, (int)translatedPoint.y);
        SDL_RenderDrawPoint(renderer, (int)scaledPoint.x, (int)scaledPoint.y);
        SDL_RenderDrawPoint(renderer, (int)shearedPoint.x, (int)shearedPoint.y);

        // Atualizando a tela
        SDL_RenderPresent(renderer);
    }

    // Liberando recursos do SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

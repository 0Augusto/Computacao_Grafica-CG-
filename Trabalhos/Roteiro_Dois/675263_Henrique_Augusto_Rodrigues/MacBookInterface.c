/*

Como compilar: gcc MacBookInterface.c -o MacBookInterface -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2   

Este código utiliza a biblioteca SDL para criar uma janela gráfica, desenhar a linha e aplicar transformações geométricas ao ponto inicial. Note que este é apenas um exemplo básico e pode ser estendido e aprimorado conforme necessário. Certifique-se de ter a biblioteca SDL instalada e configurada corretamente para compilar e executar o código.
*/

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

struct Point {
    int x;
    int y;
};

void applyTransformations(struct Point *point, float angle, float dx, float dy, float sx, float sy, float shx, float shy) {
    float angle_rad = angle * M_PI / 180.0;
    int tempX = point->x;
    point->x = round(point->x * cos(angle_rad) - point->y * sin(angle_rad));
    point->y = round(tempX * sin(angle_rad) + point->y * cos(angle_rad));

    point->x += round(dx);
    point->y += round(dy);

    point->x = round(point->x * sx);
    point->y = round(point->y * sy);

    point->x += round(point->y * shx);
    point->y += round(point->x * shy);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Transformações Geométricas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    struct Point start_point = {100, 100};
    int x1 = start_point.x, y1 = start_point.y, x2, y2;
    int drawing = 0;

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto quit;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (!drawing) {
                    x1 = event.button.x;
                    y1 = event.button.y;
                    start_point.x = x1;
                    start_point.y = y1;
                    drawing = 1;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (drawing) {
                    x2 = event.button.x;
                    y2 = event.button.y;
                    drawing = 0;

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    int dx = abs(x2 - x1), dy = abs(y2 - y1);
                    int steps = dx > dy ? dx : dy;

                    float xIncrement = (float)(x2 - x1) / steps;
                    float yIncrement = (float)(y2 - y1) / steps;

                    float x = x1, y = y1;

                    for (int i = 0; i <= steps; i++) {
                        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
                        x += xIncrement;
                        y += yIncrement;
                    }

                    float angle = 0.0, dx = 0.0, dy = 0.0, sx = 1.0, sy = 1.0, shx = 0.0, shy = 0.0;
                    applyTransformations(&start_point, angle, dx, dy, sx, sy, shx, shy);

                    printf("Original: (%d, %d)\n", x1, y1);
                    printf("Transformado: (%d, %d)\n", start_point.x, start_point.y);

                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);  // Aguardar 2 segundos
                    SDL_RenderClear(renderer);
                }
            }
        }
    }

quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


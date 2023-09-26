#include <iostream>
#include <SFML/Graphics.hpp>
#include <mpi.h>

// Cohen-Sutherland region codes
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

// Clipping window coordinates
#define X_MIN 0
#define X_MAX 800
#define Y_MIN 0
#define Y_MAX 600

// Function to calculate region code for a point
int calculateRegionCode(int x, int y) {
    int code = INSIDE;

    if (x < X_MIN)      code |= LEFT;
    else if (x > X_MAX) code |= RIGHT;

    if (y < Y_MIN)      code |= BOTTOM;
    else if (y > Y_MAX) code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping function
void cohenSutherland(int &x1, int &y1, int &x2, int &y2) {
    // ... Cohen-Sutherland algorithm implementation ...
    int code1 = calculateRegionCode(x1, y1);
    int code2 = calculateRegionCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {
            // Both endpoints are inside the clipping window
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside on the same side
            break;
        } else {
            // Some part of the line is inside, clip against the window
            int codeOut = code1 ? code1 : code2;
            int x, y;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = calculateRegionCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = calculateRegionCode(x2, y2);
            }
        }
    }

    if (accept) {
        std::cout << "Accepted line segment: (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")\n";
    } else {
        std::cout << "Rejected line segment: (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")\n";
    }
}
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Gather user input
        int x1, y1, x2, y2;
        std::cout << "Enter x1 y1 x2 y2: ";
        std::cin >> x1 >> y1 >> x2 >> y2;

        // Broadcast the line segment coordinates to other processes
        int lineCoords[4] = {x1, y1, x2, y2};
        MPI_Bcast(lineCoords, 4, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        int lineCoords[4];
        MPI_Bcast(lineCoords, 4, MPI_INT, 0, MPI_COMM_WORLD);

        int x1 = lineCoords[0];
        int y1 = lineCoords[1];
        int x2 = lineCoords[2];
        int y2 = lineCoords[3];

        // Clip the line segment using Cohen-Sutherland
        cohenSutherland(x1, y1, x2, y2);

        // Create an SFML window
        sf::RenderWindow window(sf::VideoMode(800, 600), "MPI Line Clipping");

        // Create an SFML line
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
            sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red)
        };

        // Event loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
            window.draw(line, 2, sf::Lines);
            window.display();
        }
    }

    MPI_Finalize();
    return 0;
}


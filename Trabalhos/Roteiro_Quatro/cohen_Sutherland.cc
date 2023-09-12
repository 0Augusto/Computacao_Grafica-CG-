#include <iostream>
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

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "Please use at least 2 processes.\n";
        MPI_Finalize();
        return 1;
    }

    // Assuming master process is rank 0
    if (rank == 0) {
        // Line segment coordinates
        int x1 = 100, y1 = 200;
        int x2 = 900, y2 = 400;

        // Distribute line segment to workers
        for (int worker = 1; worker < size; ++worker) {
            MPI_Send(&x1, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
            MPI_Send(&y1, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
            MPI_Send(&x2, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
            MPI_Send(&y2, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
        }
    } else {
        int x1, y1, x2, y2;

        // Receive line segment from master
        MPI_Recv(&x1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&y1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&x2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&y2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Clip the line segment
        cohenSutherland(x1, y1, x2, y2);
    }

    MPI_Finalize();
    return 0;
}


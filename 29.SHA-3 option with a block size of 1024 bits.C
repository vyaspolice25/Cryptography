#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define LANES 64

bool allNonZero(uint64_t matrix[ROWS][COLS][LANES]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            for (int k = 0; k < LANES; ++k) {
                if (matrix[i][j][k] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    uint64_t state[ROWS][COLS][LANES] = {0};
    srand(time(NULL)); 

    int steps = 0;
    while (!allNonZero(state)) {
  
        int row = rand() % ROWS;
        int col = rand() % COLS;
        int lane = rand() % LANES;
        if (state[row][col][lane] == 0) {
            state[row][col][lane] = 1;
        }
        steps++;
    }

    printf("Number of steps until all lanes have at least one nonzero bit: %d\n", steps);

    return 0;
}

OUTPUT :

Number of steps until all lanes have at least one nonzero bit: 422467

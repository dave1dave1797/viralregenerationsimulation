#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 20
#define GENERATIONS 100

void printGrid(int grid[ROWS][COLS]) {
    system("clear"); 
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j] ? 'O' : '.');
        }
        printf("\n");
    }
}

int countLiveNeighbors(int grid[ROWS][COLS], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                count += grid[r][c];
            }
        }
    }
    return count;
}

void nextGeneration(int current[ROWS][COLS], int next[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countLiveNeighbors(current, i, j);
            if (current[i][j]) {
                next[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                next[i][j] = (neighbors == 3);
            }
        }
    }
}

void copyGrid(int src[ROWS][COLS], int dest[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            dest[i][j] = src[i][j];
}

void initializeGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = rand() % 2; 
}

int main() {
    int current[ROWS][COLS];
    int next[ROWS][COLS];

    initializeGrid(current);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        printGrid(current);
        nextGeneration(current, next);
        copyGrid(next, current);
        usleep(150000); 
    }

    return 0;
}
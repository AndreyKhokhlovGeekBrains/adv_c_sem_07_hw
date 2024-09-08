#include <stdio.h>
#include <windows.h>        // For handling console colors
#include "game_objects.h"   // To access the snake_t, food_container_t, etc.
#include "game_config.h"    // For MAX_X, MAX_Y, etc.
#include "utility.h"

void printSnake(snake_t snakes[], int num_snakes, food_container_t food_container) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    char matrix[MAX_Y][MAX_X];
    int food_positions[MAX_Y][MAX_X];

    // Initialize the matrix and food positions
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (i == 0 || i == MAX_Y - 1) {
                matrix[i][j] = '-';
            } else if (j == 0 || j == MAX_X - 1) {
                matrix[i][j] = '|';
            } else {
                matrix[i][j] = ' ';
            }
            food_positions[i][j] = -1; // -1 indicates no food at this position
        }
    }

    // Place all snakes in the matrix
    for (int s = 0; s < num_snakes; s++) {
        // Head of each snake
        matrix[snakes[s].y][snakes[s].x] = '@';

        // Tail of each snake
        for (size_t i = 0; i < snakes[s].tsize; i++) {
            matrix[snakes[s].tail[i].y][snakes[s].tail[i].x] = '*';  // Snake tail
        }
    }

    // Place the snake's food and mark their positions in the food_positions array
    for (size_t i = 0; i < food_container.fsize; i++) {
        int x = food_container.food_arr[i].x;
        int y = food_container.food_arr[i].y;
        matrix[y][x] = '$';
        food_positions[y][x] = food_container.food_arr[i].maturity; // Store maturity directly
    }
    
    // Print the matrix with colors using the precomputed food_positions array
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (matrix[i][j] == '$' && food_positions[i][j] != -1) {
                switch (food_positions[i][j]) {
                    case 0:
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
                        break;
                    case 1:
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
                        break;
                    case 2:
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
                        break;
                }
            } else {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset color to default
            }
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void printExit(snake_t snakes[], int snakes_num) {
    clearScreen();
    printf("Game over!\n");
    for (int i = 0; i < snakes_num; i++) {
        printf("Snake%d reached level: %d!\n", i+1, snakes[i].level);
        printf("\n");
    }
    
    
    exit(0);
}
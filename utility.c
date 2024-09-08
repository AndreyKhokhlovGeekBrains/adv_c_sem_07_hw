#include "utility.h"
#include "game_objects.h"
#include <conio.h>  // For kbhit() and getch() on Windows

int kbhit(void) {
    return _kbhit();
}

void clearScreen() {
    system("cls");
}

void pause_game() {
    while (1) {
        if (kbhit()) {
            char key = getch();
            if (key == 'p' || key == 'P') {
                break;
            }
        }
        Sleep(1000); // Sleep for a short time to prevent high CPU usage
    }
}

void cleanup(snake_t snakes[], int num_snakes, food_container_t *food_container) {
    // Free snake tails
    for (int i = 0; i < num_snakes; i++) {
        free(snakes[i].tail);
    }

    // Free food container array
    free(food_container->food_arr);
}

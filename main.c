#include "movement.h"
#include "ai.h"
#include "game_objects.h"
#include "utility.h"
#include "game_config.h"
#include "menu.h"
#include "game_render.h"

int main(void) {
    settings settings;
    startMenu(&settings);
    srand(time(NULL)); // Seed the random number generator. This ensures that the timing of food ripening is different each time you run the game.

    food_container_t food_container = initFood(32);
    snake_t snakes[MAX_SNAKES];

    int startX = 3;
    int startY = 11;

    for (int i = 0; i < settings.num_snakes; i++) {
        // Adjust starting positions to avoid overlap
        if (i == 1) {
            startX = 10;
            startY = 11;
        }
        if (i == 2) {
            startX = 10;
            startY = 3;
        }
        snakes[i] = initSnake(startX, startY, 1);
    }

    while (1) {
        for (int i = 0; i < settings.num_snakes; i++) {
            if (settings.gameMode == AUTOPILOT) {
                generateSnakeDirection(&snakes[i], food_container, settings.num_snakes);
            } else if (kbhit()) {
                get_direction(&snakes[i], settings.num_snakes);
            }

            move(&snakes[i]);
            if (check_head_position(&snakes[i])) {
                printExit(snakes, settings.num_snakes);
            }

            eat_food(&snakes[i], &food_container, settings.num_snakes);
        }

        updateFoodMaturity(&food_container);
        Sleep(snakes[0].speed);
        clearScreen();
        printSnake(snakes, settings.num_snakes, food_container);
    }

    cleanup(snakes, settings.num_snakes, &food_container);

    return 0;
} 

// mingw32-make
// .\snake_game.exe
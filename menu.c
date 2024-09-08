#include <stdio.h>
#include "game_config.h"   // To use constants like MAX_SNAKES
#include "game_objects.h"  // For the settings structure and gameMode enum

void startMenu(settings *settings) {
    int choice;
    printf("********************************\n");
    printf("*      Welcome to Snake Game   *\n");
    printf("********************************\n");
    
    printf("\nSelect Game Mode:\n");
    printf("1. Single Player\n");
    printf("2. Autopilot\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        settings->gameMode = SINGLE_PLAYER;
        settings->num_snakes = 1;
        printf("Single Player mode selected.\n");
    } else {
        settings->gameMode = AUTOPILOT;
        int num_snakes;
        printf("Enter number of snakes (1 to %d): ", MAX_SNAKES);
        scanf("%d", &num_snakes);
        if (num_snakes < 1 || num_snakes > MAX_SNAKES) {
            printf("Invalid number of snakes. Defaulting to 1.\n");
            num_snakes = 1;
        }
        // Set the number of snakes
        settings->num_snakes = num_snakes;
        printf("Autopilot mode selected with %d snake(s).\n", num_snakes);
    }
}

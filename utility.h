#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include "game_objects.h"
#define TRUE 1
#define FALSE 0

void clearScreen();
void pause_game();
int kbhit(void);
void cleanup(snake_t snakes[], int num_snakes, food_container_t *food_container);

#endif

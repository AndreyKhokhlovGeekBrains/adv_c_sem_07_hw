#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "game_objects.h"   // To access the snake_t, food_container_t

void printSnake(snake_t snakes[], int num_snakes, food_container_t food_container);
void printExit(snake_t snakes[], int snakes_num);

#endif

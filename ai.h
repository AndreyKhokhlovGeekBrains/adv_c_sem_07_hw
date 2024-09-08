#ifndef AI_H
#define AI_H

#include "game_objects.h"

_Bool check_safe_move(snake_t *snake, food_container_t *food_container, int next_x, int next_y);
void find_safe_move(snake_t *snake, food_container_t *food_container);
void generateSnakeDirection(snake_t *snake2, food_container_t food_container, int snakes_num);

#endif

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "game_objects.h"

void moveLeft(snake_t *snake);
void moveRight(snake_t *snake);
void moveUp(snake_t *snake);
void moveDown(snake_t *snake);
void move(snake_t *snake);
void get_direction(snake_t *snake, int snakes_num);
_Bool check_head_position(snake_t *snake);

#endif

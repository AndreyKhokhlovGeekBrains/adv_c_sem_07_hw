#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum { UP, DOWN, LEFT, RIGHT } direction;
typedef enum { SINGLE_PLAYER, AUTOPILOT } game_mode;

// Definitions for snake, food, etc.
typedef struct {
    int x;
    int y;
} tail_t;

typedef struct {
    int x;
    int y;
    int maturity;
    time_t next_maturity_time;
} food_t;

typedef struct {
    size_t fsize;
    food_t *food_arr;
    time_t last_update_time;
} food_container_t;

typedef struct {
    int x;
    int y;
    int level;
    int speed;
    tail_t *tail;
    size_t tsize;
    direction direction;
} snake_t;

typedef struct {
    game_mode gameMode;
    int num_snakes;
} settings;

// Function prototypes
snake_t initSnake(int x, int y, size_t tsize);
food_container_t initFood(size_t fsize);
void updateFoodMaturity(food_container_t *food_container);
void eat_food(snake_t *snake, food_container_t *food_container, int snakes_num);

#endif

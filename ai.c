#include "utility.h"
#include "ai.h"
#include "game_config.h"
#include "game_render.h"


_Bool check_safe_move(snake_t *snake, food_container_t *food_container, int next_x, int next_y) {
    // Check if the next position would collide with the snake's own tail
    for (size_t i = 0; i < snake->tsize; i++) {
        if (next_x == snake->tail[i].x && next_y == snake->tail[i].y) {
            return FALSE; // Unsafe move if next position is occupied by the tail
        }
    }

    // Check if the next position would collide with unripened food
    for (size_t i = 0; i < food_container->fsize; i++) {
        if (food_container->food_arr[i].maturity < 2 && 
            food_container->food_arr[i].x == next_x && 
            food_container->food_arr[i].y == next_y) {
            return FALSE; // Unsafe move if next position is occupied by unripened food
        }
    }

    return TRUE; // Safe move
}

void find_safe_move(snake_t *snake, food_container_t *food_container) {
    int next_x = snake->x;
    int next_y = snake->y;

    if( next_x < 2 && snake->direction == LEFT) {
        if (next_y < MAX_Y / 2) {
            snake->direction = DOWN;
            return;
        } else {
            snake->direction = UP;
            return;
        }
    }

    if( next_y < 2 && snake->direction == UP) {
        if (next_x < MAX_X / 2) {
            snake->direction = RIGHT;
            return;
        } else {
            snake->direction = LEFT;
            return;
        }
    }

    if( next_x > MAX_X - 3 && snake->direction == RIGHT) {
        if (next_y < MAX_Y / 2) {
            snake->direction = DOWN;
            return;
        } else {
            snake->direction = UP;
            return;
        }
    }

    if( next_y > MAX_Y - 3 && snake->direction == DOWN) {
        if (next_x < MAX_X / 2) {
            snake->direction = RIGHT;
            return;
        } else {
            snake->direction = LEFT;
            return;
        }
    }
    
    // Move based on current direction first
    switch(snake->direction) {
        case RIGHT:
            if (check_safe_move(snake, food_container, next_x + 1, next_y)) return;
            break;
        case LEFT:
            if (check_safe_move(snake, food_container, next_x - 1, next_y)) return;
            break;
        case UP:
            if (check_safe_move(snake, food_container, next_x, next_y - 1)) return;
            break;
        case DOWN:
            if (check_safe_move(snake, food_container, next_x, next_y + 1)) return;
            break;
    }
    
    // If current direction is blocked, try others
    if (check_safe_move(snake, food_container, next_x - 1, next_y)) {
        snake->direction = LEFT;
        return;
    }
    if (check_safe_move(snake, food_container, next_x + 1, next_y)) {
        snake->direction = RIGHT;
        return;
    }
    if (check_safe_move(snake, food_container, next_x, next_y - 1)) {
        snake->direction = UP;
        return;
    }
    if (check_safe_move(snake, food_container, next_x, next_y + 1)) {
        snake->direction = DOWN;
        return;
    }
}

void generateSnakeDirection(snake_t *snake2, food_container_t food_container, int snakes_num) {
    if (snake2 == NULL) {
        return;
    }

    // If no food, just find a safe move
    if (food_container.fsize == 0) {
        printExit(snake2, snakes_num);
    }

    // Step 1: Find the nearest ripened food item (maturity = 2)
    food_t *nearest_food_item = NULL;
    int min_distance = INT_MAX;

    for (size_t i = 0; i < food_container.fsize; i++) {
        if (food_container.food_arr[i].maturity == 2) {
            int dist_x = abs(snake2->x - food_container.food_arr[i].x);
            int dist_y = abs(snake2->y - food_container.food_arr[i].y);
            int distance = dist_x + dist_y; // Manhattan distance

            if (distance < min_distance) {
                min_distance = distance;
                nearest_food_item = &food_container.food_arr[i];
            }
        }
    }

    // Step 2: If no ripened food is found, find a safe move
    if (nearest_food_item == NULL) {
        find_safe_move(snake2, &food_container);
        return;
    }

    // Step 3: Determine the direction based on the nearest food item's position
    int x_diff = nearest_food_item->x - snake2->x;
    int y_diff = nearest_food_item->y - snake2->y;

    // Step 4: Prioritize x-axis movement if absolute x difference is larger, otherwise prioritize y-axis
    int next_x = snake2->x;
    int next_y = snake2->y;

    if (abs(x_diff) > abs(y_diff)) {
        next_x = (x_diff > 0) ? snake2->x + 1 : snake2->x - 1; // Right or Left
    } else {
        next_y = (y_diff > 0) ? snake2->y + 1 : snake2->y - 1; // Down or Up
    }

    // Step 5: Check if the proposed move is safe
    if (check_safe_move(snake2, &food_container, next_x, next_y)) {
        // Step 6: Set direction based on the chosen move
        if (next_x > snake2->x) {
            snake2->direction = RIGHT;
        } else if (next_x < snake2->x) {
            snake2->direction = LEFT;
        } else if (next_y > snake2->y) {
            snake2->direction = DOWN;
        } else if (next_y < snake2->y) {
            snake2->direction = UP;
        }
    } else {
        // If the chosen move is not safe, find another safe move
        find_safe_move(snake2, &food_container);
    }
}
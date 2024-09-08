#include "game_objects.h"
#include "game_config.h"
#include "game_render.h"

snake_t initSnake(int x, int y, size_t tsize) {
    snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.level = 0;
    snake.speed = 400;
    snake.tsize = tsize;
    
    snake.tail = (tail_t*)malloc(sizeof(tail_t) * 100); // Grows up to 100 elements
    for(size_t i = 0; i < tsize; i++) {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.direction = RIGHT;
    return snake;
}

food_container_t initFood(size_t fsize){
    food_container_t food_container;
    food_container.fsize = fsize;
    food_container.food_arr = (food_t*)malloc(sizeof(food_t) * fsize); // Allocate based on fsize
    food_container.last_update_time = time(NULL);

    size_t index = 0;
    for(size_t i = 3; i < MAX_X - 1; i+=3) {
        for(size_t j = 1; j < MAX_Y - 2; j++) {
            if (j != 1 && j != 6 && index < 32) {
                food_container.food_arr[index].x = i;
                food_container.food_arr[index].y = j;
                food_container.food_arr[index].maturity = 0;
                food_container.food_arr[index].next_maturity_time = time(NULL) + (rand() % 10 + 1); // Random time within 10 seconds
                index++;
            }
        }
    }
    return food_container;
}

void updateFoodMaturity(food_container_t *food_container) {
    time_t current_time = time(NULL); // Get current time
    for (size_t i = 0; i < food_container->fsize; i++) {
        if (current_time >= food_container->food_arr[i].next_maturity_time) {
            if (food_container->food_arr[i].maturity < 2) {
                food_container->food_arr[i].maturity++;
            }
            food_container->food_arr[i].next_maturity_time = current_time + (rand() % 20 + 5);
        }
    }
}

void eat_food(snake_t *snake, food_container_t *food_container, int snakes_num) {
    for(size_t i = 0; i < food_container->fsize; i++) {
        if(snake->x == food_container->food_arr[i].x && snake->y == food_container->food_arr[i].y) {
            if(food_container->food_arr[i].maturity < 2) {
                printExit(snake, snakes_num);
            }

            snake->tsize++;
            snake->tail[snake->tsize - 1] = snake->tail[snake->tsize - 2];

            snake->level++;
            snake->speed -= (int)(20 / log(snake->level + 1));
            for(size_t j = i; j < food_container->fsize - 1; j++) {
                food_container->food_arr[j] = food_container->food_arr[j + 1];
            }
            food_container->fsize--;
            break;
        }
    }
}

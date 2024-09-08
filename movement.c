#include <conio.h>
#include "utility.h"
#include "movement.h"
#include "game_config.h"
#include "game_render.h"

// Snake movement functions
void moveLeft(snake_t *snake) {
    if(snake->x > 0) {
        snake->x -= 1;
    }
}

void moveRight(snake_t *snake) {
    if(snake->x < MAX_X - 1) {
        snake->x += 1;
    }
}

void moveUp(snake_t *snake) {
    if(snake->y > 0) {
        snake->y -= 1;
    }
}

void moveDown(snake_t *snake) {
    if(snake->y < MAX_Y - 1) {
        snake->y += 1;
    }
}

void move(snake_t *snake) {
    for(int i = snake->tsize - 1; i > 0; i--) {
        snake->tail[i] = snake->tail[i-1];
    }

    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;

    switch (snake->direction) {
        case LEFT:
            moveLeft(snake);
            break;
        case RIGHT:
            moveRight(snake);
            break;
        case UP:
            moveUp(snake);
            break;
        case DOWN:
            moveDown(snake);
            break;
    }
}

void get_direction(snake_t *snake, int snakes_num) {
    char key = getch();
    
    switch (key) {
        case 'a':
            if (snake->direction != RIGHT)
                snake->direction = LEFT;
            break;
        case 'd':
            if (snake->direction != LEFT)
                snake->direction = RIGHT;
            break;
        case 'w':
            if (snake->direction != DOWN)
                snake->direction = UP;
            break;
        case 's':
            if (snake->direction != UP)
                snake->direction = DOWN;
            break;
        case 'c':
            printExit(snake, snakes_num);
            break;
        case 'p':
            pause_game();
            break;
        default:
            // Do nothing for other keys
            break;
    }
}

// Check if the next position would collide with the snake's own tail
_Bool check_head_position(snake_t *snake) {
    for(size_t i = 0; i < snake->tsize; i++) {
        if(snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
            return TRUE;
        }
    }
    return FALSE;
}

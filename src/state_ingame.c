#include <curses.h>
#include <stdlib.h>

#include "keyboard.h"
#include "snake.h"

snake *s;
segment *old_tail;
float secs_since_last_advance;
bool snake_moved;

void ingame_init() {
    s = snake_new(10, 10, 1);
    snake_moved = true;
}

void ingame_destroy() {

}

void ingame_update(float dt) {
    char c = get_last_char();
    if (c != '\0') {
        switch (c) {
            case 'w':
                s->dir = DIR_U;
                break;

            case 'a':
                s->dir = DIR_L;
                break;

            case 's':
                s->dir = DIR_D;
                break;

            case 'd':
                s->dir = DIR_R;
                break;
        }
    }

    secs_since_last_advance += dt;
    if (secs_since_last_advance > 0.1f) {
        snake_advance(s, old_tail);
        snake_moved = true;
        secs_since_last_advance -= 0.1f;
    }
}

void ingame_render() {
    if (snake_moved) {
        snake_draw(s, 1, 1);
        refresh();
    }
}

void ingame_screen_resized() {

}

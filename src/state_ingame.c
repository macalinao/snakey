#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "clock.h"
#include "defines.h"
#include "keyboard.h"
#include "snake.h"
#include "util.h"

snake *s;
segment *old_tail;
float secs_since_last_advance;
bool snake_moved;

void ingame_init() {
    s = snake_new(10, 10, 1);
    snake_moved = false;
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
    if (secs_since_last_advance > 0.05f) {
        snake_advance(s, &old_tail);
        snake_moved = true;
        secs_since_last_advance -= 0.05f;
    }
}

void ingame_render() {
    if (snake_moved) {
        mvaddch(old_tail->y + 1, old_tail->x + 1, ' ');
        snake_draw(s, 1, 1);
        refresh();

        snake_moved = false;

        free(old_tail);
    }
}

void ingame_screen_resized() {

}

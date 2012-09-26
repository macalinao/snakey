#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "keyboard.h"
#include "screen.h"
#include "sound.h"

#include "state_title.h"

#define FPS 20
#define FPS_MS (int) (1000 / FPS)

#define STATE_TITLE 0
#define STATE_INGAME 1

int gamestate;

/**
 * Represents a segment of a snake.
 */
typedef struct {
    int x;
    int y;
} segment;

/**
 * Represents a snake.
 */
typedef struct {
    segment parts[1000];
} snake;

void init() {
    // Initial game state
    gamestate = STATE_TITLE;

    init_screen();
    init_sounds();
    init_keyboard();
}

/**
 * Destroy the display and make things go back to normal.
 */
void destroy() {
    destroy_keyboard();
    destroy_screen();
}

void update(float dt) {
    update_sounds();
}

void render() {
    if (gamestate == STATE_TITLE) {
        render_title();
    }
}

int main() {
    init();

    int last = clock();
    while (true) {
        int now = clock();
        int delta = now - last;
        last = now;
        float secs = (float) now / CLOCKS_PER_SEC;

        int ms = (int) (secs * 1000);
        if (ms < FPS_MS) {
            usleep(FPS_MS - ms);
        }

        poll_keyboard();

        if (update_window_size()) {
            redraw_boundaries();
            title_drawn = false;
        }
        update(secs);

        // Rendering
        render();
        refresh();
    }
    destroy();
    return 0;
}

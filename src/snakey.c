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

void set_state(int state) {
    switch (gamestate) {
        case STATE_TITLE: destroy_title(); break;
        default: break;
    }

    switch (state) {
        case STATE_TITLE: init_title(); break;
        default: break;
    }

    gamestate = state;
}

void init() {
    gamestate = -1;

    init_screen();
    sound_init();
    init_keyboard();

    set_state(STATE_TITLE);
}

/**
 * Destroy the display and make things go back to normal.
 */
void destroy() {
    destroy_keyboard();
    destroy_screen();
}

void update(float dt) {
    poll_keyboard();        
    if (update_window_size()) {
        redraw_boundaries();
        title_drawn = false;
    }
    switch (gamestate) {
        case STATE_TITLE: update_title(dt); break;
    }
}

void render() {
    switch (gamestate) {
        case STATE_TITLE: render_title(); break;
    }
    
    // Draw the changes
    refresh();
}

void signal_callback_handler(int signum) {
   destroy();
   exit(0);
}

int main() {
    signal(SIGINT, signal_callback_handler);

    init();

    int last = clock();
    while (true) {
        int now = clock();
        int delta = now - last;
        last = now;
        float secs = (float) delta / CLOCKS_PER_SEC;

        int ms = (int) (secs * 1000);
        if (ms < FPS_MS) {
            usleep(FPS_MS - ms);
        }

        update(secs);
        render();
    }
    destroy();
    return 0;
}

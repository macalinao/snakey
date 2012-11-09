#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "defines.h"

#include "clock.h"
#include "keyboard.h"
#include "screen.h"
#include "sound.h"

#include "state_title.h"
#include "state_ingame.h"
#include "state_gameover.h"

int gamestate;

void destroy();

void set_state(int state) {
    if (state == STATE_QUIT) {
        destroy();
        exit(0);
    }

    switch (gamestate) {
        case STATE_TITLE: state_title_destroy(); break;
        case STATE_INGAME: state_ingame_destroy(); break;
        case STATE_GAMEOVER: state_gameover_destroy(); break;
        default: break;
    }

    clear();

    gamestate = state;

    switch (gamestate) {
        case STATE_TITLE: state_title_init(); break;
        case STATE_INGAME: state_ingame_init(); break;
        case STATE_GAMEOVER: state_gameover_init(); break;
        default: break;
    }
}

void init() {
    gamestate = -1;

    init_screen();
    sound_init();
    init_keyboard();

    set_state(STATE_TITLE);

    clock_start();
}

/**
 * Destroy the display and make things go back to normal.
 */
void destroy() {
    destroy_keyboard();
    destroy_screen();
}

void update() {
    float dt = clock_update();

    poll_keyboard();        
    if (update_window_size()) {
        switch (gamestate) {
            case STATE_TITLE: state_title_screen_resized(); break;
            case STATE_INGAME: state_ingame_screen_resized(); break;
            case STATE_GAMEOVER: state_gameover_screen_resized(); break;
        }
    }
    switch (gamestate) {
        case STATE_TITLE: state_title_update(dt); break;
        case STATE_INGAME: state_ingame_update(dt); break;
        case STATE_GAMEOVER: state_gameover_update(dt); break;
    }
}

void render() {
    switch (gamestate) {
        case STATE_TITLE: state_title_render(); break;
        case STATE_INGAME: state_ingame_render(); break;
        case STATE_GAMEOVER: state_gameover_render(); break;
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

    while (true) {
        update();
        render();
    }

    destroy();

    return 0;
}

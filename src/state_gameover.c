#include <curses.h>

#include "defines.h"
#include "keyboard.h"
#include "screen.h"
#include "snakey.h"
#include "sound.h"

void draw_gameover() {
    int menu_top = get_rows() / 2;
    int colstart = (get_cols() / 2) - 14;

    attron(COLOR_PAIR(3));
    mvprintw(menu_top, colstart, "G A M E   O V E R");
    attroff(COLOR_PAIR(3));
}

void state_gameover_init() {
    sound_play(SOUND_GAMEOVER);
    draw_gameover();
}

void state_gameover_destroy() {
    if (!sound_is_done(SOUND_GAMEOVER)) {
        sound_stop(SOUND_GAMEOVER);
    }
}

void state_gameover_update() {
    if (get_last_char() == ' ') {
        set_state(STATE_GAMEOVER);
    }
}

void state_gameover_render() {
    
}

void state_gameover_screen_resized() {
    draw_gameover();
}

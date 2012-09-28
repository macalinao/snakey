#include <curses.h>

#include "defines.h"
#include "keyboard.h"
#include "screen.h"
#include "snakey.h"
#include "sound.h"

#define SEL_START 0
#define SEL_HS 1
#define SEL_CREDS 2
#define SEL_QUIT 3

int current_selection;
int menu_top;

bool title_drawn;
bool menu_drawn;

void draw_title() {
    attron(COLOR_PAIR(2));

    int rows = get_rows();
    int cols = get_cols();

    int toplogo = rows / 4;
    int logoleft = (cols / 2) - 32;

    mvprintw(toplogo, logoleft, "  _________ _______      _____   ____  __.________________.___.");
    mvprintw(toplogo + 1, logoleft, " /   _____/ \\      \\    /  _  \\ |    |/ _|\\_   _____/\\__  |   |");
    mvprintw(toplogo + 2, logoleft, " \\_____  \\  /   |   \\  /  /_\\  \\|      <   |    __)_  /   |   |");
    mvprintw(toplogo + 3, logoleft, " /        \\/    |    \\/    |    \\    |  \\  |        \\ \\____   |");
    mvprintw(toplogo + 4, logoleft, "/_______  /\\____|__  /\\____|__  /____|__ \\/_______  / / ______|");
    mvprintw(toplogo + 5, logoleft, "        \\/         \\/         \\/        \\/        \\/  \\/       ");

    attroff(COLOR_PAIR(2));
}

void draw_menu() {
    menu_top = get_rows() - (get_rows() / 4) - 3;
    int colstart = (get_cols() / 2) - 14;

    attron(COLOR_PAIR(3));

    if (current_selection == SEL_START) {
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(menu_top,     colstart, ">       S T A R T       <");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
    } else {
        mvprintw(menu_top,     colstart, "        S T A R T        ");
    }

    if (current_selection == SEL_HS) {
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(menu_top + 2, colstart, "> H I G H   S C O R E S <");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
    } else {
        mvprintw(menu_top + 2, colstart, "  H I G H   S C O R E S  ");
    }

    if (current_selection == SEL_CREDS) {
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(menu_top + 4, colstart, ">     C R E D I T S     <");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
    } else {
        mvprintw(menu_top + 4, colstart, "      C R E D I T S      ");
    }

    if (current_selection == SEL_QUIT) {
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(menu_top + 6, colstart, ">        Q U I T        <");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
    } else {
        mvprintw(menu_top + 6, colstart, "         Q U I T         ");
    }

    attroff(COLOR_PAIR(3));
}

void redraw_boundaries() {
    int rows = get_rows();
    int cols = get_cols();

    clear();

    attron(COLOR_PAIR(1));

    int i;
    for (i = 0; i <= cols; i++) {
        move(0, i);
        addch('+');

        move(rows - 1, i);
        addch('+');
    }

    for (i = 1; i < rows; i++) {
        move(i, 0);
        addch('+');

        move(i, cols - 1);
        addch('+');
    }

    attroff(COLOR_PAIR(1));
}

void menu_select() {
    switch (current_selection) {
        case SEL_QUIT:
            set_state(STATE_QUIT);
            break;
    }
}

void title_init() {
    current_selection = 0;
    sound_play(SOUND_TITLE);
}

void title_destroy() {

}

void title_update(float dt) {
    if (!sound_is_done(SOUND_TITLE)) return;

    char last = get_last_char();
    if (last != '\0') {
        int move = 0;
        switch (last) {
            case 'j': move = 1; break;
            case 'k': move = -1; break;
            case ' ': menu_select(); return;
        }
        current_selection += move;
        if (current_selection == -1) {
            current_selection = 3;
        }

        if (current_selection == 4) {
            current_selection = 0;
        }
        menu_drawn = false;
        sound_play(SOUND_CLICK);
    }
}

void title_render() {
    if (!title_drawn) {
        draw_title();
        title_drawn = true;
    }

    if (!menu_drawn) {
        draw_menu();
        menu_drawn = true;
    }
}

void title_screen_resized() {
    redraw_boundaries();
    title_drawn = false;
    menu_drawn = false;
}

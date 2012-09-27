#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

bool window_changed;
int cols;
int rows;

bool init_colors() {
    if (!has_colors()) {
        return false;
    }

    start_color();

    // Let's define our colors
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    return true;
}

void init_screen() {
    // Start the screen
    initscr();

    // Remove cursor
    curs_set(0);

    if (!init_colors()) {
        endwin();
        printf("Your terminal unfortunately does not support colors. What a shame.");
        exit(1);
    }
}

void destroy_screen() {
    curs_set(1);
    endwin();
}

struct winsize get_window_size() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

bool update_window_size() {
    struct winsize w = get_window_size();
    bool ret = (cols != w.ws_col || rows != w.ws_row);
    cols = w.ws_col;
    rows = w.ws_row;
    return ret;
}

int get_rows() {
    return rows;
}

int get_cols() {
    return cols;
}

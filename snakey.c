#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#include "bloopsaphone/bloopsaphone.h"

#define FPS 4
#define FPS_MS (int) (1000 / FPS)

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

bool window_changed;
int cols;
int rows;

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

void redraw_boundaries() {
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

void update(float dt) {
}

void render() {
}

int main() {
    initscr();

    if (!has_colors()) {
        endwin();
        printf("Your terminal unfortunately does not support colors. What a shame.");
        exit(1);
    }

    start_color();

    // Let's define our colors
    init_pair(1, COLOR_RED, COLOR_BLACK);

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

        if (update_window_size()) {
            redraw_boundaries();
        }
        update(secs);

        // Rendering
        render();
        refresh();
    }

    endwin();
    return 0;
}

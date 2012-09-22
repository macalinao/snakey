#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "../bloopsaphone/c/bloopsaphone.h"

#define FPS 20
#define FPS_MS (int) (1000 / FPS)

#define NB_ENABLE 0
#define NB_DISABLE 1

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

int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

/**
 * We're non-blocking
 * @param state [description]
 */
void nonblock(int state) {
    struct termios ttystate;
 
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
 
    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
 
}

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

void draw_title() {
    attron(COLOR_PAIR(2));

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

char c;

bool init_colors() {
    if (!has_colors()) {
        return false;
    }

    start_color();

    // Let's define our colors
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    return true;
}

bloops *B;
bloopsaphone *square;

void init_sounds() {
    B = bloops_new();

    square = bloops_square();
    square->params.punch = 123.23;
    square->params.freq = 440;
    square->params.vibe = 123.23;

    bloops_track2(B, square, "- 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G \
                                16:A 8:B + 16:C 8:D 12:E 12:E 12:E \
                                E - E + E - E + D - D D 12:D 12:D 12:D 1:E");
    bloops_track2(B, square, "- 2 8:E 16:F# 8:G# 16:A 8:B 8:E 16:F# 8:G# 16:A 8:B \
                                + 16:C# 8:D# 16:E 8:F# 12:G# 12:G# 12:G# \
                                2:B 2:B 2:A 4:A 12:A 12:A 12:A 1:B");
    bloops_track2(B, square, "- 1 8:G 16:A 8:B + 16:C 8:D \
                                16:E 8:F# 16:G 8:A 12:B 12:B 12:B \
                                12:E 12:G# 12:B + 12:E - 12:B 12:G# 12:G# 12:B + 12:E 12:G# 12:B + 12:E \
                                12:D - 12:A 12:F# 12:D 12:F# 12:A + 12:D - 12:F# 12:D 12:A - 12:F# 12:F# 1:G#");

    bloops_play(B);
}

void init() {
    // Initial game state
    gamestate = STATE_TITLE;

    // Start the screen
    initscr();

    // Remove cursor
    curs_set(0);

    if (!init_colors()) {
        endwin();
        printf("Your terminal unfortunately does not support colors. What a shame.");
        exit(1);
    }
    init_sounds();

    nonblock(NB_ENABLE);
}

/**
 * Destroy the display and make things go back to normal.
 */
void destroy() {
    nonblock(NB_DISABLE);

    curs_set(1);
    endwin();
}

void update_sounds() {
    if (bloops_is_done(B)) {
        bloops_play(B);
    }
}

void update(float dt) {
    update_sounds();
}

bool title_drawn;
void render() {
    if (gamestate == STATE_TITLE && !title_drawn) {
        draw_title();
        title_drawn = true;
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

        if (kbhit()) {
            c = fgetc(stdin);
            if (c == 'q') {
                break;
            }
        } else {
            c = '\0';
        }

        if (update_window_size()) {
            redraw_boundaries();
        }
        update(secs);

        // Rendering
        render();
        refresh();
    }
    destroy();
    return 0;
}

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "screen.h"
#include "sound.h"

#include "state_title.h"

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

char c;

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

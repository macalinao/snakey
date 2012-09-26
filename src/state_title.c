#include <curses.h>

#include "screen.h"

bool title_drawn;

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

    int botlogo = rows - toplogo;
    int colsdiv2 = (cols / 2);

    attron(COLOR_PAIR(3));

    mvprintw(botlogo, colsdiv2 - 5, "S T A R T");
    mvprintw(botlogo + 2, colsdiv2 - 12, "H I G H   S C O R E S");
    mvprintw(botlogo + 4, colsdiv2 - 7, "C R E D I T S");

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

void update_title(float dt) {

}

void render_title() {
    if (!title_drawn) {
        draw_title();
        title_drawn = true;
    }
}

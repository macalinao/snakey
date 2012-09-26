#include <stdbool.h>
#include <termios.h>

struct screen {
    int rows;
    int columns;
} the_screen;

void init_screen();

void destroy_screen();

struct winsize get_window_size();

bool update_window_size();

int get_rows();

int get_cols();

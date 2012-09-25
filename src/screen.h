#include <stdbool.h>
#include <termios.h>

struct screen {
    int rows;
    int columns;
} the_screen;

int cols;
int rows;

struct winsize get_window_size();

bool update_window_size();

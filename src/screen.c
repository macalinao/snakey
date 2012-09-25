#include <sys/ioctl.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

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

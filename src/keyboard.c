#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#define NB_ENABLE 0
#define NB_DISABLE 1

/**
 * Keyboard hit.
 * @return [description]
 */
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

void init_keyboard() {
    nonblock(NB_ENABLE);
}

void destroy_keyboard() {
    nonblock(NB_DISABLE);
}

void poll_keyboard() {
    if (kbhit()) {
        c = fgetc(stdin);
    } else {
        c = '\0';
    }
}

/**
 * Gets the last char typed into the console.
 * @return The last character.
 */
char get_last_char() {
    return c;
}

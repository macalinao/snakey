#include <time.h>
#include <unistd.h>

#include "defines.h"

int last;

void clock_start() {
    last = clock();
}

float clock_update() {
    int now = clock();
    int delta = now - last;
    last = now;
    float secs = (float) delta / CLOCKS_PER_SEC;

    int ms = (int) (secs * 1000);
    if (ms < FPS_MS) {
        usleep(FPS_MS - ms);
    }

    return secs;
}

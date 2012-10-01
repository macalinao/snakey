#include <sys/time.h>
#include <unistd.h>

#include "defines.h"

struct timeval last;

struct timeval get_now() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t;
}

void clock_start() {
    last = get_now();
}

float clock_update() {
    struct timeval now =  get_now();
    int deltas = now.tv_sec - last.tv_sec;
    int deltau = now.tv_usec - last.tv_usec;
    last = now;

    float delta = deltas + ((float) deltau / 1000000);

    if (delta < SECS_PER_FRAME) {
        usleep((int) ((SECS_PER_FRAME - delta) * 1000000));
    }

    return delta;
}

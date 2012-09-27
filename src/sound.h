#include <stdbool.h>

#define SOUND_TITLE 0
#define SOUND_CLICK 1

void sound_init();

void sound_play(int sound);

bool sound_is_done(int sound);

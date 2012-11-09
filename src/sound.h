#include <stdbool.h>

#define SOUND_TITLE 0
#define SOUND_CLICK 1
#define SOUND_GAMEOVER 2

/**
 * Initializes sound.
 */
void sound_init();

/**
 * Plays a sound.
 * @param sound [description]
 */
void sound_play(int sound);

/**
 * Stops a sound.
 * @param sound [description]
 */
void sound_stop(int sound);

/**
 * Checks if the given sound is done playing.
 * @param  sound [description]
 * @return       [description]
 */
bool sound_is_done(int sound);

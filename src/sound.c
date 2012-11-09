#include "defines.h"

#include "sound.h"

#include "../bloopsaphone/c/bloopsaphone.h"

bloopsaphone *square;

bloops* sounds[10];

void load_instruments() {
    square = bloops_square();
}

void load_sounds() {
    // TITLE
    sounds[SOUND_TITLE] = bloops_new();
    bloops_track2(sounds[SOUND_TITLE], square, "- 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G \
                                16:A 8:B + 16:C 8:D 12:E 12:E 12:E \
                                E - E + E - E + D - D D 12:D 12:D 12:D 1:E");
    bloops_track2(sounds[SOUND_TITLE], square, "- 2 8:E 16:F# 8:G# 16:A 8:B 8:E 16:F# 8:G# 16:A 8:B \
                                + 16:C# 8:D# 16:E 8:F# 12:G# 12:G# 12:G# \
                                2:B 2:B 2:A 4:A 12:A 12:A 12:A 1:B");
    bloops_track2(sounds[SOUND_TITLE], square, "- 1 8:G 16:A 8:B + 16:C 8:D \
                                16:E 8:F# 16:G 8:A 12:B 12:B 12:B \
                                12:E 12:G# 12:B + 12:E - 12:B 12:G# 12:G# 12:B + 12:E 12:G# 12:B + 12:E \
                                12:D - 12:A 12:F# 12:D 12:F# 12:A + 12:D - 12:F# 12:D 12:A - 12:F# 12:F# 1:G#");
    
    // CLICK
    sounds[SOUND_CLICK] = bloops_new();
    bloops_track2(sounds[SOUND_CLICK], square, "+ + 32:C 32:E");

    // GAMEOVER
    sounds[SOUND_GAMEOVER] = bloops_new();
    bloops_track2(sounds[SOUND_GAMEOVER], square, "8:C - 8:B 8:A# 8:A 1:G#");
}

#if SOUND_ENABLE

void sound_init() {
    load_instruments();
    load_sounds();
}

void sound_play(int sound) {
    bloops_play(sounds[sound]);
}

void sound_stop(int sound) {
    bloops_stop(sounds[sound]);
}

bool sound_is_done(int sound) {
    return (bool) bloops_is_done(sounds[sound]);
}

#else

void sound_init() {}
void sound_play(int sound) {}
void sound_stop(int sound) {}
bool sound_is_done(int sound) { return true; }

#endif

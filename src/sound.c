#include "../bloopsaphone/c/bloopsaphone.h"

bloops *B;
bloopsaphone *square;

void init_sounds() {
    B = bloops_new();

    square = bloops_square();
    square->params.punch = 123.23;
    square->params.freq = 440;
    square->params.vibe = 123.23;

    bloops_track2(B, square, "- 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G 8:C 16:D 8:E 16:F 8:G \
                                16:A 8:B + 16:C 8:D 12:E 12:E 12:E \
                                E - E + E - E + D - D D 12:D 12:D 12:D 1:E");
    bloops_track2(B, square, "- 2 8:E 16:F# 8:G# 16:A 8:B 8:E 16:F# 8:G# 16:A 8:B \
                                + 16:C# 8:D# 16:E 8:F# 12:G# 12:G# 12:G# \
                                2:B 2:B 2:A 4:A 12:A 12:A 12:A 1:B");
    bloops_track2(B, square, "- 1 8:G 16:A 8:B + 16:C 8:D \
                                16:E 8:F# 16:G 8:A 12:B 12:B 12:B \
                                12:E 12:G# 12:B + 12:E - 12:B 12:G# 12:G# 12:B + 12:E 12:G# 12:B + 12:E \
                                12:D - 12:A 12:F# 12:D 12:F# 12:A + 12:D - 12:F# 12:D 12:A - 12:F# 12:F# 1:G#");

    bloops_play(B);
}

void update_sounds() {
    if (bloops_is_done(B)) {
        bloops_play(B);
    }
}

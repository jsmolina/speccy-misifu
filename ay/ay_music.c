#include "ay_music.h"

extern uint8_t ay_song_03_alleycat[];

void initialize_ay() {
    vt_init(ay_song_03_alleycat);
}

void keep_playing() {
    vt_play();
}

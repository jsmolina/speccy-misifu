#include "ay_music.h"

extern uint8_t music_module[];

void initialize_ay() {
    vt_init(music_module);
}

void keep_playing() {
    vt_play();
}

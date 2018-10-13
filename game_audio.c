/*
        This file is part of Gandalf.

        Pietro Bros is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        Pietro Bros is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with Gandalf.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <arch/zx.h>
#include <intrinsic.h>
#include <stdlib.h>
#include <string.h>
#include <z80.h>
#include "game_ay.h"


void audio_ingame(void) {

  ay_song_play(AY_SONG_LOOP, 3, ay_song_03_alleycat);
}

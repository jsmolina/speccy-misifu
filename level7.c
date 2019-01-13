#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_dog1[] = {0x0, 0xf, 0x1f, 0x3f, 0x7f, 0x8f, 0x3e, 0x60};
const uint8_t udg_dog1m[] = {0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0};
const uint8_t udg_dog2[] = {0x0, 0xb3, 0xde, 0xef, 0xef, 0xcf, 0xe6, 0x31};
const uint8_t udg_dogmilk[] = {0x3c, 0x66, 0xc3, 0x81, 0xc3, 0xff, 0x7e, 0x3c};

// https://user-images.githubusercontent.com/447481/51000354-2598e700-152d-11e9-86ac-7106cfed0137.png

void print_a_dog(uint8_t row, uint8_t col) {
    // sp1_PrintAt(uint16_t row,uint16_t col
    sp1_PrintAt(row, col, INK_WHITE | PAPER_MAGENTA, 'C');
    sp1_PrintAt(row, col + 1, INK_WHITE | PAPER_MAGENTA, 'D');
    sp1_PrintAt(row, col + 2, INK_WHITE | PAPER_MAGENTA, 'E');
    sp1_PrintAt(row, col + 3, INK_BLUE | PAPER_MAGENTA, 'O');
}

void  print_background_level7() {
 sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_MAGENTA,
                  ' ' );
  level = 7;

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('C', udg_dog1);
  sp1_TileEntry('D', udg_dog1m);
  sp1_TileEntry('E', udg_dog2);
  sp1_TileEntry('O', udg_dogmilk);

  level_x_max = 27;
  level_x_min = 1;

  print_room_walls(20, PAPER_MAGENTA, INK_CYAN);

  print_a_dog(FLOOR_Y + 1, 8);

  reset_misifu_position();
}


void level7_loop() {

}
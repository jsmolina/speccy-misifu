#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_birdcage1[] = {0xf, 0xf0, 0xc0, 0xff, 0xc0, 0xf0, 0xff, 0xf};
const uint8_t udg_birdcage2[] = {0xf0, 0xf, 0x3, 0xff, 0x3, 0xf, 0xff, 0xf0};

void  print_background_level6() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_GREEN | PAPER_RED,
                  ' ' );
  sp1_Invalidate(&full_screen);
  level = 6;
  define_silla_udgs();
  sp1_TileEntry('A', udg_birdcage1);
  sp1_TileEntry('B', udg_birdcage2);
  level_x_max = 28;
  level_x_min = 0;

  print_room_walls(20, PAPER_RED, INK_GREEN);
  // paint the chair
  paint_chair(17, 22, PAPER_RED, INK_GREEN);
  paint_table(17, 26, PAPER_RED, INK_GREEN);
  // 18, 27
  sp1_PrintAt(17, 26, INK_GREEN | PAPER_RED, 'A');
  sp1_PrintAt(17, 27, INK_GREEN | PAPER_RED, 'B');
  reset_misifu_position();
}

void level6_loop() {
    dog_checks();
    move_broom();

    check_chair_and_table();
    // bincat_appears, bincat_in_bin
    detect_cat_in_window(0);
}

#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_birdcage1[] = {0xf, 0xf0, 0xc0, 0xff, 0xc0, 0xf0, 0xff, 0xf};
const uint8_t udg_birdcage2[] = {0xf0, 0xf, 0x3, 0xff, 0x3, 0xf, 0xff, 0xf0};
const uint8_t udg_bird[] = {0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff};
const uint8_t udg_bird2[] = {0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff};

void  print_background_level6() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_GREEN | PAPER_RED,
                  ' ' );
  sp1_Invalidate(&full_screen);
  level = 6;
  define_silla_udgs();
  sp1_TileEntry('A', udg_birdcage1);
  sp1_TileEntry('B', udg_birdcage2);
  sp1_TileEntry('C', udg_bird);
  sp1_TileEntry('D', udg_bird2);
  level_x_max = 27;
  level_x_min = 0;

  print_room_walls(20, PAPER_RED, INK_GREEN);
  // paint the chair
  paint_chair(17, 22, PAPER_RED, INK_GREEN);
  paint_table(17, 26, PAPER_RED, INK_GREEN);
  // 18, 27
  sp1_PrintAt(17, 26, INK_GREEN | PAPER_RED, 'A');
  sp1_PrintAt(17, 27, INK_GREEN | PAPER_RED, 'B');
  reset_misifu_position();
  // cage is in 25 position
  windows[0].x = 25;
  windows[0].has_item = 'B'; // bird is inside cage
}

static void check_cage_and_bird() {
    // todo think on moving cage
    if(misifu.x == windows[0].x && windows[0].has_item == 'B') {
        windows[0].has_item = 'Z';
        misifu.state = FALLING;
        sp1_PrintAtInv(17, 26, INK_GREEN | PAPER_RED, ' ');
        sp1_PrintAtInv(17, 27, INK_GREEN | PAPER_RED, ' ');
        sp1_PrintAt(FLOOR_Y, 26, INK_GREEN | PAPER_RED, 'A');
        sp1_PrintAt(FLOOR_Y, 27, INK_GREEN | PAPER_RED, 'B');
    }

    if(windows[0].has_item == 'Z') {
        // todo udg of bird flying
    }
}

void level6_loop() {
    dog_checks();
    move_broom();

    check_chair_and_table();
    // bincat_appears, bincat_in_bin
    detect_cat_in_window(0);
    check_cage_and_bird();
}

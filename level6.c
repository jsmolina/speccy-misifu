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
  sp1_TileEntry('C', udg_birdcage1);
  sp1_TileEntry('D', udg_birdcage2);

  level_x_max = 27;
  level_x_min = 0;

  print_room_walls(20, PAPER_RED, INK_GREEN);
  // paint the chair
  paint_chair(17, 22, PAPER_RED, INK_GREEN);
  paint_table(17, 26, PAPER_RED, INK_GREEN);
  // 18, 27
  sp1_PrintAt(17, 26, INK_GREEN | PAPER_RED, 'C');
  sp1_PrintAt(17, 27, INK_GREEN | PAPER_RED, 'D');
  reset_misifu_position();
  // cage is in 25 position
  windows[0].x = 25;
  windows[0].has_item = BIRD; // bird is inside cage
  opened_window_frames = 1;
}

static void check_cage_and_bird() {
    // todo think on moving cage
    if(misifu.y == 16 && misifu.x == windows[0].x && windows[0].has_item == BIRD) {
        windows[0].has_item = RIGHT;
        misifu.state = FALLING;
        sp1_PrintAtInv(17, 26, INK_GREEN | PAPER_RED, ' ');
        sp1_PrintAtInv(17, 27, INK_GREEN | PAPER_RED, ' ');
        bit_beepfx_di_fastcall(BEEPFX_DROP_1);
        sp1_PrintAt(FLOOR_Y, 26, INK_GREEN | PAPER_RED, 'C');
        sp1_PrintAt(FLOOR_Y, 27, INK_GREEN | PAPER_RED, 'D');
    }

    if(windows[0].has_item != BIRD) {
        move_right_and_left();
        // todo move sprite bincat with a bird also
    }
}

void level6_loop() {
    move_broom();

    check_chair_and_table();
    // bincat_appears, bincat_in_bin
    check_cage_and_bird();
    detect_cat_in_window(0);
    dog_checks();
}

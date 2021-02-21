#include "defines.h"
#include "level4.h"

const uint8_t udg_fishtank1[] = {0x7f, 0x1f, 0x3f, 0x7a, 0x78, 0x7a, 0x3f, 0x0f};
const uint8_t udg_fishtank2[] = {0xfe, 0xf8, 0x3c, 0x1e, 0x2e, 0x1e, 0x7c, 0xf0};

void  print_background_level3() {
  level = 3;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_MAGENTA | BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', udg_fishtank1);
  sp1_TileEntry('B', udg_fishtank2);

  print_room_walls(12, PAPER_MAGENTA, INK_CYAN);

  // paint the chair
  paint_chair(10, PAPER_MAGENTA | INK_CYAN | BRIGHT);

  // 17,22
  paint_table(22, PAPER_MAGENTA | INK_CYAN | BRIGHT);

  paint_lamp(26, PAPER_MAGENTA | INK_CYAN | BRIGHT);
  // fishtank
  sp1_PrintAt( 17, 22,  INK_WHITE | PAPER_MAGENTA | BRIGHT, 'A');
  sp1_PrintAt( 17, 23,  INK_WHITE | PAPER_MAGENTA | BRIGHT, 'B');

  reset_misifu_position();

  aux_object.y = 5;
  aux_object.x = 5;
  repaint_lives = 1;

  level_x_max = 28;
  level_x_min = 1;
}


inline static void check_chair_and_fishtank_level3() {

    if(misifu.state == FALLING) {
        if(misifu.y == 16 && (misifu.x == 21 || misifu.x == 22)) {
            // get inside fishtank and outside of this level
            total_points += 5;
            level = 4;
            print_background_level4();
        }
    }

    if(misifu.in_bin != NONE && misifu.x != 10  && misifu.x != 21 && misifu.x != 22) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }
}



void level3_loop() {
    move_broom();
    dog_checks();
    detect_fall_in_chair(10, 1);
    check_chair_and_fishtank_level3();
    detect_cat_in_window(8);
}

#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_birdcage1[] = {0xf, 0xf0, 0xc0, 0xff, 0xc0, 0xf0, 0xff, 0xf};
const uint8_t udg_birdcage2[] = {0xf0, 0xf, 0x3, 0xff, 0x3, 0xf, 0xff, 0xf0};

void  print_background_level6() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_RED,
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
  windows[0].y = 7;
  windows[0].has_item = BIRD; // bird is inside cage
}

static void check_cage_and_bird() {
    // todo think on moving cage
    if(misifu.y == 16 && abs(misifu.x - windows[0].x) < 2 && windows[0].has_item == BIRD) {
        windows[0].has_item = RIGHT;
        misifu.state = FALLING;
        sp1_PrintAtInv(17, 26, INK_GREEN | PAPER_RED, ' ');
        sp1_PrintAtInv(17, 27, INK_GREEN | PAPER_RED, ' ');
        bit_beepfx_di_fastcall(BEEPFX_DROP_1);
        sp1_PrintAt(FLOOR_Y, 26, INK_GREEN | PAPER_RED, 'C');
        sp1_PrintAt(FLOOR_Y, 27, INK_GREEN | PAPER_RED, 'D');
    }

    if(windows[0].has_item != BIRD) {
        ++windows[0].x;
        if(windows[0].x > 28) {
            ++windows[0].y;
            windows[0].x = 0;
        }

        if(windows[0].y > 19) {
            windows[0].y = 7;
        }

        if(abs(windows[0].y - misifu.y) < 2 && abs(windows[0].x - misifu.x) < 2) {
            get_out_of_level_generic(WON_LEVEL); // yayy
            return;
        }
        if (frame_big < FRAME_CHANGE) {
            windows[1].x = BIRD_OFFSET;
        } else {
            windows[1].x = BIRD_OFFSET2;
        }

        sp1_MoveSprAbs(bincatsp, &full_screen, (void*)windows[1].x, windows[0].y, windows[0].x, 0, 0);
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

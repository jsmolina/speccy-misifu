#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_spiderplant11[] = {0x3, 0x33, 0xfe, 0x3c, 0xce, 0xfc, 0xce, 0x3d};
const uint8_t udg_spiderplant21[] = {0x3, 0x7, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3};
const uint8_t udg_spidershelfleft[] = {0xff, 0xfc, 0xf0, 0xc0, 0xc0, 0xf0, 0xfc, 0xff};
const uint8_t udg_spidershelfright[] = {0xff, 0x3f, 0xf, 0x3, 0x3, 0xf, 0x3f, 0xff};
const uint8_t udg_spiderempty[] = {0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
const uint8_t udg_spiderbook[] = {0xff, 0x0, 0xfe, 0x86, 0xfe, 0xfc, 0x0, 0xff};

static void paint_plant(uint8_t row, uint8_t col) {
    sp1_PrintAt( row, col, INK_BLACK | PAPER_MAGENTA, 'W');
    sp1_PrintAt( row, col + 1, INK_BLACK | PAPER_MAGENTA, 'W');
    sp1_PrintAt( row + 1, col, INK_BLACK | PAPER_MAGENTA, 'Y');
}

void  print_background_level5() {

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_CYAN | PAPER_MAGENTA,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);

  define_silla_udgs();

  sp1_TileEntry('L', udg_spidershelfleft);
  sp1_TileEntry('M', udg_spidershelfright);

  sp1_TileEntry('E', udg_spiderempty);
  sp1_TileEntry('B', udg_spiderbook);

  sp1_TileEntry('W', udg_spiderplant11);
  sp1_TileEntry('Y', udg_spiderplant21);

  print_room_walls(8, PAPER_MAGENTA, INK_CYAN);

  // paint the chair
  paint_chair(17, 10, PAPER_MAGENTA, INK_CYAN);

  level_x_max = 28;
  level_x_min = 0;

  for(idx_j = 5; idx_j != 20; ++idx_j ) {
     sp1_PrintAt(idx_j, 18,  INK_BLACK | PAPER_MAGENTA, 'L');

     for(idx = 19; idx != 29; ++idx) {
        random_value = rand();
        if (random_value > 150) {
            sp1_PrintAt(idx_j, idx,  INK_BLACK | PAPER_MAGENTA, 'B');
        } else {
            sp1_PrintAt(idx_j, idx,  INK_BLACK | PAPER_MAGENTA, 'E');
        }

     }

     sp1_PrintAt(idx_j, 29,  INK_BLACK | PAPER_MAGENTA, 'M');
  }

  paint_plant(3, 20);
  paint_plant(3, 24);
  paint_plant(3, 28);

  aux_object.y = 5;
  aux_object.x = 5;
  aux_object.offset = AUX_BROOM;

  reset_misifu_position();
  // spider starts here
  windows[0].x = 10;
  windows[0].y = 3;
  windows[0].has_item = LEFT;
  bincat_appears = NONE;

  sp1_UpdateNow();
}

void level5_loop() {
    // misifu.state = CAT_IN_ROPE;
    if(misifu.state == FALLING) {
        // 5 to 19, impair
        if(misifu.x > 16 && misifu.x < 28 && misifu.y >= 5 && misifu.y < 20 && (misifu.y & 1) == 0) {
            misifu.state = CAT_IN_ROPE;
        }
    }

    move_broom();
    check_broom_collision();
    // SPIDER, row (5-12), col (17-28)

    // see how to move spider in short code

    // bincat_appears, bincat_in_bin
    sp1_MoveSprAbs(bincatsp, &full_screen, (void*)SPIDER, windows[0].y, windows[0].x, 0, 0);
    detect_cat_in_window(12);

}

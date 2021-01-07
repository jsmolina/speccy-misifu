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

static void paint_plant(uint8_t row, uint8_t col, uint8_t clean) {
    if(clean == CLEAN) {
        sp1_PrintAtInv( row, col, INK_BLACK | PAPER_MAGENTA, ' ');
        sp1_PrintAtInv( row, col + 1, INK_BLACK | PAPER_MAGENTA, ' ');
        sp1_PrintAtInv( row + 1, col, INK_BLACK | PAPER_MAGENTA, ' ');
    } else {
        sp1_PrintAt( row, col, INK_BLACK | PAPER_MAGENTA, 'W');
        sp1_PrintAt( row, col + 1, INK_BLACK | PAPER_MAGENTA, 'W');
        sp1_PrintAt( row + 1, col, INK_BLACK | PAPER_MAGENTA, 'Y');
    }
}

void  print_background_level5() {

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_MAGENTA,
                  ' ' );
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
  level_x_min = 1;

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

  paint_plant(3, 20, 0);
  paint_plant(3, 24, 0);
  paint_plant(3, 28, 0);

  reset_misifu_position();
  // spider starts here
  windows[0].x = 10;
  windows[0].y = 3;
  idx = 1;
  assign_window_pos(0, 20);
  assign_window_pos(0, 24);
  assign_window_pos(0, 28);

  bincat_appears = NONE;
  eaten_items = 3;
  level = 5;

  sp1_UpdateNow();
}


static void vase_falls(uint8_t i) {
    if (windows[i].has_item == 'Z') {
        return;
    }

    windows[i].has_item = 'Z';
    bit_beepfx_di_fastcall(BEEPFX_HIT_2);
    paint_plant(3, windows[i].x, CLEAN);
    --eaten_items;

    if(eaten_items == 0) {
        get_out_of_level_generic(WON_LEVEL);
    }
}

static inline void detect_vase_falling() {
    if(misifu.y == 4) { // 17-28
        // thrown vase
        if(misifu.x >= 16 && misifu.x < 21) {
            vase_falls(1);
        } else if(misifu.x >= 22 && misifu.x < 25) {
            vase_falls(2);
        } else if(misifu.x >= 26 && misifu.x < 29) {
            vase_falls(3);
        }

    }
}

void level5_loop() {
    // bincat_appears, bincat_in_bin
    sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1 +SPIDER, windows[0].y, windows[0].x, 0, 0);

    // misifu.state = CAT_IN_ROPE;
    if(misifu.state == FALLING) {
        // 5 to 19, impair
        if(misifu.x > 16 && misifu.x < 28 && misifu.y >= 5 && misifu.y < 20 && (misifu.y & 1) == 0) {
            misifu.state = CAT_IN_ROPE;
            misifu.draw_additional = CAT_IN_SHELVE;
        }
    }

    move_broom();
    // SPIDER, row (5-12), col (17-28)
    //anim_spider();
    if(random_value < 18 && bincat_appears == NONE) {
        windows[0].x = random_value;

        if(random_value < 3) {
            windows[0].x = misifu.x;
        }

        windows[0].y = 3;
        bincat_appears = 15;
    }
    // if already animating
    if (bincat_appears != NONE) {
        --bincat_appears;
        ++windows[0].y;

    }

    dog_checks();
    detect_fall_in_chair(9);
    detect_vase_falling();
    detect_cat_in_window(12);

    //detect_spider_bite();
    if(abs(windows[0].y - misifu.y) < 1 && abs(windows[0].x - misifu.x) < 1) {
        // SPIDER BITE
        get_out_of_level_generic(BITE);
    }
}

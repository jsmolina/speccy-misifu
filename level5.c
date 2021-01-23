#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

#define BLACK_MAGENTA_BRIGHT 0x58
#define LEVEL5_TILES_LEN  6
#define LEVEL5_TILES_BASE  65

#define UDG_SPIDERPLANT11 65
#define UDG_SPIDERPLANT21 66
#define UDG_SPIDERSHELF_LEFT 67
#define UDG_SPIDERSHELF_RIGHT 68
#define UDG_SPIDEREMPTY 69
#define UDG_SPIDERBOOK 70

#define SPIDER_HORIZONTALLY 1
#define SPIDER_DOWN 2
#define SPIDER_UP 3

#define BROKEN_VASE 25

uint8_t level5[] = {
    0x03, 0x33, 0xfe, 0x3c, 0xce, 0xfc, 0xce, 0x3d, // y:0, x:0 (65)
    0x03, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // y:0, x:1 (66)
    0xff, 0xfc, 0xf0, 0xc0, 0xc0, 0xf0, 0xfc, 0xff, // y:0, x:2 (67)
    0xff, 0x3f, 0x0f, 0x03, 0x03, 0x0f, 0x3f, 0xff, // y:0, x:3 (68)
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, // y:0, x:4 (69)
    0xff, 0x00, 0xfe, 0x86, 0xfe, 0xfc, 0x00, 0xff, // y:0, x:5 (70)
};

void paint_vase(uint8_t col, uint8_t clean) {
        sp1_PrintAtInv( 3, col, BLACK_MAGENTA_BRIGHT, clean);
        sp1_PrintAtInv( 3, col + 1, BLACK_MAGENTA_BRIGHT, clean);
        if (clean != ' ') {
            ++clean;
        }
        sp1_PrintAtInv( 3 + 1, col, BLACK_MAGENTA_BRIGHT, clean);

}

void  print_background_level5() {

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  BLACK_MAGENTA_BRIGHT,
                  ' ');
  sp1_Invalidate(&full_screen);

  uint8_t *pt = level5;

  for (idx = 0; idx < LEVEL5_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LEVEL5_TILES_BASE + idx, pt);
  }

  print_room_walls(8, PAPER_MAGENTA, INK_CYAN);

  // paint the chair
  paint_chair(10, PAPER_MAGENTA | INK_CYAN | BRIGHT);

  level_x_max = 28;
  level_x_min = 1;

  for(idx_j = 5; idx_j != 20; ++idx_j ) {
     sp1_PrintAt(idx_j, 18,  BLACK_MAGENTA_BRIGHT, UDG_SPIDERSHELF_LEFT);

     for(idx = 19; idx != 29; ++idx) {
        random_value = rand();
        if (random_value > 150) {
            sp1_PrintAt(idx_j, idx,  BLACK_MAGENTA_BRIGHT, UDG_SPIDERBOOK);
        } else {
            sp1_PrintAt(idx_j, idx,  BLACK_MAGENTA_BRIGHT, UDG_SPIDEREMPTY);
        }

     }

     sp1_PrintAt(idx_j, 29,  BLACK_MAGENTA_BRIGHT, UDG_SPIDERSHELF_RIGHT);
  }


  idx_j = 1;
  for(idx = 20; idx != 32; idx += 4) {
      paint_vase(idx, UDG_SPIDERPLANT11);
      windows[idx_j].has_item = UDG_SPIDERPLANT11; // later BROKEN_VASE
      ++idx_j;
  }

  reset_misifu_position();
  // spider starts here
  windows[0].x = 10;
  windows[0].y = 3;
  idx = 1;
  bincat_appears = SPIDER_HORIZONTALLY;
  eaten_items = 3;
  level = 5;

  sp1_UpdateNow();
}


inline void detect_vase_falling() {
    // thrown vase
    idx_j = 1;
    for(idx = 20; idx != 32; idx += 4) {
        if(misifu.y == 4 && windows[idx_j].has_item != BROKEN_VASE && (misifu.x >= idx -1 && misifu.x <= idx)) {
            windows[idx_j].has_item = BROKEN_VASE;
            bit_beepfx_di_fastcall(BEEPFX_HIT_2);
            paint_vase(idx, ' ');
            --eaten_items;
            ++misifu.y;
        }
        ++idx_j;
    }
}

void level5_loop() {
    // misifu.state = CAT_IN_ROPE;
    if(misifu.state == FALLING) {
        // 5 to 19, impair
        if(misifu.x > 16 && misifu.x < 28 && misifu.y >= 5 && misifu.y < 20 && (misifu.y & 1) == 0) {
            misifu.state = CAT_IN_ROPE;
            misifu.draw_additional = CAT_IN_SHELVE;
        }
    }

    //move_broom();
    // SPIDER, row (5-12), col (17-28)
    //anim_spider();
    // spider should move right, then down, then up

    // spider FSM
    if((frame & 1) == 0) {
        if(bincat_appears == SPIDER_HORIZONTALLY) {
            if(windows[0].x > misifu.x) {
                --windows[0].x;
            } else if (windows[0].x < misifu.x) {
                ++windows[0].x;
            } else {
                bincat_appears = SPIDER_DOWN;
            }
        } else if(bincat_appears == SPIDER_DOWN) {
            if(windows[0].y < FLOOR_Y) {
                ++windows[0].y;
            } else {
                bincat_appears = SPIDER_UP;
            }
        } else if(bincat_appears == SPIDER_UP) {
            if(windows[0].y > 3) {
                --windows[0].y;
            } else {
                bincat_appears = SPIDER_HORIZONTALLY;
            }
        }
    }

    dog_checks();
    detect_fall_in_chair(10);
    detect_vase_falling();
    detect_cat_in_window(12);

    // bincat_appears, bincat_in_bin
    sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1 +SPIDER, windows[0].y, windows[0].x, 0, 0);

    if(eaten_items == 0) {
        get_out_of_level_generic(WON_LEVEL);
    }

    //detect_spider_bite();
    if(abs(windows[0].y - misifu.y) < 1 && abs(windows[0].x - misifu.x) < 1) {
        // SPIDER BITE
        get_out_of_level_generic(BITE);
    }
}

#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"

#define BLACK_MAGENTA_BRIGHT 0x58
#define LEVEL5_TILES_LEN  12
#define LEVEL5_TILES_BASE  65

#define UDG_ESTANTERIA_DER_01 65
#define UDG_ESTANTERIA_DER_02 66
#define UDG_ESTANTERIA_IZQ_01 67
#define UDG_ESTANTERIA_IZQ_02 68
#define UDG_ESTANTERIA_TOP_VACIO 69
#define UDG_JARRON_FLORES 70
#define UDG_JARRON_DER 71
#define UDG_JARRON_IZQ 72
#define UDG_LIBRO_INCLINADO_01 73
#define UDG_LIBRO_INCLINADO_02 74
#define UDG_LIBROS_01 75
#define UDG_LIBROS_02 76

#define SPIDER_HORIZONTALLY 1
#define SPIDER_DOWN 2
#define SPIDER_UP 3
#define TOTAL_EMPTY_HOLES 32
#define TOTAL_ITALIC_HOLES 6


#define BROKEN_VASE 25

uint8_t level5[] = {
    0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, // y:0, x:0 (65)
    0xe7, 0xa7, 0xa7, 0xe7, 0xe7, 0xe7, 0xa7, 0xe7, // y:0, x:1 (66)
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, // y:0, x:2 (67)
    0xee, 0xea, 0xea, 0xee, 0xee, 0xee, 0xea, 0xee, // y:0, x:3 (68)
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // y:0, x:4 (69)
    0x5a, 0xbd, 0xf6, 0xbd, 0x5f, 0xb5, 0x6e, 0x3c, // y:0, x:5 (70)
    0xc0, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, // y:0, x:6 (71)
    0x03, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, // y:0, x:7 (72)
    0xff, 0xff, 0x00, 0x00, 0x60, 0xe0, 0xf0, 0x50, // y:0, x:8 (73)
    0x78, 0x38, 0x3c, 0x1c, 0x1e, 0x0e, 0x0f, 0x06, // y:0, x:9 (74)
    0xff, 0xff, 0x00, 0x00, 0xee, 0xaa, 0xee, 0xee, // y:0, x:10 (75)
    0xee, 0xaa, 0xaa, 0xee, 0xee, 0xee, 0xaa, 0xee, // y:0, x:11 (76)
};

const uint8_t empty_holes [] = {0x17, 0x9f, 0xf0, 0x23, 0x67, 0x8f, 0x38, 0xf2, 0x34,
 0x59, 0xf2, 0x5f, 0x13, 0x45, 0x78, 0xf3, 0x78, 0xf0, 0x26, 0x9f, 0x26,
 0x56, 0xf2, 0x45, 0x68, 0xf4, 0x8f, 0x02, 0x36, 0x79, 0xf2, 0x7f};

const uint8_t italic [] = {0x05, 0x41, 0x47, 0x85, 0xa1, 0xc5};

void paint_vase(uint8_t col, uint8_t clean) {

        for(x = 0; x != 2; ++x) {
            sp1_PrintAtInv( 3, col + x, INK_CYAN | PAPER_MAGENTA | BRIGHT, clean);
        }
        if (clean != ' ') {
            ++clean;
        }
        // jarron derecho
        sp1_PrintAtInv( 4, col + 1, INK_WHITE | PAPER_MAGENTA | BRIGHT, clean);
        if (clean != ' ') {
            ++clean;
        }
        // jarron izquierdo
        sp1_PrintAtInv( 4, col, INK_WHITE | PAPER_MAGENTA | BRIGHT, clean);
}

void paintHole() {
    if(idx == 15) {
        ++idx_j;
        return;
    }
    first_keypress = UDG_ESTANTERIA_TOP_VACIO;
    if((idx_j & 1) == 0) {
        first_keypress = ' ';
    }
    sp1_PrintAtInv(idx_j, 19 + idx, BLACK_MAGENTA_BRIGHT, first_keypress);

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

  // paint the chair and lamp
  paint_chair(10, PAPER_MAGENTA | INK_CYAN | BRIGHT);
  paint_lamp(6, PAPER_MAGENTA | INK_CYAN | BRIGHT);

  level_x_max = 28;
  level_x_min = 1;

  for(idx_j = 5; idx_j != 20; ++idx_j ) {
     if((idx_j & 1) == 0) {
        first_keypress = UDG_ESTANTERIA_DER_02;
        x = UDG_LIBROS_02;
     } else {
        first_keypress = UDG_ESTANTERIA_DER_01;
        x = UDG_LIBROS_01;
     }
     // parte baja estanteria
     if(idx_j == 19) {
        x = UDG_ESTANTERIA_TOP_VACIO;
     }
     sp1_PrintAt(idx_j, 18,  BLACK_MAGENTA_BRIGHT, first_keypress + 2);
     sp1_PrintAt(idx_j, 29,  BLACK_MAGENTA_BRIGHT, first_keypress);
     // first paints all filled
     for(idx = 19; idx != 29; ++idx) {
        sp1_PrintAt(idx_j, idx,  BLACK_MAGENTA_BRIGHT, x);
     }
  }
  idx_j = 5;
  for(x = 0; x != TOTAL_EMPTY_HOLES; ++x) {
     idx = (empty_holes[x] & 0xF0) >> 4;
     paintHole();
     idx = (empty_holes[x] & 0x0F);
     paintHole();
  }

  for(x = 0; x != TOTAL_ITALIC_HOLES; ++x) {
     idx_j = (italic[x] & 0xF0) >> 4;
     idx = (italic[x] & 0x0F);
     for (first_keypress = 0; first_keypress != 2; ++first_keypress) {
        sp1_PrintAtInv(5 + idx_j + first_keypress, 19 + idx, BLACK_MAGENTA_BRIGHT, UDG_LIBRO_INCLINADO_01 + first_keypress);
     }
  }


  idx_j = 1;
  for(idx = 19; idx != 31; idx += 4) {
      paint_vase(idx, UDG_JARRON_FLORES);
      windows[idx_j].has_item = UDG_JARRON_FLORES; // later BROKEN_VASE
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
    for(idx = 19; idx != 31; idx += 4) {
        if(misifu.y == 4 && windows[idx_j].has_item != BROKEN_VASE && (misifu.x >= idx -1 && misifu.x <= idx)) {
            windows[idx_j].has_item = BROKEN_VASE;
            misifu.state = FALLING_FLOOR;
            misifu.draw_additional = NONE;
            bit_beepfx_di_fastcall(BEEPFX_DROP_1);
            paint_vase(idx, ' ');
            total_points += 10;
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
        if(misifu.x > 16 && misifu.x < 29 && misifu.y >= 5 && misifu.y < 20 && (misifu.y & 1) == 0) {
            misifu.state = CAT_IN_ROPE;
            misifu.draw_additional = CAT_IN_SHELVE;
        }
    }

    move_broom();
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

    detect_fall_in_chair(10, 1);
    detect_vase_falling();


    // bincat_appears, bincat_in_bin
    sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1 +SPIDER, windows[0].y, windows[0].x, 0, 0);

    if(eaten_items == 0) {
        get_out_of_level_generic(WON_LEVEL);
    }

    //detect_spider_bite();
    if(misifu.state != FALLING_FLOOR && abs(windows[0].y - misifu.y) < 2 &&
        (windows[0].x == misifu.x || windows[0].x == (misifu.x + 1))) {
        // SPIDER BITE
        get_out_of_level_generic(BITE);
    }

    detect_cat_in_window(12);
    dog_checks();
}

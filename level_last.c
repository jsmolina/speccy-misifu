#include "level3.h"
#include "defines.h"
#include "level1.h"
#include "int.h"
#include <stdlib.h>
#include <string.h>
#include <input.h>
#include <sound.h> // for bit_beepfx()

#define RED_GREEN_BRIGHT INK_RED | PAPER_GREEN | BRIGHT

#define RAT_TO_RIGHT 1
#define RAT_TO_LEFT 2
#define UDG_UDG_CORAZON_01 128
#define UDG_UDG_CORAZON_02 129
#define UDG_UDG_CORAZON_ROTO_01 130
#define UDG_UDG_CORAZON_ROTO_02 131
#define UDG_RATA_DERECHA_01 132
#define UDG_RATA_DERECHA_02 133
#define UDG_RATA_IZQUIERDA_01 134
#define UDG_RATA_IZQUIERDA_02 135
#define UDG_UDG_GATA_A_01 136
#define UDG_UDG_GATA_A_02 137
#define UDG_UDG_GATA_B_01 138
#define UDG_UDG_GATA_B_02 139

#define LAST_TILES_LEN  12
#define LAST_TILES_BASE  128

extern uint8_t cartoon2[];

const uint8_t last[] = {
    0x3c, 0x66, 0x5f, 0x7f, 0x3f, 0x0f, 0x03, 0x01, // y:0, x:0 (128)
    0x78, 0xfc, 0xfc, 0xfc, 0xf8, 0xe0, 0x80, 0x00, // y:0, x:1 (129)
    0x00, 0x3c, 0x7e, 0x7e, 0x7f, 0x3f, 0x0f, 0x03, // y:0, x:2 (130)
    0x78, 0xfc, 0xfc, 0xfc, 0x78, 0x60, 0x40, 0x00, // y:0, x:3 (131)
    0x00, 0x00, 0x00, 0x10, 0x27, 0x2f, 0x1f, 0x0f, // y:0, x:4 (132)
    0x00, 0x00, 0x30, 0x70, 0xf8, 0xf4, 0xfe, 0xfc, // y:0, x:5 (133)
    0x00, 0x00, 0x0c, 0x0e, 0x1f, 0x2f, 0x7f, 0x3f, // y:0, x:6 (134)
    0x00, 0x00, 0x00, 0x08, 0xe4, 0xf4, 0xf8, 0xf0, // y:0, x:7 (135)
    0x00, 0x04, 0x07, 0x0f, 0x0d, 0x0f, 0x07, 0x07, // y:0, x:8 (136)
    0x00, 0x40, 0xc0, 0xe0, 0x60, 0xe0, 0xc0, 0xc0, // y:0, x:9 (137)
    0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, // y:0, x:10 (138)
    0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc8, 0xd8, 0xf0, // y:0, x:11 (139)
};


void paint_cupids() {
    __asm
    extern enable_bank_n
   di
   ld a,0x80
   ld i,a                      ; point I at uncontended bank

   ld a,4
   call enable_bank_n          ; bank 4 in top 16k, stack moved
    __endasm;
    memcpy(16384, cartoon2, 6912);
    __asm
    extern restore_bank_0
    call restore_bank_0

    ld a,0xd0
    ld i,a                      ; restore I

    ei
    __endasm;
}

void print_background_level_last() {
  level = 10;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_GREEN | BRIGHT,
                  ' ' );
  zx_border(INK_BLACK);

  sp1_Invalidate(&full_screen);
  sp1_MoveSprAbs(misifu.sp, &full_screen, (int) sprite_protar1, FLOOR_Y - 1, 4, 0, 0);
  sp1_UpdateNow();
  paint_cupids();

  uint8_t *pt = last;

  for (idx = 0; idx < LAST_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LAST_TILES_BASE + idx, pt);
  }

  x = UDG_UDG_GATA_A_01;
  for(idx_j = 5; idx_j != 7; ++idx_j) {
      for(idx = 15; idx != 17; ++idx) {
          sp1_PrintAtInv(idx_j, idx, INK_BLACK | PAPER_GREEN | BRIGHT, x);
          ++x;
      }
  }

  // this is rats positions
  frame = 10;
  for(idx_j = 0; idx_j != 3; ++idx_j) {
      x = (rand() % 19) + 5;
      windows[idx_j].x = x;
      windows[idx_j].y = frame;
      windows[idx_j].has_item = RAT_TO_RIGHT  + (x & 1);
      frame += 4;
  }

  // frame = floor
  //frame = 4;
  // y = 0, floor on bottom
  frame = 23;
  for(idx_j = 0; idx_j != 5; ++idx_j) {
      eaten_items = 0;
      for(idx = 4; idx != 28; ++idx) {
            random_value = rand();

            if((idx & 1) == 0) {
                x_malo = UDG_UDG_CORAZON_01;
                bincat_in_bin = INK_RED | PAPER_GREEN | BRIGHT;
                if(idx_j != 0 && (random_value & 1)) {
                    x_malo = UDG_UDG_CORAZON_ROTO_01;
                    bincat_in_bin = INK_BLUE | PAPER_GREEN | BRIGHT;
                }
            }

            sp1_PrintAtInv(
                    frame,
                    idx,
                    bincat_in_bin,
                    x_malo + (idx & 1));

            if((idx & 1) == 0) {
                floor_holes[idx_j][eaten_items] = x_malo;
                ++eaten_items;
            }

      }
      frame = frame - 4;
  }


  misifu.x = 4;
  misifu.y = FLOOR_Y;
  level_x_max = 26;
  level_x_min = 4;
  aux_object.offset = AUX_ARROWLEFT;
  aux_object.y = 3;
  aux_object.x = 33;
}


/**
 hearts y are 23, 19, 15, 11, 7
**/
static uint8_t lvl3_y_to_idj(uint8_t y) {

    if(y == 5) {
        return 4;
    } else if(y == 9) {
        return 3;
    } else if(y == 13) {
        return 2;
    } else if(y == 17) {
        return 1;
    } else if (y == FLOOR_Y) {
        return 0;
    } else {
        return UNDEF;
    }
}


static inline uint8_t rand_cat_to_move() {
    if(random_value < 50) {
        return 0;
    } else if(random_value < 100) {
        return 1;
    } else if(random_value < 150) {
        return 2;
    }
    return UNDEF;
}

void throw_cupid_arrow() {
    // arrow should remove tiles (and redraw them)
    // if arrow object is hidden, decide to throw it or not
    if (aux_object.x == 33 && random_value >= level_x_min && random_value <= level_x_max && (tick & 1) == 0) {
        aux_object.x = random_value;
        aux_object.y = 0;

        if(aux_object.x > 16) {
            aux_object.offset = AUX_ARROWLEFT;
        } else {
            aux_object.offset = AUX_ARROWRIGHT;
        }
    }
    if(aux_object.x != 33) {
        if(aux_object.x <= FLOOR_Y) {
            ++aux_object.y;
            if((random_value & 1) == 0) {
                if (aux_object.offset == AUX_ARROWRIGHT) {
                    ++aux_object.x;
                } else {
                    --aux_object.x;
                }
            }
            idx_j = lvl3_y_to_idj(aux_object.y - 1);
            if(idx_j == UNDEF) {
                return;
            }
            idx = aux_object.x - 3;
            if((idx & 1) == 1) {
                --idx;
            }
            x_malo = idx + 4;
            idx = idx >> 1;
            if(floor_holes[idx_j][idx] == UDG_UDG_CORAZON_01) {
                floor_holes[idx_j][idx] = UDG_UDG_CORAZON_ROTO_01;
                for(x = 0; x != 2; ++x) {
                    sp1_PrintAtInv(
                        aux_object.y + 1,
                        x_malo + x,
                        INK_BLUE | PAPER_GREEN | BRIGHT,
                        floor_holes[idx_j][idx] + x);
                }
            }
        } else {
            // out of screen
            aux_object.x = 33;
        }
        sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, aux_object.x, 0, 0);
    }
    // si toca el gato lo tira?
}

void level10_loop() {
    throw_cupid_arrow();
    idx_j = rand_cat_to_move();
    if(idx_j != UNDEF) {
        for(x = 0; x != 2; ++x) {
            sp1_PrintAtInv( windows[idx_j].y, windows[idx_j].x + x, PAPER_GREEN | BRIGHT, ' ');
        }
        if(windows[idx_j].has_item == RAT_TO_RIGHT) {
            idx = UDG_RATA_DERECHA_01;
            ++windows[idx_j].x;
        } else {
            idx = UDG_RATA_IZQUIERDA_01;
            --windows[idx_j].x;
        }
        if(windows[idx_j].x <= level_x_min) {
            windows[idx_j].has_item = RAT_TO_RIGHT;
        } else if(windows[idx_j].x >= level_x_max) {
            windows[idx_j].has_item = RAT_TO_LEFT;
        }
        for(x = 0; x != 2; ++x) {
            sp1_PrintAtInv( windows[idx_j].y, windows[idx_j].x + x, PAPER_GREEN | BRIGHT, idx + x);
        }
        // colision
        if(((misifu.y + 1) == windows[idx_j].y) && (misifu.x == windows[idx_j].x || misifu.x == (windows[idx_j].x - 1))) {
            misifu.state = FALLING;
            ++misifu.y;
        }
    }

    idx_j = lvl3_y_to_idj(misifu.y);
    if (idx_j != UNDEF) {
        idx = misifu.x - 3; // (3, 5, 7) => (0, 2, 4)
        if((idx & 1) == 1) {
            --idx;
        }
        idx = idx >> 1; //  (0, 2, 4) => (0, 1, 2) [real indexes]

        if (floor_holes[idx_j][idx] == UDG_UDG_CORAZON_ROTO_01) {
            misifu.state = FALLING;
            if (misifu.y >= FLOOR_Y) {
                get_out_of_level_generic(FALLING);
                return;
            }
        } else if (floor_holes[idx_j][idx] == UDG_UDG_CORAZON_01 && misifu.state == FALLING) {
            if(idx_j == 0) {
                get_out_of_level_generic(LEVELFINISHED); // yayyy
                return;
            }
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE;
            misifu.offset = BORED;
        }
        if(idx_j == 4 && (misifu.x == 15 || misifu.x == 16)) {
            get_out_of_level_generic(LEVELFINISHED);
            return;
        }
    }

}
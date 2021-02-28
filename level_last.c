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
#define UDG_UDG_CORAZON_ROTO_01 128
#define UDG_UDG_CORAZON_ROTO_02 129
#define UDG_RATA_DERECHA_01 130
#define UDG_RATA_DERECHA_02 131
#define UDG_RATA_IZQUIERDA_01 132
#define UDG_RATA_IZQUIERDA_02 133

#define LAST_TILES_LEN  6
#define LAST_TILES_BASE  128


uint8_t last[] = {
    0x00, 0x3c, 0x7e, 0x7e, 0x7f, 0x3f, 0x0f, 0x03, // y:0, x:0 (128)
    0x78, 0xfc, 0xfc, 0xfc, 0x78, 0x60, 0x40, 0x00, // y:0, x:1 (129)
    0x00, 0x00, 0x00, 0x10, 0x27, 0x2f, 0x1f, 0x0f, // y:0, x:2 (130)
    0x00, 0x00, 0x30, 0x70, 0xf8, 0xf4, 0xfe, 0xfc, // y:0, x:3 (131)
    0x00, 0x00, 0x0c, 0x0e, 0x1f, 0x2f, 0x7f, 0x3f, // y:0, x:4 (132)
    0x00, 0x00, 0x00, 0x08, 0xe4, 0xf4, 0xf8, 0xf0, // y:0, x:5 (133)
};


void print_background_level_last() {
  level = 10;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_GREEN | BRIGHT,
                  ' ' );
  zx_border(INK_BLACK);

  sp1_Invalidate(&full_screen);
  sp1_MoveSprAbs(misifu.sp, &full_screen, (int) sprite_protar1, FLOOR_Y - 1, 4, 0, 0);
  sp1_UpdateNow();
  show_cupids();

  uint8_t *pt = last;

  for (idx = 0; idx < LAST_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LAST_TILES_BASE + idx, pt);
  }
  assign_hearts();

  // this is rats positions
  frame = 6;
  for(idx_j = 0; idx_j != 4; ++idx_j) {
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

  // fred! (lover)
  sp1_DeleteSpr_fastcall(dogr1sp);
  dogr1sp = add_sprite_protar1();

  misifu.x = 4;
  misifu.y = FLOOR_Y;
  level_x_max = 26;
  level_x_min = 4;
  aux_object.offset = AUX_ARROWLEFT;
  aux_object.y = 3;
  aux_object.x = 33;
  x_malo = 4;
  dog_offset = RIGHTC1;
  misifu.state = FALLING;
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

inline void throw_cupid_arrow() {
    // arrow should remove tiles (and redraw them)
    // if arrow object is hidden, decide to throw it or not
    if (aux_object.x == 33 && random_value >= level_x_min && random_value <= level_x_max && (tick & 1) == 0) {
        aux_object.x = random_value;
        aux_object.y = 3;

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
            if(idx_j != UNDEF) {

                idx = aux_object.x - 3;
                if((idx & 1) == 1) {
                    --idx;
                }
                bincat_in_bin = idx + 4;
                idx = idx >> 1;
                if(floor_holes[idx_j][idx] == UDG_UDG_CORAZON_01) {
                    floor_holes[idx_j][idx] = UDG_UDG_CORAZON_ROTO_01;
                    row1_moving = INK_BLUE | PAPER_GREEN | BRIGHT;
                } else {
                    floor_holes[idx_j][idx] = UDG_UDG_CORAZON_01;
                    row1_moving = INK_RED | PAPER_GREEN | BRIGHT;
                }
                for(x = 0; x != 2; ++x) {
                    sp1_PrintAtInv(
                        aux_object.y + 1,
                        bincat_in_bin + x,
                       row1_moving,
                        floor_holes[idx_j][idx] + x);
                }
            }

        } else {
            // out of screen
            aux_object.x = 33;
        }

        if(misifu.x == aux_object.x && misifu.y == aux_object.y) {
            get_out_of_level_generic(FALLING_HEARTS);
            return;
        }

        sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, aux_object.x, 0, 0);
    }
    // si toca el gato lo tira?
}

void level10_loop() {
    for(idx_j= 0; idx_j != 4; ++idx_j) {
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
                get_out_of_level_generic(FALLING_HEARTS);
                return;
            }
        } else if (floor_holes[idx_j][idx] == UDG_UDG_CORAZON_01 && misifu.state == FALLING) {
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE;
            misifu.offset = BORED;
        }
        if(idx_j == 4 && (misifu.x == x_malo || misifu.x == (x_malo + 1))) {
            get_out_of_level_generic(LEVELFINISHED);
            return;
        }
    }
    // move Fred! (reusing x_malo... but fred is a kidnapped good guy)
    // dog_offset
    // enemy_apears
    if(frame == 2) {
        if(dog_offset == RIGHTC1 || dog_offset == RIGHTC2) {
            ++x_malo;
            if((x_malo & 1) == 0) {
                dog_offset = RIGHTC1;
            } else {
                dog_offset = RIGHTC2;
            }
        } else {
            --x_malo;
            if((x_malo & 1) == 0) {
                dog_offset = LEFTC1;
            } else {
                dog_offset = LEFTC2;
            }
        }
        if(x_malo >= level_x_max) {
            dog_offset = LEFTC1;
        }
        if(x_malo <= level_x_min) {
            dog_offset = RIGHTC1;
        }

        sp1_MoveSprAbs(dogr1sp, &full_screen, (int) sprite_protar1 + dog_offset, 4, x_malo, 0, 0);
    }
    throw_cupid_arrow();

}
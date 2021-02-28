#include <stdlib.h>
#include <sound.h>
#include <intrinsic.h>
#include "defines.h"
#include "level1.h"
#include "int.h"

#define BLACK_CYAN_BRIGHT 0x68

#define UDG_WATERTOP 128
#define UDG_WATERTOP2 129
#define UDG_FISH 130
#define UDG_FISH2 131
#define UDG_FISHL 132
#define UDG_FISHL2 133

#define UDG_EEL_TAIL 134
#define UDG_EEL_TAIL2 135
#define UDG_EEL_HEAD 136
#define UDG_EEL_HEAD2 137

#define UDG_EEL_LEFT_HEAD 138
#define UDG_EEL_LEFT_HEAD2 139
#define UDG_EEL_LEFT_TAIL 140
#define UDG_EEL_LEFT_TAIL2 141

#define TOTAL_FISHES 8
#define TOTAL_EELS 4

#define FISH_TO_RIGHT 0
#define FISH_TO_LEFT 1
#define EATEN_FISH 2

#define EEL_TO_RIGHT 0
#define EEL_TO_LEFT 1

#define FISHTANK_TILES_LEN  14
#define FISHTANK_TILES_BASE  128
uint8_t fishtank[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x00, 0x00, // y:0, x:0 (128)
    0xff, 0xff, 0xff, 0xc3, 0x00, 0x00, 0x00, 0x00, // y:0, x:1 (129)
    0x30, 0x1c, 0xbe, 0xfd, 0xff, 0xbe, 0x1c, 0x30, // y:0, x:2 (130)
    0x30, 0x1c, 0x3e, 0x7d, 0x7f, 0x3e, 0x1c, 0x30, // y:0, x:3 (131)
    0x0c, 0x38, 0x7d, 0xbf, 0xff, 0x7d, 0x38, 0x0c, // y:0, x:4 (132)
    0x0c, 0x38, 0x7c, 0xbe, 0xfe, 0x7c, 0x38, 0x0c, // y:0, x:5 (133)
    0x00, 0x00, 0x70, 0xfd, 0xcf, 0x07, 0x00, 0x00, // y:0, x:6 (134)
    0x00, 0x07, 0xcf, 0xfd, 0x70, 0x00, 0x00, 0x00, // y:0, x:7 (135)
    0x00, 0x00, 0x7e, 0xfd, 0xff, 0x8e, 0x00, 0x00, // y:0, x:8 (136)
    0x00, 0xc0, 0xfe, 0xfd, 0x7f, 0x0c, 0x06, 0x00, // y:0, x:9 (137)
    0x00, 0x00, 0x7e, 0xbf, 0xff, 0x71, 0x00, 0x00, // y:0, x:10 (138)
    0x00, 0x03, 0x7f, 0xbf, 0xfe, 0x30, 0x60, 0x00, // y:0, x:11 (139)
    0x00, 0x00, 0x0e, 0xbf, 0xf3, 0xe0, 0x00, 0x00, // y:0, x:12 (140)
    0x00, 0xe0, 0xf3, 0xbf, 0x0e, 0x00, 0x00, 0x00, // y:0, x:13 (141)
};


uint8_t check_udg_collision(uint8_t udgy, uint8_t udgx) {
    if ((misifu.x <= udgx) && (misifu.x >= (udgx - 2))) {
        if(abs(misifu.y - udgy) < 2) {
            // consider not in same y
            if(misifu.offset == SWIM_UP1 && (misifu.x == (udgx - 2) || (misifu.x == udgx))) {
                // nothing
            } else if(misifu.y == udgy || (misifu.y == (udgy - 1))) {
                return 1;
            } else if(misifu.y == (udgy + 1 ) && (misifu.offset > SWIM_LC2)) {
                return 1;
            }
        }
    }
    return 0;
}

void  print_background_level4() {
  level = 4;
  eaten_items = 0;
  bincat_in_bin = 5; // number of halts
  misifu.offset = SWIM_RC1;
  // todo cat should not take too much or get out of breath... level timer
  // swimming state always here
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  BLACK_CYAN_BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);

  uint8_t *pt = fishtank;
  for (idx = 0; idx < FISHTANK_TILES_LEN; idx++, pt += 8) {
     sp1_TileEntry(FISHTANK_TILES_BASE + idx, pt);
  }

  // start fishes positions
  for(idx = 0; idx != TOTAL_FISHES; ++idx) {
        floor_holes[0][idx] = rand() % 28;
        floor_holes[1][idx] = FISH_TO_RIGHT; // direction
  }

  for(idx = 0; idx != TOTAL_EELS; ++idx) {
      // y  = 4, 8, 12, 16
      floor_holes[2][idx] = rand() % 28 + 1;
      floor_holes[3][idx] = (idx & 1); // 0 or 1 (EEL_TO_LEFT, EEL_TO_RIGHT)
  }

  level_x_max = 28;
  level_x_min = 1;

  reset_misifu_position();
  misifu.state = SWIMMING;
  // loose breathe
  misifu.draw_additional = 30;

  misifu.y = 5;
  anim_frames = 3;

  // sprite changed
  sp1_DeleteSpr_fastcall(misifu.sp);
  misifu.sp = add_sprite_swim();
}

static void get_out_of_level4(uint8_t fall) {
    sp1_DeleteSpr_fastcall(misifu.sp);
    misifu.sp = add_sprite_protar1();
    get_out_of_level_generic(fall);
}


void level4_loop() {
  x = (frame & 1);

  for(idx = 0; idx != 32; ++idx) {
    idx_j = UDG_WATERTOP + (x & 1);
    sp1_PrintAtInv( 0, idx,  BLACK_CYAN_BRIGHT, idx_j);
    ++x;
  }
    //si usamos la de color celeste y magenta, los otros dos colores son banco y negro
  // move fishes
  idx_j  = 3; // 3, 5, 7, 9, 11, 13, 15, 17
  for(idx = 0; idx != TOTAL_FISHES; ++idx) {
        if(floor_holes[1][idx] != EATEN_FISH) {
            sp1_PrintAtInv( idx_j, floor_holes[0][idx],  INK_BLACK | PAPER_CYAN | BRIGHT, ' ');

            if (check_udg_collision(idx_j, floor_holes[0][idx])) {
                floor_holes[1][idx] = EATEN_FISH;
                bit_beepfx_di_fastcall(BEEPFX_SCORE);
                ++eaten_items;
                total_points += 10;
                if(eaten_items == 4) {
                    --bincat_in_bin;
                } else if(eaten_items == 6) {
                    --bincat_in_bin;
                } else if(eaten_items == 7) {
                    --bincat_in_bin;
                }
                sp1_PrintAtInv(23, 1 + eaten_items, INK_WHITE | PAPER_CYAN | BRIGHT, UDG_FISH);
            } else {

                if(floor_holes[1][idx] == FISH_TO_RIGHT) {
                    x = UDG_FISH + (frame == 2);
                    ++floor_holes[0][idx];
                    if(floor_holes[0][idx] == 31) {
                        ++floor_holes[1][idx]; // FISH_TO_LEFT;
                    }
                } else if(floor_holes[1][idx] == FISH_TO_LEFT) {
                    x = UDG_FISHL + (frame == 2);
                    --floor_holes[0][idx];
                    if(floor_holes[0][idx] == 0) {
                        --floor_holes[1][idx]; // FISH_TO_RIGHT
                    }
                }

                sp1_PrintAtInv( idx_j, floor_holes[0][idx],  INK_MAGENTA | PAPER_CYAN | BRIGHT, x);
            }
        }
        idx_j += 2;
  }

  // lower down
  for(idx = 0; idx <= bincat_in_bin; ++idx) {
      intrinsic_halt();
  }

  idx_j = 4;
  for(idx = 0; idx != TOTAL_EELS; ++idx) {
       if (check_udg_collision(idx_j, floor_holes[2][idx]) || check_udg_collision(idx_j, floor_holes[2][idx] + 1)) {
            get_out_of_level4(ELECTRIFIED);
            return;
       }
       sp1_PrintAtInv( idx_j, floor_holes[2][idx],  INK_BLACK | PAPER_CYAN | BRIGHT, ' ');
       sp1_PrintAtInv( idx_j, floor_holes[2][idx] + 1,  INK_BLACK | PAPER_CYAN | BRIGHT, ' ');

        opened_window = (frame >= 2); // if frame should move +1 (HEAD, HEAD FRAME2)
        if(floor_holes[3][idx] == EEL_TO_RIGHT) {
            ++floor_holes[2][idx];
            first_keypress = UDG_EEL_TAIL + opened_window;
            bincat_appears = UDG_EEL_HEAD + opened_window;

            if(floor_holes[2][idx] >= 30) {
                floor_holes[3][idx] = EEL_TO_LEFT;
            }
        } else {  /// EEL_TO_LEFT
            --floor_holes[2][idx];
            first_keypress = UDG_EEL_LEFT_HEAD + opened_window; // LEFT_HEAD
            bincat_appears = UDG_EEL_LEFT_TAIL + opened_window; // LEFT TAIL

            if(floor_holes[2][idx] == 0) {
                floor_holes[3][idx] = EEL_TO_RIGHT;
            }
        }

        if(frame == 2) {
            x = INK_WHITE | PAPER_CYAN | BRIGHT;
        } else {
            x = INK_BLACK | PAPER_CYAN | BRIGHT;
        }

        sp1_PrintAtInv( idx_j, floor_holes[2][idx], x, first_keypress);
        sp1_PrintAtInv( idx_j, floor_holes[2][idx] + 1, x, bincat_appears);  // +1 if frame 2, +2 if frame 1

    idx_j += 4;
  }

  // cat checks
  if(frame == 2 && misifu.y >= 1) {
      --misifu.draw_additional;

      if(misifu.draw_additional == 20) {
        zx_border(INK_BLUE);
      } else if(misifu.draw_additional == 10) {
        zx_border(INK_RED);
      } else if(misifu.draw_additional == 0) {
        get_out_of_level4(OXYGEN);
        return;
      }
  } else if(misifu.y == 0) {
      // breathe
      misifu.draw_additional = 30;
      zx_border(INK_BLACK);
  }

  if(eaten_items == TOTAL_FISHES) {
    get_out_of_level4(WON_LEVEL);
  }
}
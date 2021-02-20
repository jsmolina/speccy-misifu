#ifndef _LEVEL1
#define _LEVEL1

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <stdlib.h>
#include <sound.h> // for bit_beepfx()
#include "defines.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level_last.h"

#define TILES_BASE 128
#define TILES_LEN 30


#define UDG_JLADRILLOS 128
#define UDG_QUESO 129
#define UDG_PIEDRAS 130
#define UDG_VALLA2 131
#define UDG_VALLA1 132
#define UDG_VALLA3 133
#define UDG_VALLA4 134
#define UDG_CUBODOWN1 135
#define UDG_CUBODOWN2 136
#define UDG_CUBODOWN3 137
#define UDG_CUBOMIDDLE1 138
#define UDG_CUBOMIDDLE2 139
#define UDG_CUBOMIDDLE3 140
#define UDG_CUBOTOP1 141
#define UDG_CUBOTOP2 142
#define UDG_CUBOTOP3 143
#define UDG_C 144
#define UDG_A 145
#define UDG_T 146
#define UDG_ROPE 147
#define UDG_WIN1 148
#define UDG_WIN2 149
#define UDG_CLOTHES11 150
#define UDG_CLOTHES12 151
#define UDG_CLOTHES21 152
#define UDG_CLOTHES22 153
#define UDG_BOOT 154
#define UDG_PANTIES 155
#define UDG_VALLAROTA 156
#define UDG_VOLUMEN 157

#define MAX_COORDS_LADRILLOS 45
#define TOTAL_COORDS_SUELO 15
#define BACKGROUND_LVL1_DEFAULT 0x58   // INK BLACK, PAPER MAGENTA, BRIGHT
#define BACKGROUND_LVL1_CYAN 0x68


const uint8_t coords_lad [] = {0x00, 0x01, 0x0a, 0x05, 0x01, 0x0d, 0x01, 0x23, 0x21, 0x2f, 0x29, 0x31, 0x31, 0x31,
    0x3c, 0x31, 0x3d, 0x31, 0x41, 0x4f, 0x41, 0x7f, 0x71, 0x79, 0x71, 0x88, 0x89, 0x87, 0x81, 0xb0, 0xbd, 0xb1,
    0xc0, 0xc1, 0xc7, 0xcf, 0xc2, 0xd1, 0xd6, 0xd2, 0xd7, 0xd1, 0xd6, 0xd1, 0xd7};

const uint8_t coords_suelo [] = {0x0c, 0x05, 0x0b, 0x10, 0x15, 0x18, 0x16, 0x14, 0x17, 0x22, 0x25, 0x24, 0x24, 0x23, 0x29};
const uint16_t suelo_flags = 0x69b2;

uint8_t is_in_bin(uint8_t x_pos) {
    if (x_pos == 0 || x_pos == 1 || x_pos == 2) {
        return 1;
    } else if(x_pos == 4 || x_pos == 5 || x_pos == 6) {
        return 2;
    } else if(x_pos == 8 || x_pos == 9 || x_pos == 10) {
        return 3;
    } else if(x_pos == 19 || x_pos == 20 || x_pos == 21) {
        return 4;
    } else if(x_pos == 23 || x_pos == 24 || x_pos == 25) {
        return 5;
    }

    return NONE;
}

inline uint8_t  get_cubo_offset() {
    if(x == 1 || x == 5 || x == 9 || x == 20 || x == 24) {
        return 0;
    }
    if(x == 2 || x == 6 || x == 10 || x == 21 || x == 25) {
        return 1;
    }

    if(x == 3 || x == 7 || x == 11 || x == 22 || x == 26) {
        return 2;
    }

    return UNDEF;
}


void paint_window(uint16_t colour, uint8_t udg_id) {
  uint8_t second_udg;

  if(opened_window > 11) {
    return;
  }

  for (x = 0; x != 2; ++x) {
      sp1_PrintAtInv(windows[opened_window].y + x,
                     windows[opened_window].x,
                     BACKGROUND_LVL1_DEFAULT,
                     UDG_VOLUMEN);
  }

  for (x = windows[opened_window].x + 1; x != windows[opened_window].x + 5; ++x) {
    // top is equal
    sp1_PrintAtInv(windows[opened_window].y, x, colour, udg_id);
    if(udg_id == ' ') {
        second_udg = UDG_WIN1;
    } else {
        second_udg = udg_id;
    }
    sp1_PrintAtInv(windows[opened_window].y + 1, x, colour, second_udg);
  }
}

void print_lives() {
    sp1_PrintAtInv( 17, 27, INK_CYAN | PAPER_BLACK | BRIGHT, 48 + lives);
    print_points();
    repaint_lives = 0;
}

void paint_bricks(uint8_t clean) {
  // paint bricks (decompressing!)
  idx_j = 255; // idx_j is y, idx is x
  for(x=0; x != MAX_COORDS_LADRILLOS; ++x) {
    // y
    // if y changes, x returns to zero
    if (((coords_lad[x] & 0xF0) >> 4) != idx_j) {
        idx = 0;
    }

    idx_j = (coords_lad[x] & 0xF0) >> 4;
    // special case for reloading just clothes row
    if(clean == 1 && (idx_j != 6 && idx_j != 7 && idx_j != 10 && idx_j != 11)) {
        continue;
    }

    // x has relative coordinates jump with previous
    idx += (coords_lad[x] & 0x0F);
    // 15 is used as 'larger jump, no paint'
    if((coords_lad[x] & 0x0F) == 15) {
        continue;
    }
    sp1_PrintAtInv(idx_j, idx, BACKGROUND_LVL1_DEFAULT, UDG_JLADRILLOS);
  }
}

void  print_background_lvl1() {
  uint8_t *pt = tiles_lvl1;

  level = 1;
  opened_window = NONE;
  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  BACKGROUND_LVL1_DEFAULT, ' ' );

  sp1_Invalidate(&full_screen);

  for (idx = 0; idx < TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(TILES_BASE + idx, pt);
  }

  // paint valla
  for (x = 0; x!=MAX_X; ++x) {

      if (x % 2 == 0) {
        idx_j = UDG_VALLA1;
      } else if (x % 3 == 0) {
        idx_j = UDG_VALLA4;
      } else {
        idx_j = UDG_VALLA3;
      }
      sp1_PrintAt(15, x,  PAPER_CYAN | BRIGHT, idx_j);

      for (idx_j=16; idx_j!=21; ++idx_j)
      {
          sp1_PrintAt( idx_j, x,  PAPER_CYAN | BRIGHT, UDG_VALLA2);
      }

      // this func uses x and modifies frame (ugly thing, saving memory...)
      frame = get_cubo_offset();

      if(frame != UNDEF) {
          // cubo
          idx_j = 22;
          if((x >= 5 && x<=7)  ||  (x >= 20 && x<=22)) {
             idx_j = 21;
          }
          //
          sp1_PrintAtInv(idx_j, x, BACKGROUND_LVL1_DEFAULT, UDG_CUBODOWN1 + frame);
          sp1_PrintAtInv(idx_j - 1, x, BACKGROUND_LVL1_DEFAULT, UDG_CUBOMIDDLE1 + frame);
          sp1_PrintAtInv(idx_j - 2, x, BACKGROUND_LVL1_DEFAULT, UDG_CUBOMIDDLE1 + frame);
          sp1_PrintAtInv(idx_j - 3, x, BACKGROUND_LVL1_DEFAULT, UDG_CUBOTOP1 + frame);
      }

  }
  sp1_PrintAtInv(17, 3, BACKGROUND_LVL1_CYAN, UDG_VALLAROTA);
  sp1_PrintAtInv(18, 13, BACKGROUND_LVL1_CYAN, UDG_VALLAROTA);
  sp1_PrintAtInv(20, 18, BACKGROUND_LVL1_CYAN, UDG_VALLAROTA);
  sp1_PrintAtInv(16, 23, BACKGROUND_LVL1_CYAN, UDG_VALLAROTA);

  print_lives();

  sp1_PrintAt( 17, 29, BACKGROUND_LVL1_CYAN, UDG_C);
  sp1_PrintAt( 17, 30,  BACKGROUND_LVL1_CYAN, UDG_A);
  sp1_PrintAt( 17, 31,  BACKGROUND_LVL1_CYAN, UDG_T);

  // paint the ropes
  for (idx=0; idx != MAX_X; ++idx) {
    sp1_PrintAt(9, idx, BACKGROUND_LVL1_DEFAULT, UDG_ROPE);
    sp1_PrintAt(5, idx, BACKGROUND_LVL1_DEFAULT, UDG_ROPE);
    sp1_PrintAt(1, idx, BACKGROUND_LVL1_DEFAULT, UDG_ROPE);
  }

  // paint bricks (decompressing!)
  paint_bricks(0);

  idx_j = 255;
  for(x=0; x != TOTAL_COORDS_SUELO; ++x) {
      // frame will be zero or one (thus queso or piedras)
      frame = ((suelo_flags >> x) & 1);
      // coords_suelo
      if (((coords_suelo[x] & 0xF0) >> 4) != idx_j) {
         idx = 0;
      }
      idx_j = ((coords_suelo[x] & 0xF0) >> 4);

      idx += (coords_suelo[x] & 0x0F);
      sp1_PrintAt(idx_j + 21, idx,  BACKGROUND_LVL1_DEFAULT, UDG_QUESO + frame);
  }


   idx_j = 4;
   idx = 2;
   // define how to paint windows
   for(opened_window = 0; opened_window != 12; ++opened_window) {
      windows[opened_window].x = idx;
      windows[opened_window].y = idx_j;
      idx = idx + 8;
      if (idx >= 32) {
        idx = 2;
        idx_j = idx_j + 4;
      }

      paint_window(PAPER_CYAN | BRIGHT, ' ');
   }
   opened_window = UNDEF;

   reset_misifu_position();
   bincat_appears = NONE;
   bincat_in_bin = NONE;

   level_x_max = 28;
   level_x_min = 1;

   // row 1 and row 2 of clothes
   for(idx_j = 0; idx_j != 2; ++idx_j) {
       for(idx = 0; idx != 5; ++idx) { // vest, boots, panties
           floor_holes[idx_j][idx] = idx + 1; // 0,1,2,3
           floor_holes[idx_j][idx + 5] = idx + 18; // 4,5,6,7
       }
   }
   floor_holes[2][0] = UDG_CLOTHES11;
   floor_holes[2][1] = UDG_CLOTHES12;
   floor_holes[2][2] = UDG_BOOT;
   floor_holes[2][3] = UDG_BOOT;
   floor_holes[2][4] = UDG_PANTIES;

   aux_object.offset = AUX_PHONE;
   // make disapear for sure
   sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1, 16, 33, 0, 0);

   //sp1_UpdateNow();
}

void paint_clothes(uint8_t clean) {
    uint8_t udg_topaint = ' ';
    uint8_t color;
    idx_j = 0;
    if(clean == 1) {
        color = BACKGROUND_LVL1_DEFAULT;
    } else {
        color = INK_WHITE | PAPER_MAGENTA | BRIGHT;
    }
    for(idx = 0; idx!= 10; ++idx) { // indexes go from 0 to 9
        if (clean == 0) {
            if (floor_holes[0][idx] == 0) {
                floor_holes[0][idx] = 32;
            }

            // row1
            --floor_holes[0][idx];
            ++floor_holes[1][idx];

            if (floor_holes[1][idx] > 31) {
                floor_holes[1][idx] = 0;
            }
        }

        level_time = 0;
        for (x = 6; x != 14; x += 4, ++level_time) {
            if(clean == 0) {
                udg_topaint = floor_holes[2][idx_j];
            }
            sp1_PrintAtInv(x, floor_holes[level_time][idx], color, udg_topaint);

            if(floor_holes[2][idx_j] == UDG_CLOTHES11) {
                if(clean == 0) {
                    udg_topaint = UDG_CLOTHES21;
                }
                sp1_PrintAtInv(x + 1, floor_holes[level_time][idx], color, udg_topaint);
            } else if(floor_holes[2][idx_j] == UDG_CLOTHES12) {
                if(clean == 0) {
                    udg_topaint = UDG_CLOTHES22;
                }
                sp1_PrintAtInv(x + 1, floor_holes[level_time][idx], color, udg_topaint);
            }
        }

        ++idx_j;
        if(idx_j == 5) { // while udgs go from 0 to 4
           idx_j = 0;
        }
    }
}

inline void anim_windows() {
    if(repaint_lives == 1) {
        print_lives();
    }

    // decide if window should open
    // OPEN
    if (opened_window_frames == NONE) {
        if (random_value > 125) {
            opened_window = random_value - 125;
        } else {
            opened_window = random_value;
        }

        if(opened_window < 12) {
            // makes the window to be opened for about 20 frames
            opened_window_frames = 50;
            paint_window(INK_BLACK | PAPER_WHITE, UDG_WIN2);
            aux_object.y = windows[opened_window].y;
            aux_object.x = windows[opened_window].x;
            horizontal_direction = NONE;

            if (misifu.y < 14 && random_value < 200) {
                // detect where to go and randomly throw an object
                if(misifu.x < aux_object.x && (aux_object.x - misifu.x) > 2) {
                    horizontal_direction = LEFT;
                } else if(misifu.x > aux_object.x && ( misifu.x - aux_object.x) > 2) {
                    horizontal_direction = RIGHT;
                }

                if(misifu.y < aux_object.y && (aux_object.y - misifu.y) > 2) {
                    horizontal_direction |= UP;
                } else if(misifu.y > aux_object.y && (misifu.y - aux_object.y) > 2) {
                    horizontal_direction |= DOWN;
                }
            }

        }
    } else {
        --opened_window_frames;

        if (horizontal_direction != NONE) {
            if(misifu.state != FALLING_FLOOR && misifu.y < 14 && abs(misifu.x - aux_object.x) < 2 && abs(misifu.y - aux_object.y) < 2) {
                bit_beepfx_di_fastcall(BEEPFX_HIT_2);
                aux_object.offset = AUX_ZAP;
                misifu.state = FALLING_FLOOR;
            } else {
                // now move accordingly
                if ((horizontal_direction & LEFT) != 0) {
                    --aux_object.x;
                } else if ((horizontal_direction & RIGHT) != 0){
                    ++aux_object.x;
                }

                if ((horizontal_direction & UP) != 0) {
                    --aux_object.y;
                } else if ((horizontal_direction & DOWN) != 0) {
                    ++aux_object.y;
                }
            }
            sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, aux_object.x, 0, 0);
        }

    }
    // end of windows
    if (opened_window_frames == 1) {
        paint_window(PAPER_CYAN | BRIGHT, ' ');
        opened_window = UNDEF;
        opened_window_frames = NONE;
        aux_object.offset = AUX_PHONE;
        // move outside of screen
        sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, 33, 0, 0);

    }
}



inline void check_bincat() {
    // checks if bincat should appear and where
    if (bincat_appears == NONE && misifu.in_bin != NONE) {
        bincat_in_bin = random_value % 6;
        // less probable
        if(bincat_in_bin != NONE) {
            //anim_frames_bincat = 20;

            if (bincat_in_bin == HIGHER_BIN_X || bincat_in_bin == HIGHER_BIN_X2) {
                // reused as row and also number of frames appearing
                bincat_appears = 16;
            } else {
                bincat_appears = 17;
            }
            sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1+ AUX_BINCAT, bincat_appears, bin_places2[bincat_in_bin], 0, 0);
            bincat_appears = 40;

        } else {
            bincat_in_bin = NONE;
        }
    }

    // delete bincat after some frames
    if (bincat_appears != NONE) {
        --bincat_appears;

        // cat falls if cat_in_bin is the same of bincat_in_bin
        if (bincat_in_bin == misifu.in_bin) {
            misifu.state = FALLING_FLOOR;
            misifu.in_bin = NONE;
            bit_beepfx_di_fastcall(BEEPFX_HIT_1);
        }

        if (bincat_appears <= 1) {
            sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1, 16, 33, 0, 0);
            bincat_appears = NONE;
            bincat_in_bin = 0;
        }
    }
}

inline void detect_fall_in_bin() {
    // detect falling over bin
    if(misifu.y == 15 || misifu.y == 18) {
        misifu.in_bin = is_in_bin(misifu.x);
        // store that it is on first bin pos so collide will bincat is easier
        //misifu.in_bin = misifu.x - (bin_places[misifu.x] - 1);
        if (misifu.in_bin != NONE && misifu.in_bin != bincat_in_bin) {
            if (misifu.y == 15 && (misifu.in_bin == HIGHER_BIN_X || misifu.in_bin == HIGHER_BIN_X2)) {
                misifu.y = 16;
                // stop falling
                misifu.state = NONE;
                misifu.draw_additional = CAT_IN_BIN;
            } else if (misifu.y == 18 && misifu.in_bin != HIGHER_BIN_X && misifu.in_bin != HIGHER_BIN_X2) {
                misifu.state = NONE;
                misifu.draw_additional = CAT_IN_BIN;
            }
        }
    } else if(misifu.y == 12) {
        misifu.y = 13;
        misifu.state = NONE;
        misifu.draw_additional = CAT_IN_FENCE;
    // now check ropes TODO check ropes clothes are not colliding
    } else if(misifu.y == 10) {
        misifu.state = CAT_IN_ROPE;
        misifu.draw_additional = CAT_IN_ROPE1;
    } else if(misifu.y == 6) {
        misifu.state = CAT_IN_ROPE;
        misifu.draw_additional = CAT_IN_ROPE2;
    }
}


void detect_fall_in_window() {
    if(misifu.state != FALLING && misifu.state != JUMPING) {
        return;
    }
    idx = misifu.x - 1;
    if(opened_window < 12 && (abs(misifu.y - windows[opened_window].y) < 2)
        && ((idx > (windows[opened_window].x - 2) && idx < windows[opened_window].x + 4)) ) {
        if(last_success_level == 0) {
            print_background_level2();
        } else if(last_success_level == 2) {
            print_background_level3();
        }  else if(last_success_level == 4) {
            print_background_level5();
        } else if(last_success_level == 5) {
            print_background_level6();
        } else if(last_success_level == 6) {
            print_background_level7();
        } else if(last_success_level == 7) {
            print_background_level_last();
        }
        return;
    }

}

void level1_loop() {
    //move_clothes();
    // move clothes to the right
    if((frame & 1) == 0) {
        paint_bricks(1);
        paint_clothes(1);
        paint_clothes(0);
        // now move cat
        if(misifu.state == CAT_IN_ROPE) {
            if(misifu.draw_additional == CAT_IN_ROPE1 || misifu.draw_additional == CAT_IN_ROPE3) {
                 ++misifu.x;
                 if(misifu.x >= 28) {
                    misifu.state = FALLING;
                    misifu.draw_additional = NONE;
                    ++misifu.y;
                }
            } else if(misifu.draw_additional == CAT_IN_ROPE2) {
                --misifu.x;
                if(misifu.x == 0) {
                    misifu.state = FALLING;
                    misifu.draw_additional = NONE;
                    ++misifu.y;
                }
            }
            if(misifu.x >= 28 || misifu.x == 0) {
                misifu.state = FALLING;
                misifu.draw_additional = NONE;
                ++misifu.y;
            }
        }
    }

    anim_windows();
    check_bincat();
    dog_checks();
    if (misifu.state == FALLING) {
        detect_fall_in_bin();
    }
    detect_fall_in_window();
}

#endif

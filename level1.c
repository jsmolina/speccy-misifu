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
#define TILES_LEN 29


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

uint8_t tiles[] = {
0x00, 0x01, 0x01, 0x7e, 0x00, 0x10, 0x10, 0xe7, // y:0, x:0 (128)
0x00, 0x80, 0x04, 0x00, 0x08, 0x40, 0x01, 0x00, // y:0, x:1 (129)
0x00, 0x00, 0x00, 0x26, 0x0b, 0x87, 0x10, 0x00, // y:0, x:2 (130)
0x05, 0x0b, 0x05, 0x0b, 0x05, 0x03, 0x05, 0x0b, // y:0, x:3 (131)
0x30, 0xf0, 0xf8, 0xf4, 0xf8, 0xf4, 0xfa, 0xf4, // y:0, x:4 (132)
0x00, 0x00, 0x30, 0x3c, 0x3a, 0xfc, 0xfa, 0xf4, // y:0, x:5 (133)
0x00, 0x0c, 0xca, 0xdc, 0xfa, 0xfc, 0xfa, 0xf4, // y:0, x:6 (134)
0x16, 0x76, 0x78, 0x9f, 0x60, 0x9f, 0xe0, 0xff, // y:0, x:7 (135)
0x4a, 0x46, 0x4a, 0x3c, 0x00, 0xff, 0x00, 0xff, // y:0, x:8 (136)
0x48, 0x2e, 0x1e, 0xf9, 0x06, 0xf9, 0x07, 0xff, // y:0, x:9 (137)
0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, // y:0, x:10 (138)
0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46, // y:0, x:11 (139)
0x48, 0x2a, 0x48, 0x2a, 0x48, 0x2a, 0x48, 0x2a, // y:0, x:12 (140)
0x1f, 0x62, 0x9e, 0x7f, 0x7f, 0x9f, 0xe1, 0x9e, // y:0, x:13 (141)
0x02, 0x05, 0x02, 0x00, 0xc0, 0xf8, 0xff, 0x00, // y:0, x:14 (142)
0x61, 0x99, 0x57, 0x91, 0x20, 0x00, 0x01, 0xff, // y:0, x:15 (143)
0x01, 0x39, 0x6d, 0x61, 0x61, 0x75, 0x3d, 0x19, // y:0, x:16 (144)
0x01, 0x1b, 0x3d, 0x65, 0x7d, 0xcd, 0xd9, 0x1b, // y:0, x:17 (145)
0x01, 0x7d, 0xf1, 0xb3, 0x31, 0x1b, 0x19, 0x1b, // y:0, x:18 (146)
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, // y:0, x:19 (147)
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, // y:0, x:20 (148)
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // y:0, x:21 (149)
0x10, 0x30, 0x38, 0x7c, 0x6f, 0x6d, 0x6f, 0x0d, // y:0, x:22 (150)
0x18, 0x1c, 0x3e, 0x7e, 0xee, 0xee, 0xee, 0xf0, // y:0, x:23 (151)
0x0f, 0x0d, 0x0f, 0x0d, 0x1f, 0x1e, 0x18, 0x00, // y:0, x:24 (152)
0x0f, 0x0f, 0x07, 0x07, 0x03, 0xc3, 0xf3, 0xff, // y:0, x:25 (153)
0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x3e, 0x7c, 0x70, // y:0, x:26 (154)
0x7e, 0x1c, 0x00, 0x81, 0xc3, 0xe7, 0xff, 0xff, // y:0, x:27 (155)
0x05, 0x0b, 0x25, 0x33, 0x35, 0x33, 0x15, 0x0b, // y:0, x:28 (156)
};


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

uint8_t  get_cubo_offset() {
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


void paint_window(uint16_t colour) {

  if(opened_window > 11) {
    return;
  }

  for (x = windows[opened_window].x; x != windows[opened_window].x + 5; ++x) {
    // top is equal
    sp1_PrintAtInv(windows[opened_window].y, x, colour, UDG_WIN2);
    if (opened_window > 7) {
        // bottom varies
        sp1_PrintAtInv(windows[opened_window].y + 1, x, colour, UDG_WIN2);
    } else {
        sp1_PrintAtInv(windows[opened_window].y + 1, x, colour, UDG_WIN1);
    }
  }
}

void print_lives() {
    sp1_PrintAtInv( 17, 27, INK_CYAN | PAPER_BLACK, 48 + lives);
    repaint_lives = 0;
}

void  print_background_lvl1() {
  uint16_t color = INK_BLACK | PAPER_MAGENTA;
  uint8_t *pt = tiles;

  level = 1;
  opened_window = NONE;
  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, color, ' ' );

  sp1_Invalidate(&full_screen);

  for (idx = 0; idx < TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(TILES_BASE + idx, pt);
  }

  // paint valla
  for (x = 0; x!=MAX_X; ++x) {

      if (x % 2 == 0) {
        sp1_PrintAt(15, x, INK_CYAN | PAPER_BLACK, UDG_VALLA1);
      } else if (x % 3 == 0) {
        sp1_PrintAt(15, x,  INK_CYAN | PAPER_BLACK, UDG_VALLA4);
      } else {
         sp1_PrintAt(15, x,  INK_CYAN | PAPER_BLACK, UDG_VALLA3);
      }

      for (idx_j=16; idx_j!=21; ++idx_j)
      {
          sp1_PrintAt( idx_j, x,  PAPER_CYAN, UDG_VALLA2);
      }

      // this func uses x and modifies frame (ugly thing, saving memory...)
      frame = get_cubo_offset();

      if(frame != UNDEF) {
          // cubo
          idx_j = 22;
          if((x>=5 && x<=7)  ||  (x>=20 && x<=22)) {
             idx_j = 21;
          }
          //
          sp1_PrintAtInv(idx_j, x, INK_BLACK | PAPER_MAGENTA, UDG_CUBODOWN1 + frame);
          sp1_PrintAtInv(idx_j - 1, x, INK_BLACK | PAPER_MAGENTA, UDG_CUBOMIDDLE1 + frame);
          sp1_PrintAtInv(idx_j - 2, x, INK_BLACK | PAPER_MAGENTA, UDG_CUBOMIDDLE1 + frame);
          sp1_PrintAtInv(idx_j - 3, x, INK_BLACK | PAPER_MAGENTA, UDG_CUBOTOP1 + frame);
      }
  }

  print_lives();

  sp1_PrintAt( 17, 29, INK_BLACK | PAPER_CYAN, UDG_C);
  sp1_PrintAt( 17, 30,  INK_BLACK | PAPER_CYAN, UDG_A);
  sp1_PrintAt( 17, 31,  INK_BLACK | PAPER_CYAN, UDG_T);

  // paint the ropes
  for (idx=0; idx != MAX_X; ++idx) {
    sp1_PrintAt(9, idx, color, UDG_ROPE);
    sp1_PrintAt(5, idx, color, UDG_ROPE);
    sp1_PrintAt(1, idx, color, UDG_ROPE);
  }

  floor_holes[0][0] = UDG_JLADRILLOS;
  floor_holes[0][1] = UDG_JLADRILLOS;
  floor_holes[0][11] = UDG_JLADRILLOS;
  floor_holes[0][16] = UDG_JLADRILLOS;
  floor_holes[0][17] = UDG_JLADRILLOS;
  floor_holes[1][1] = UDG_JLADRILLOS;
  floor_holes[1][17] = UDG_JLADRILLOS;
  floor_holes[2][17] = UDG_JLADRILLOS;
  floor_holes[2][8] = UDG_JLADRILLOS;

  floor_holes[3][8] = UDG_JLADRILLOS;
  floor_holes[3][1] = UDG_JLADRILLOS;
  floor_holes[3][2] = UDG_JLADRILLOS;
  floor_holes[4][5] = UDG_PIEDRAS;
  floor_holes[4][13] = UDG_PIEDRAS;
  floor_holes[4][22] = UDG_PIEDRAS;

  frame = 0;
  for(idx = 0; idx != 6; ++idx) {
    for(idx_j = 0; idx_j != 24; ++idx_j) {
        if(floor_holes[idx][idx_j] == UDG_JLADRILLOS || floor_holes[idx][idx_j] == UDG_PIEDRAS) {
            if (idx == 4) {
                frame = 22;
                sp1_PrintAt( frame + 1, idx_j + 5, color, floor_holes[idx][idx_j]);
            }
            sp1_PrintAt( frame, idx_j, color, floor_holes[idx][idx_j]);
        }
    }
    frame += 4;
  }
  sp1_PrintAt(21,12,color, UDG_QUESO);
  sp1_PrintAt(21,27,color, UDG_QUESO);
  sp1_PrintAt(22,0,color, UDG_QUESO);
  sp1_PrintAt(23,2,color, UDG_QUESO);
  sp1_PrintAt(23,7,color, UDG_QUESO);
  sp1_PrintAt(23,15,color, UDG_QUESO);

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

      paint_window(PAPER_CYAN);
   }
   opened_window = UNDEF;

   reset_misifu_position();
   bincat_appears = 1;
   bincat_in_bin = NONE;

   level_x_max = 28;
   level_x_min = 1;

   // floor holes initialize, save memory ftw
   floor_holes[0][0] = 1;  // row1clothes
   floor_holes[0][1] = 18; // row1clothes
   floor_holes[1][0] = 1;  // row2clothes
   floor_holes[1][1] = 18; // row2clothes
   aux_object.offset = AUX_PHONE;
   sp1_UpdateNow();
}


static void repaint_clothes(uint8_t row, uint8_t col, uint8_t clean) {
    if(clean == 1) {
        sp1_PrintAtInv(row, col, PAPER_MAGENTA, ' ');
        sp1_PrintAtInv(row, col + 1, PAPER_MAGENTA, ' ');
        sp1_PrintAtInv(row + 1, col, PAPER_MAGENTA, ' ');
        sp1_PrintAtInv(row + 1, col + 1, PAPER_MAGENTA, ' ');

        sp1_PrintAtInv(row, col + 3, PAPER_MAGENTA, ' ');
        sp1_PrintAtInv(row, col + 4, PAPER_MAGENTA, ' ');
        sp1_PrintAtInv(row, col + 5, PAPER_MAGENTA, ' ');
    } else {
        sp1_PrintAtInv(row, col, INK_WHITE | PAPER_MAGENTA, UDG_CLOTHES11);
        sp1_PrintAtInv(row, col + 1, INK_WHITE | PAPER_MAGENTA, UDG_CLOTHES12);
        sp1_PrintAtInv(row + 1, col, INK_WHITE | PAPER_MAGENTA, UDG_CLOTHES21);
        sp1_PrintAtInv(row + 1, col + 1, INK_MAGENTA | PAPER_WHITE, UDG_CLOTHES22);

        sp1_PrintAtInv(row, col + 3, INK_WHITE | PAPER_MAGENTA, UDG_BOOT);
        sp1_PrintAtInv(row, col + 4, INK_WHITE | PAPER_MAGENTA, UDG_BOOT);
        sp1_PrintAtInv(row, col + 5, INK_MAGENTA | PAPER_WHITE, UDG_PANTIES);
    }
}

static void increase_indexes_clothes(uint8_t idx) {
    repaint_clothes(10, floor_holes[0][idx], 1);
    repaint_clothes(6, floor_holes[1][idx], 1);
    // row1
    --floor_holes[1][idx];
    // row2
    ++floor_holes[0][idx];
    if(floor_holes[0][idx] > 26) {
        floor_holes[0][idx] = 0;
    }

    if (floor_holes[1][idx] < 2) {
        floor_holes[1][idx] = 28;
    }
    repaint_clothes(10, floor_holes[0][idx], 0);
    repaint_clothes(6, floor_holes[1][idx], 0);
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
            paint_window(PAPER_BLACK | INK_WHITE);
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
            sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, aux_object.x, 0, 0);
        }

    }
    // end of windows
    if (opened_window_frames == 1) {
        paint_window(PAPER_CYAN);
        opened_window = UNDEF;
        opened_window_frames = NONE;
        aux_object.offset = AUX_PHONE;
        // move outside of screen
        sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, 33, 0, 0);

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
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)AUX_BINCAT, bincat_appears, bin_places2[bincat_in_bin], 0, 0);
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
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)AUX_BINCAT, 16, 33, 0, 0);
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
    } else if(misifu.y == 9) {
        misifu.state = CAT_IN_ROPE;
        misifu.draw_additional = CAT_IN_ROPE1;
    } else if(misifu.y == 5) {
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
        && ((idx >= (windows[opened_window].x - 2) && idx < windows[opened_window].x + 4)) ) {
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
    increase_indexes_clothes(0);
    increase_indexes_clothes(1);
    // now move cat
    if(misifu.draw_additional == CAT_IN_ROPE1 || misifu.draw_additional == CAT_IN_ROPE3) {
         ++misifu.x;
    } else if(misifu.draw_additional == CAT_IN_ROPE2) {
        --misifu.x;
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

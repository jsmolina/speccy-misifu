#ifndef _LEVEL1
#define _LEVEL1

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <stdlib.h>
#include <sound.h> // for bit_beepfx()
#include "defines.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level_last.h"


const uint8_t udg_valla1[] = {0xcf, 0xf, 0x7, 0xb, 0x7, 0xb, 0x5, 0xb};
const uint8_t udg_valla2[] = {0x5, 0xb, 0x5, 0xb, 0x5, 0x3, 0x5, 0xb};
const uint8_t udg_valla3[] = {0xff, 0xff, 0xcf, 0xc3, 0xc5, 0x3, 0x5, 0xb};
const uint8_t udg_valla4[] = {0xff, 0xf3, 0x35, 0x23, 0x5, 0x3, 0x5, 0xb};

const uint8_t cubo_down1[] = {0xe9, 0x89, 0x87, 0x60, 0x9f, 0x60, 0x1f, 0x0};
const uint8_t cubo_down2[] = {0x4a, 0x46, 0x4a, 0x3c, 0x0, 0xff, 0x0, 0xff};
const uint8_t cubo_down3[] = {0xb7, 0xd1, 0xe1, 0x6, 0xf9, 0x6, 0xf8, 0x0};

const uint8_t cubo_middle1[] = {0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9};
const uint8_t cubo_middle2[] = {0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46};
const uint8_t cubo_middle3[] = {0xb7, 0xd5, 0xb7, 0xd5, 0xb7, 0xd5, 0xb7, 0xd5};

const uint8_t cubotop1[] = {0x1f, 0x62, 0x9e, 0x7f, 0x7f, 0x9f, 0xe1, 0x9e};
const uint8_t cubotop2[] = {0x2, 0x5, 0x2, 0x0, 0xc0, 0xf8, 0xff, 0x0};
const uint8_t cubotop3[] = {0x61, 0x99, 0x57, 0x91, 0x20, 0x0, 0x1, 0xff};

const uint8_t udg_rope[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd2};
const uint8_t udg_win1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d}; // with rope

const uint8_t udg_c[] = {0x1, 0x39, 0x6d, 0x61, 0x61, 0x75, 0x3d, 0x19};
const uint8_t udg_a[] = {0x1, 0x1b, 0x3d, 0x65, 0x7d, 0xcd, 0xd9, 0x1b};
const uint8_t udg_t[] = {0x1, 0x7d, 0xf1, 0xb3, 0x31, 0x1b, 0x19, 0x1b};

const uint8_t udg_clothes11[] = {0x10, 0x30, 0x38, 0x7c, 0x6f, 0x6d, 0x6f, 0xd};
const uint8_t udg_clothes12[] = {0x18, 0x1c, 0x3e, 0x7e, 0xee, 0xee, 0xee, 0xf0};
const uint8_t udg_clothes21[] = {0xf, 0xd, 0xf, 0xd, 0x1f, 0x1e, 0x18, 0x0};
const uint8_t udg_clothes22[] = {0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x3c, 0xc, 0x0};
const uint8_t udg_boot[] = {0xe, 0xe, 0xe, 0xe, 0x1e, 0x3e, 0x7c, 0x70};
const uint8_t udg_boot2[] = {0x81, 0xe3, 0xff, 0x7e, 0x3c, 0x18, 0x0, 0x0};

const uint8_t j_ladrillos[] = {0x0, 0x1, 0x1, 0x7e, 0x0, 0x10, 0x10, 0xe7};
const uint8_t j_piedras[] = {0x0, 0x0, 0x0, 0x26, 0xb, 0x87, 0x10, 0x0};

uint8_t is_in_bin(uint8_t x_pos) {
    if (x_pos == 0 || x_pos == 1 || x_pos == 2) {
        return 1;
    } else if(x_pos == 4 || x_pos == 5 || x_pos == 6) {
        return 5;
    } else if(x_pos == 8 || x_pos == 9 || x_pos == 10) {
        return 9;
    } else if(x_pos == 19 || x_pos == 20 || x_pos == 21) {
        return 20;
    } else if(x_pos == 23 || x_pos == 24 || x_pos == 25) {
        return 24;
    }

    return NONE;
}

// todo add udg for numbers (score, lives)

void  print_cubo(uint8_t x) {
  idx_j = 22;
  if(x == HIGHER_BIN_X || x == HIGHER_BIN_X2) {
     idx_j = 21;
  }
  sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'L');
  sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'D');
  sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'E');

  --idx_j;
  sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

  --idx_j;
  sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

  --idx_j;
  sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'I');
  sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'J');
  sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'K');

  --idx_j;
  for (idx_j = idx_j; idx_j != 15; --idx_j) {
    sp1_PrintAt( idx_j, x, PAPER_CYAN, 'V');
    sp1_PrintAt( idx_j, x + 1, PAPER_CYAN, 'V');
    sp1_PrintAt( idx_j, x + 2, PAPER_CYAN, 'V');
  }
  sp1_PrintAt(idx_j, x, PAPER_CYAN, 'W');
  sp1_PrintAt(idx_j, x + 1, PAPER_CYAN, 'W');
  sp1_PrintAt(idx_j, x + 2, PAPER_CYAN, 'X');
}


void paint_window(uint16_t colour) {

  if(opened_window > 11) {
    return;
  }

  for (x = windows[opened_window].x; x != windows[opened_window].x + 5; ++x) {
    // top is equal
    sp1_PrintAtInv(windows[opened_window].y, x, colour, 'N');
    if (opened_window > 7) {
        // bottom varies
        sp1_PrintAtInv(windows[opened_window].y + 1, x, colour, 'N');
    } else {
        sp1_PrintAtInv(windows[opened_window].y + 1, x, colour, 'M');
    }
  }
}

void print_lives() {
    sp1_PrintAtInv( 17, 27, INK_CYAN | PAPER_BLACK, 48 + lives);
    repaint_lives = 0;
}

void  print_background_lvl1() {
  uint16_t color = INK_BLACK | PAPER_MAGENTA;

  level = 1;
  opened_window = NONE;
  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE, color, ' ' );

  sp1_Invalidate(&full_screen);
  sp1_TileEntry('$', j_ladrillos);
  sp1_TileEntry(144, queso_textura);
  sp1_TileEntry('%', j_piedras);
  sp1_TileEntry('V', udg_valla2);  // middle of fence
  sp1_TileEntry('W', udg_valla1);  // top of fence
  sp1_TileEntry('X', udg_valla3); // another top of fence
  sp1_TileEntry('Y', udg_valla4); // another top of fence
  sp1_TileEntry('L', cubo_down1);
  sp1_TileEntry('D', cubo_down2);
  sp1_TileEntry('E', cubo_down3);
  sp1_TileEntry('F', cubo_middle1);
  sp1_TileEntry('G', cubo_middle2);
  sp1_TileEntry('H', cubo_middle3);
  sp1_TileEntry('I', cubotop1);
  sp1_TileEntry('J', cubotop2);
  sp1_TileEntry('K', cubotop3);
  sp1_TileEntry('C', udg_c);
  sp1_TileEntry('A', udg_a);
  sp1_TileEntry('T', udg_t);

  sp1_TileEntry('R', udg_rope); // da rope
  sp1_TileEntry('M', udg_win1); // bottom with rope
  sp1_TileEntry('N', udg_win2); // full square

  sp1_TileEntry('O', udg_clothes11);
  sp1_TileEntry('P', udg_clothes12);
  sp1_TileEntry('Q', udg_clothes21);
  sp1_TileEntry('S', udg_clothes22);
  sp1_TileEntry('U', udg_boot);
  sp1_TileEntry('Z', udg_boot2);

  // paint valla
  for (x = 0; x!=MAX_X; ++x) {
      frame = is_in_bin(x - 1);
      if (frame == NONE) {
          if (x % 2 == 0) {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'W');
          } else if (x % 3 == 0) {
            sp1_PrintAt(15, x,  PAPER_CYAN, 'Y');
          } else {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'X');
          }

          for (idx_j=16; idx_j!=21; ++idx_j)
          {
              sp1_PrintAt( idx_j, x,  PAPER_CYAN, 'V');
          }
      } else if(frame == x) {
          print_cubo(x);
      }
  }

  print_lives();

  sp1_PrintAt( 17, 29, INK_BLACK | PAPER_CYAN, 'C');
  sp1_PrintAt( 17, 30,  INK_BLACK | PAPER_CYAN, 'A');
  sp1_PrintAt( 17, 31,  INK_BLACK | PAPER_CYAN, 'T');

  // paint the ropes
  for (idx=0; idx != MAX_X; ++idx) {
    sp1_PrintAt(9, idx, color, 'R');
    sp1_PrintAt(5, idx, color, 'R');
    sp1_PrintAt(1, idx, color, 'R');
  }

  floor_holes[0][0] = '$';
  floor_holes[0][1] = '$';
  floor_holes[0][11] = '$';
  floor_holes[0][16] = '$';
  floor_holes[0][17] = '$';
  floor_holes[1][1] = '$';
  floor_holes[1][17] = '$';
  floor_holes[2][17] = '$';
  floor_holes[2][8] = '$';

  floor_holes[3][8] = '$';
  floor_holes[3][1] = '$';
  floor_holes[3][2] = '$';
  floor_holes[4][5] = '%';
  floor_holes[4][13] = '%';
  floor_holes[4][22] = '%';

  frame = 0;
  for(idx = 0; idx != 6; ++idx) {
    for(idx_j = 0; idx_j != 24; ++idx_j) {
        if(floor_holes[idx][idx_j] == '$' || floor_holes[idx][idx_j] == '%') {
            if (idx == 4) {
                frame = 22;
                sp1_PrintAt( frame + 1, idx_j + 5, color, floor_holes[idx][idx_j]);
            }
            sp1_PrintAt( frame, idx_j, color, floor_holes[idx][idx_j]);
        }
    }
    frame += 4;
  }
  sp1_PrintAt(21,12,color, 144);
  sp1_PrintAt(21,27,color, 144);
  sp1_PrintAt(22,0,color, 144);
  sp1_PrintAt(23,2,color, 144);
  sp1_PrintAt(23,7,color, 144);
  sp1_PrintAt(23,15,color, 144);

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
        sp1_PrintAtInv(row, col, INK_WHITE | PAPER_MAGENTA, 'O');
        sp1_PrintAtInv(row, col + 1, INK_WHITE | PAPER_MAGENTA, 'P');
        sp1_PrintAtInv(row + 1, col, INK_WHITE | PAPER_MAGENTA, 'Q');
        sp1_PrintAtInv(row + 1, col + 1, INK_WHITE | PAPER_MAGENTA, 'S');

        sp1_PrintAtInv(row, col + 3, INK_WHITE | PAPER_MAGENTA, 'U');
        sp1_PrintAtInv(row, col + 4, INK_WHITE | PAPER_MAGENTA, 'U');
        sp1_PrintAtInv(row, col + 5, INK_WHITE | PAPER_MAGENTA, 'Z');
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
        bincat_in_bin = bin_places2[random_value % 6];
        // less probable
        if(bincat_in_bin != NONE) {
            //anim_frames_bincat = 20;

            if (bincat_in_bin == HIGHER_BIN_X || bincat_in_bin == HIGHER_BIN_X2) {
                // reused as row and also number of frames appearing
                bincat_appears = 16;
            } else {
                bincat_appears = 17;
            }
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)AUX_BINCAT, bincat_appears, bincat_in_bin, 0, 0);
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

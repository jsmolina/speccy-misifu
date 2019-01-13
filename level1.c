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


const uint8_t udg_valla1[] = {0xff, 0x9f, 0x8f, 0x87, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla2[] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla3[] = {0xff, 0xe1, 0xe1, 0x81, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla4[] = {0xef, 0x8f, 0x83, 0x83, 0x83, 0x81, 0x81, 0x81};

const uint8_t cubo_down1[] = {0xab, 0xd5, 0xaa, 0xd5, 0xfe, 0x31, 0xe, 0x1};
const uint8_t cubo_down2[] = {0xff, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0x0, 0xff};
const uint8_t cubo_down3[] = {0xa9, 0x57, 0xa5, 0x5b, 0xf3, 0x8c, 0xf8, 0x80};
const uint8_t cubo_middle1[] = {0x9e, 0xa5, 0xa5, 0xba, 0x9d, 0xcf, 0xb1, 0xde};
const uint8_t cubo_middle2[] = {0x0, 0xff, 0x52, 0xad, 0x52, 0xff, 0xff, 0x0};
const uint8_t cubo_middle3[] = {0x7d, 0xa9, 0xad, 0x5d, 0xfd, 0x7b, 0x8d, 0x7f};

const uint8_t cubotop1[] = {0xff, 0xff, 0xf3, 0xcf, 0x9f, 0xbf, 0x9f, 0xcf};
const uint8_t cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
const uint8_t cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

const uint8_t udg_rope[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd2};
const uint8_t  udg_win1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d}; // with rope

const uint8_t udg_c[] = {0x62, 0x42, 0x4e, 0x4e, 0x4e, 0x62, 0x72, 0x7e};
const uint8_t udg_a[] = {0x72, 0x60, 0x4c, 0x40, 0x18, 0x12, 0x12, 0x7e};
const uint8_t udg_t[] = {0x60, 0x2, 0x12, 0x72, 0x78, 0x78, 0x78, 0x7e};


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

static uint8_t has_a_bin(uint8_t x_pos) {
    if (x_pos == 1 || x_pos == 2 || x_pos == 3) {
        return 1;
    } else if(x_pos == 5 || x_pos == 6 || x_pos == 7) {
        return 5;
    } else if(x_pos == 9 || x_pos == 10 || x_pos == 11) {
        return 9;
    } else if(x_pos == 20 || x_pos == 21 || x_pos == 22) {
        return 20;
    } else if(x_pos == 24 || x_pos == 25 || x_pos == 26) {
        return 24;
    }

    return NONE;
}

// todo add udg for numbers (score, lives)

void  print_cubo(uint8_t x) {
  uint8_t idx_j;

  idx_j = 22;
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
  // onlidx_j second bin is higher
  if(x == HIGHER_BIN_X) {
      --idx_j;
      sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

      --idx_j;
      sp1_PrintAt(idx_j, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(idx_j, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(idx_j, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');
  }

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


void paint_window(uint8_t num, uint16_t colour) {

  for (x = windows[num].x; x != windows[num].x + 5; ++x) {
    // top is equal
    sp1_PrintAtInv(windows[num].y, x, colour, 'N');
    if (num > 7) {
        // bottom varies
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'N');
    } else {
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'M');
    }
  }
}

void print_lives() {
    sp1_PrintAtInv( 17, 27, INK_CYAN | PAPER_BLACK, 48 + lives);
    repaint_lives = 0;
}

void  print_background_lvl1() {
  level = 1;

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );
  sp1_Invalidate(&full_screen);

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


  // paint valla
  for (x = 0; x!=MAX_X; ++x) {
      frame = has_a_bin(x);
      if (frame == NONE) {
          if (x % 2 == 0) {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'W');
          } else if (x % 3 == 0) {
            sp1_PrintAt(15, x,  PAPER_CYAN, 'Y');
          } else {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'X');
          }

          for (y=16; y!=21; ++y)
          {
              sp1_PrintAt( y, x,  PAPER_CYAN, 'V');
          }
      } else if(frame == x) {
          print_cubo(x);
      }
  }

  print_lives();

  sp1_PrintAt( 17, 29, INK_CYAN | PAPER_BLACK, 'C');
  sp1_PrintAt( 18, 30,  INK_CYAN | PAPER_BLACK, 'A');
  sp1_PrintAt( 19, 31,  INK_CYAN | PAPER_BLACK, 'T');

  // paint the ropes
  for (idx=0; idx != MAX_X; ++idx) {
    sp1_PrintAt(9, idx, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(5, idx, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(1, idx, INK_BLACK | PAPER_MAGENTA, 'R');
  }


   idx_j = 4;
   idx = 2;
   // define how to paint windows
   for(frame = 0; frame != 12; ++frame) {
      windows[frame].x = idx;
      windows[frame].y = idx_j;
      idx = idx + 8;
      if (idx >= 32) {
        idx = 2;
        idx_j = idx_j + 4;
      }

      paint_window(frame, PAPER_CYAN);
   }

   reset_misifu_position();
   bincat_appears = NONE;

   level_x_max = 28;
   level_x_min = 0;

   sp1_UpdateNow();
}

void leave_level() {

}



void move_clothes() {
// now take decisions
    // move clothes to the right
    if (random_value > 125 && row1_moving == NONE) {
        row1_moving = 20;
    } else if (row1_moving != NONE) {
        //--row1_moving in int.c
        if ((row1_moving & 1) == 0) {
            // check if clothes should move
            for (idx = 0; idx != 2; ++idx) {
                --row2clothes[idx].col;
                ++row1clothes[idx].col;
                if(row1clothes[idx].col > 26) {
                    row1clothes[idx].col = 0;
                }

                if (row2clothes[idx].col < 2) {
                    row2clothes[idx].col = 28;
                }
                sp1_MoveSprAbs(row1clothes[idx].sp, &full_screen, (void*)1, 10, row1clothes[idx].col, 0, 0);
                sp1_MoveSprAbs(row2clothes[idx].sp, &full_screen, (void*)1, 6, row2clothes[idx].col, 0, 0);
            }
            // now move cat
            if(misifu.draw_additional == CAT_IN_ROPE1 || misifu.draw_additional == CAT_IN_ROPE3) {
                 ++misifu.x;
            } else if(misifu.draw_additional == CAT_IN_ROPE2) {
                --misifu.x;
            }
        }

    }

}

void anim_windows() {
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
            paint_window(opened_window, PAPER_BLACK);
            aux_object.y = windows[opened_window].y;
            aux_object.x = windows[opened_window].x;
            horizontal_direction = NONE;
            vertical_direction = NONE;

            if (misifu.y < 14 && (random_value & 1) == 0) {
                // detect where to go and todo randomly throw an object
                if(misifu.x < aux_object.x && (aux_object.x - misifu.x) > 2) {
                    horizontal_direction = LEFT;
                } else if(misifu.x > aux_object.x && ( misifu.x - aux_object.x) > 2) {
                    horizontal_direction = RIGHT;
                }

                if(misifu.y < aux_object.y && (aux_object.y - misifu.y) > 2) {
                    vertical_direction = UP;
                } else if(misifu.y > aux_object.y && (misifu.y - aux_object.y) > 2) {
                    vertical_direction = DOWN;
                }
            }

        }
    } else {
        --opened_window_frames;

        if (vertical_direction != NONE || horizontal_direction != NONE) {
            if(abs(misifu.x - aux_object.x) < 2 && abs(misifu.y - aux_object.y) < 2) {
                // todo falling to loose a live
                bit_beepfx_di_fastcall(BEEPFX_HIT_2);
                aux_object.offset = AUX_ZAP;
                misifu.state = FALLING;
            } else {
                // now move accordingly
                if (horizontal_direction == LEFT) {
                    --aux_object.x;
                } else if (horizontal_direction == RIGHT){
                    ++aux_object.x;
                }

                if (vertical_direction == UP) {
                    --aux_object.y;
                } else if (vertical_direction == DOWN) {
                    ++aux_object.y;
                }
            }
            sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, aux_object.x, 0, 0);
        }

    }
    // end of windows
    if (opened_window_frames == 1) {
        paint_window(opened_window, PAPER_CYAN);
        opened_window = NONE;
        opened_window_frames = NONE;
        aux_object.offset = RIGHTC1;
        // move outside of screen
        sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, 33, 0, 0);

    }
}



void check_bincat() {
    // checks if bincat should appear and where
    if (bincat_appears == NONE && misifu.in_bin != NONE) {
        bincat_in_bin = bin_places2[random_value % 6];
        // less probable
        if(bincat_in_bin != NONE) {
            //anim_frames_bincat = 20;

            if (bincat_in_bin == HIGHER_BIN_X) {
                // reused as row and also number of frames appearing
                bincat_appears = 15;
            } else {
                bincat_appears = 17;
            }
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, bincat_appears, bincat_in_bin, 0, 0);
            bincat_appears = 40;

            // cat falls if misifu.in_bin is the same of bincat_in_bin
            if (bincat_in_bin == misifu.in_bin) {
                misifu.state = FALLING;
            }
        } else {
            bincat_in_bin = NONE;
        }
    }

    // delete bincat after some frames
    if (bincat_appears != NONE) {
        --bincat_appears;

        // cat falls if cat_in_bin is the same of bincat_in_bin
        if (bincat_in_bin == misifu.in_bin) {
            misifu.state = FALLING;
            misifu.in_bin = NONE;
            bit_beepfx_di_fastcall(BEEPFX_HIT_1);
        }

        if (bincat_appears < 1 && bincatsp != NULL) {
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, 16, 33, 0, 0);
            bincat_appears = NONE;
            bincat_in_bin = 0;
        }
    }
}

void detect_fall_in_bin() {
    // detect falling over bin
    if(misifu.y == 16 || misifu.y == 18) {
        misifu.in_bin = is_in_bin(misifu.x);
        // store that it is on first bin pos so collide will bincat is easier
        //misifu.in_bin = misifu.x - (bin_places[misifu.x] - 1);
        if (misifu.in_bin != NONE) {
            if (misifu.in_bin == HIGHER_BIN_X && misifu.y == 16) {
                // stop falling
                misifu.state = NONE;
                misifu.draw_additional = CAT_IN_BIN;
            } else if (misifu.in_bin != HIGHER_BIN_X && misifu.y == 18) {
                misifu.state = NONE;
                misifu.draw_additional = CAT_IN_BIN;

            }
        }
    } else if(misifu.y == 13) {
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
    if(misifu.state != FALLING) {
        return;
    }
    idx = misifu.x - 1;
    if(opened_window < 12 && (abs(misifu.y - windows[opened_window].y) < 2)
        && ((idx >= windows[opened_window].x && idx < windows[opened_window].x + 5)) ) {
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
        }
        return;
    }

}



#endif

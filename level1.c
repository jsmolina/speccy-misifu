#ifndef _LEVEL1
#define _LEVEL1

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <stdlib.h>
#include "defines.h"

void reset_misifu_position() {
  misifu.in_bin = NONE;
  misifu.x = 0;
  misifu.y = FLOOR_Y;
  misifu.initial_jump_y = 0;
  misifu.draw_additional = NONE;
  misifu.offset = RIGHTC1;
  misifu.state = NONE;
}

uint8_t is_in_bin(uint8_t x_pos) {
    if (x_pos == 0 || x_pos == 1 || x_pos == 2) {
        return 1;
    } else if(x_pos == 4 || x_pos == 5 || x_pos == 6) {
        return 5;
    } else if(x_pos == 8 || x_pos == 9 || x_pos == 10) {
        return 9;
    } else if(x_pos == 20 || x_pos == 21 || x_pos == 22) {
        return 20;
    } else if(x_pos == 24 || x_pos == 25 || x_pos == 26) {
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
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'O');
    } else {
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'M');
    }
  }
}

void  print_background_lvl1() {
  level = 1;

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );
  zx_border(INK_BLACK);
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
  sp1_TileEntry('O', udg_win3); // bottom without rope

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
    if (bincat_appears != YES && misifu.in_bin != NONE) {
        bincat_in_bin = bin_places2[random_value % 6];
        // less probable
        if(bincat_in_bin != NONE) {
            bincat_appears = YES;
            anim_frames_bincat = 20;

            if (bincat_in_bin == HIGHER_BIN_X) {
                // reused as row and also number of frames appearing
                anim_frames_bincat = 15;
            } else {
                anim_frames_bincat = 17;
            }
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, anim_frames_bincat, bincat_in_bin, 0, 0);
            anim_frames_bincat = 40;

            // cat falls if misifu.in_bin is the same of bincat_in_bin
            if (bincat_in_bin == misifu.in_bin) {
                misifu.state = FALLING;
            }
        } else {
            bincat_in_bin = NONE;
        }
    }

    // delete bincat after some frames
    if (bincat_appears == YES) {
        --anim_frames_bincat;

        // cat falls if cat_in_bin is the same of bincat_in_bin
        if (bincat_in_bin == misifu.in_bin) {
            misifu.state = FALLING;
            misifu.in_bin = NONE;
        }

        if (anim_frames_bincat < 1 && bincatsp != NULL) {
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




#endif

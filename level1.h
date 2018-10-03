#ifndef _LEVEL1
#define _LEVEL1

#include <defines.h>
#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>

struct udgstruct windows[14];


const uint8_t bin_places2[] = {NONE, 1, 5, 9, 20, 24};


uint8_t is_in_bin(uint8_t x_pos) {
    if (x_pos > 0 && x_pos < 4) {
        return 1;
    } else if(x_pos > 4 && x_pos  < 8) {
        return 5;
    } else if(x_pos > 8 && x_pos < 12) {
        return 9;
    } else if(x_pos > 19 && x_pos < 23) {
        return 20;
    } else if(x_pos > 23 && x_pos < 27) {
        return 24;
    }

    return NONE;
}

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

const uint8_t cubotop1[] = {0x0, 0x0, 0x33, 0x4f, 0x9f, 0xbf, 0x9f, 0xcf};
const uint8_t cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
const uint8_t cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

uint8_t udg_rope[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd2};
unsigned char udg_win1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d}; // with rope
unsigned char udg_win3[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

const uint8_t udg_c[] = {0x62, 0x42, 0x4e, 0x4e, 0x4e, 0x62, 0x72, 0x7e};
const uint8_t udg_a[] = {0x72, 0x60, 0x4c, 0x40, 0x18, 0x12, 0x12, 0x7e};
const uint8_t udg_t[] = {0x60, 0x2, 0x12, 0x72, 0x78, 0x78, 0x78, 0x7e};

// todo add udg for numbers (score, lives)

void  print_cubo(uint8_t x) {
  uint8_t y;

  y = 22;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'L');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'D');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'E');
  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');
  // only second bin is higher
  if(x == HIGHER_BIN_X) {
      --y;
      sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

      --y;
      sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');
  }

  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'I');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'J');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'K');

  --y;
  for (y = y; y != 15; y--) {
    sp1_PrintAt( y, x, PAPER_CYAN, 'V');
    sp1_PrintAt( y, x + 1, PAPER_CYAN, 'V');
    sp1_PrintAt( y, x + 2, PAPER_CYAN, 'V');
  }
  sp1_PrintAt(y, x, PAPER_CYAN, 'W');
  sp1_PrintAt(y, x + 1, PAPER_CYAN, 'W');
  sp1_PrintAt(y, x + 2, PAPER_CYAN, 'X');
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
  uint8_t x, y, count;


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
  sp1_TileEntry('O', udg_win3); // bottom without rope

  // paint valla
  for (x = 0; x!=MAX_X; ++x) {
      count = is_in_bin(x);
      if (count == NONE) {
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
      } else if(count == x) {
          print_cubo(x);
      }
  }
  sp1_PrintAt( 17, 29, INK_CYAN | PAPER_BLACK, 'C');
  sp1_PrintAt( 18, 30,  INK_CYAN | PAPER_BLACK, 'A');
  sp1_PrintAt( 19, 31,  INK_CYAN | PAPER_BLACK, 'T');

  // paint the ropes
  for (x=0; x != MAX_X; ++x) {
    sp1_PrintAt(9, x, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(5, x, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(1, x, INK_BLACK | PAPER_MAGENTA, 'R');
  }


   y = 4;
   x = 2;
   // define how to paint windows
   for(count = 0; count != 12; ++count) {
      windows[count].x = x;
      windows[count].y = y;
      x = x + 8;
      if (x >= 32) {
        x = 2;
        y = y + 4;
      }

      paint_window(count, PAPER_CYAN);
   }

}



void move_clothes() {
// now take decisions
    // move clothes to the right
    if (random_value % 20 == 0 && row1_moving == NONE) {
        row1_moving = 20;
    } else if (row1_moving != NONE) {
        --row1_moving;
        if (row1_moving % 2 == 0) {
            // check if clothes should move
            for (index = 0; index != 4; ++index) {
                row1clothes[index].col = (row1clothes[index].col + 1) % 30;
                sp1_MoveSprAbs(row1clothes[index].sp, &full_screen, 0, 10, row1clothes[index].col, 0, 0);

            }

            for (index = 0; index != 2; ++index) {
                --row2clothes[index].col;

                if (row2clothes[index].col < 2) {
                    row2clothes[index].col = 28;
                }
                sp1_MoveSprAbs(row2clothes[index].sp, &full_screen, 0, 6, row2clothes[index].col, 0, 0);
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
        opened_window = random_value % 120;
        if(opened_window < 12) {
            // makes the window to be opened for about 20 frames
            opened_window_frames = 50;
            paint_window(opened_window, PAPER_BLACK);
            aux_object.y = windows[opened_window].y;
            aux_object.x = windows[opened_window].x;
            horizontal_direction = NONE;
            vertical_direction = NONE;

            if (misifu.y < 14 && rand() % 2 == 0) {
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
                aux_object.offset = RIGHTC2;
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

void dog_checks() {
// time for doggy checks
    if (misifu.state != FIGHTING && enemy_apears == YES) {
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);

        --x_malo;

        if (x_malo <= 0) {
            enemy_apears = NONE;
            x_malo = 33;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }

        if (frame < 2) {
            dog_offset = DOG1;
        } else if (frame < 4) {
            // todo fighting will be 49 + 48
            dog_offset = DOG2;
        }

        // detects collission malo->misifu
        if( abs(misifu.x - x_malo) < 3 && misifu.y > 18) {
            enemy_apears = NONE;
            misifu.state = FIGHTING;
            misifu.y = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            misifu.x = 33;
        }
    }

    if (misifu.state == FIGHTING) {
        if (frame < 2) {
            dog_offset = DOGFIGHTING1;
        } else if (frame < 4) {
            dog_offset = DOGFIGHTING2;
        }

        --anim_frames;
        if (anim_frames < 1) {
            misifu.state = NONE;
            misifu.x = 0;
            enemy_apears = NONE;
            x_malo = 33;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
            // todo remove one live
        } else {
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }
    }
    // check if dog should appear
    if (enemy_apears != YES && first_keypress != NONE) {
        enemy_apears = random_value % 100;
    }

}

void check_bincat() {
    // checks if bincat should appear and where
    if (bincat_appears != YES && misifu.in_bin != NONE) {
        bincat_in_bin = bin_places2[rand() % 6];
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

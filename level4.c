#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"
#include "int.h"

#define BLACK_CYAN_BRIGHT 0x68
const uint8_t udg_watertop[] = {0xff, 0xef, 0xc5, 0x80, 0x0, 0x0, 0x0, 0x0};
const uint8_t udg_fish[] = {0x0, 0x9c, 0xbe, 0xfd, 0xff, 0xbf, 0x9e, 0x0};
const uint8_t udg_fishL[] = {0x0, 0x39, 0x7d, 0xbf, 0xff, 0xfd, 0x79, 0x0};
const uint8_t udg_eel[] = {0x0, 0x0, 0x0, 0x48, 0x36, 0x1, 0x0, 0x0};

static void print_eel(uint8_t y, uint8_t x, uint8_t toprint) {
    sp1_PrintAtInv(y, x,  BLACK_CYAN_BRIGHT, toprint);
}

static void assign_eels_pos(uint8_t y, uint8_t x) {
    floor_holes[idx][Y_POS] = y;
    floor_holes[idx][X_POS] = x;
    print_eel(y, x, 'E');
    ++idx;
}

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
  eaten_items = 8;
  misifu.offset = SWIM_RC1;
  // todo cat should not take too much or get out of breath... level timer
  // swimming state always here
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  BLACK_CYAN_BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);


  sp1_TileEntry('W', udg_watertop);
  sp1_TileEntry('A', udg_fish);
  sp1_TileEntry('B', udg_fishL);
  sp1_TileEntry('E', udg_eel);

  // paint watertop (once)
  for(idx = 0; idx != 32; ++idx) {
    sp1_PrintAt( 0, idx,  BLACK_CYAN_BRIGHT, 'W');
  }

  // udgxs, udgys are fishes. Mod is slow, but helps reduce code and paint might be slow.
  idx_j = 3;
  for(idx = 0; idx != 8; ++idx) {
        windows[idx].x = rand() % 28;
        windows[idx].y = idx_j;
        windows[idx].has_item = FISH_RIGHT;

         // row, col
        sp1_PrintAt( windows[idx].y, windows[idx].x,  BLACK_CYAN_BRIGHT, 'A');
        idx_j += 2; // fishes are 3, 5, 7, 9, 11, 13, 15, 17
  }

  idx = 0;
  assign_eels_pos(4, 3);
  assign_eels_pos(8, 24);
  assign_eels_pos(12, 12);
  assign_eels_pos(16, 5);
  assign_eels_pos(4, 12);


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


static void print_fish(uint8_t idx, uint8_t to_print) {
    if(to_print == 'Z') {
        return;
    }
    sp1_PrintAtInv( windows[idx].y, windows[idx].x,  BLACK_CYAN_BRIGHT, to_print);
}

void level4_loop() {

    // fish collision
    for(idx = 0; idx != 8; ++idx) {
        if(windows[idx].has_item != 'Z' && check_udg_collision(windows[idx].y, windows[idx].x) == 1) {
            windows[idx].has_item = 'Z';  // eaten fish
            repaint_lives = 1;
            // delete collided fish
            sp1_PrintAtInv(windows[idx].y, windows[idx].x, BLACK_CYAN_BRIGHT, ' ');
            windows[idx].x = 1;
            windows[idx].y = 23;
            sp1_PrintAtInv(windows[idx].y, windows[idx].x + eaten_items, INK_GREEN | PAPER_BLACK, 'A');
            bit_beepfx_di_fastcall(BEEPFX_SCORE);
            --eaten_items;

            if(eaten_items == 0) {
                get_out_of_level4(WON_LEVEL);
            }
        }
    }
    // eel collision
    for(idx = 0; idx != 5; ++idx) {

        if(check_udg_collision(floor_holes[idx][Y_POS], floor_holes[idx][X_POS]) == 1)
        {
            // loose a life and out of level
            get_out_of_level4(ELECTRIFIED);
            return;
        }
    }

    //fishes_on_move();
    if(frame_big == 1) { // 1/4 of times
        for(idx = 0; idx != 8; ++idx) {
            // move to the right until reached limits
            print_fish(idx, ' ');
            if( windows[idx].has_item == FISH_RIGHT) {
                ++windows[idx].x;
            } else if( windows[idx].has_item == FISH_LEFT) {
                --windows[idx].x;
            }
            print_fish(idx, windows[idx].has_item);

            if(windows[idx].x >= 30) {
                windows[idx].has_item = FISH_LEFT;
            } else if(windows[idx].x < 1) {
                windows[idx].has_item = FISH_RIGHT;
            }

        }
    }
    // eels on move
    if(random_value < 40) {
        for(idx = 0; idx != 5; ++idx) {
            print_eel(floor_holes[idx][Y_POS], floor_holes[idx][X_POS], ' ');
            if(floor_holes[idx][X_POS] > 30) {
                floor_holes[idx][X_POS] = 0;
            }
            ++floor_holes[idx][X_POS];
            print_eel(floor_holes[idx][Y_POS], floor_holes[idx][X_POS], 'E');
        }
    }

    // cat checks
    if(frame_big == 1 && misifu.y >= 1) {
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
}
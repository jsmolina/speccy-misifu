#include <stdlib.h>
#include "defines.h"

const uint8_t udg_watertop[] = {0xff, 0xef, 0xc5, 0x80, 0x0, 0x0, 0x0, 0x0};
const uint8_t udg_fish[] = {0x0, 0x9c, 0xbe, 0xfd, 0xff, 0xbf, 0x9e, 0x0};
const uint8_t udg_fishL[] = {0x0, 0x39, 0x7d, 0xbf, 0xff, 0xfd, 0x79, 0x0};
const uint8_t udg_eel[] = {0x0, 0x0, 0x0, 0x48, 0x36, 0x1, 0x0, 0x0};


void  print_background_level4() {
  level = 4;
  // todo cat should not take too much or get out of breath... level timer
  // swimming state always here
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_MAGENTA | PAPER_CYAN,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);


  sp1_TileEntry('W', udg_watertop);
  sp1_TileEntry('F', udg_fish);
  sp1_TileEntry('G', udg_fishL);
  sp1_TileEntry('E', udg_eel);

  // paint watertop (once)
  for(idx = 0; idx != 32; ++idx) {
    sp1_PrintAt( 0, idx,  INK_BLACK | PAPER_CYAN, 'W');
  }

  // udgxs, udgys are fishes. Mod is slow, but helps reduce code and paint might be slow.
  idx_j = 3;
  for(idx = 0; idx != 8; ++idx) {
        windows[idx].x = rand() % 28;
        windows[idx].y = idx_j;
        windows[idx].has_item = RIGHT;

         // row, col
        sp1_PrintAt( windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'F');
        idx_j += 2; // fishes are 3 5 7 9 11 13 15 19
  }

  // now eels
  idx_j = 4;
  for(idx = 0; idx != 5; ++idx) {
       // paint eels... if there's an overlap... bad luck
       floor_holes[X_AXIS][idx] = rand() % 28;
       floor_holes[Y_AXIS][idx] = idx_j;
       // row, col
       sp1_PrintAt( floor_holes[Y_AXIS][idx], floor_holes[X_AXIS][idx],  INK_BLACK | PAPER_CYAN, 'E');
       idx_j += 5; // eels are  4, 9, 14, 19
  }

  level_x_max = 28;
  level_x_min = 0;

  reset_misifu_position();
  misifu.state = SWIMMING;
  // loose breathe
  misifu.draw_additional = 100;

  misifu.x = 5;
  misifu.y = 5;
  anim_frames = 3;

  sp1_UpdateNow();

  // sprite changed
  sp1_DeleteSpr_fastcall(misifu.sp);
  misifu.sp = add_sprite_swim();
}

static void print_fishes(uint8_t clean) {
    for (idx = 0; idx != 8; ++idx) {
        if (clean == 1) {
            // used for simulating the animation with udg
            sp1_PrintAtInv( windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, ' ');
        } else if ( windows[idx].has_item == RIGHT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'F');
        } else if ( windows[idx].has_item == LEFT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'G');
        }
    }
}

static void print_eels(uint8_t color) {
    for(idx = 0; idx != 5; ++idx) {
       // row, col
       sp1_PrintAt( floor_holes[Y_AXIS][idx], floor_holes[X_AXIS][idx],  color | PAPER_CYAN, 'E');
  }
}

inline void fishes_on_move() {
    if(frame == 1) { // 1/4 of times
        print_fishes(1);
        // modify udgxs, udgxys todo direction

        for(idx = 0; idx != 8; ++idx) {
            // move to the right until reached limits
            if( windows[idx].has_item == RIGHT) {
                ++windows[idx].x;
            } else if( windows[idx].has_item == LEFT) {
                --windows[idx].x;
            }

            if(windows[idx].x >= 30) {
                windows[idx].has_item = LEFT;
            } else if(windows[idx].x < 1) {
                windows[idx].has_item = RIGHT;
            }


            // todo maybe move a bit up and down
        }
        print_fishes(0);
        print_eels(INK_WHITE);
    } else {
        print_eels(INK_BLACK);
    }


}

inline void map_to_fish_index() {
    // 3 5 7 9 11 13 15 19
    // 0 1 2 3  4  5  6 7
    if(misifu.y == 3) {
        return 0;
    } else if(misifu.y == 5) {
        return 1;
    } else if(misifu.y == 7) {
        return 2;
    } else if(misifu.y == 9) {
        return 3;
    } else if(misifu.y == 11) {
        return 4;
    } else if(misifu.y == 13) {
        return 5;
    } else if(misifu.y == 15) {
        return 6;
    } else if(misifu.y == 19) {
        return 7;
    }
    return UNDEF;
}

void level4_loop() {
    fishes_on_move();

    // misifu floats
    if(frame == 1 && misifu.y >= 1) {
        --misifu.draw_additional;

        if(misifu.draw_additional == 80) {
            zx_border(INK_BLUE);
        } else if(misifu.draw_additional == 40) {
            zx_border(INK_RED);
        } else if(misifu.draw_additional == 0) {
            // todo get out of level and loose a live
            zx_border(INK_GREEN);
        }
    } else if(misifu.y == 0) {
        // breathe
        misifu.draw_additional = 100;
        zx_border(INK_BLACK);
    }
}
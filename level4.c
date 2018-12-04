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
  for(idx = 0; idx != 8; ++idx) {
        udgxs[idx] = rand() % 28;
        udgys[idx] = rand() % 22;

        // fish up direction (ojo 0-5)
        floor_holes[FISHES_HORIZ_DIR][idx] = RIGHT;
        floor_holes[FISHES_VERT_DIR][idx] = UP;
         // row, col
        sp1_PrintAt( udgys[idx], udgxs[idx],  INK_BLACK | PAPER_CYAN, 'F');
  }

  // now eels
  for(idx = 0; idx != 5; ++idx) {
       // paint eels... if there's an overlap... bad luck
       floor_holes[0][idx] = rand() % 28;
       floor_holes[1][idx] = rand() % 22;
       // row, col
       sp1_PrintAt( floor_holes[1][idx], floor_holes[0][idx],  INK_BLACK | PAPER_CYAN, 'E');
  }

  level_x_max = 28;
  level_x_min = 0;

  reset_misifu_position();
  misifu.state = SWIMMING;

  misifu.x = 5;
  misifu.y = 5;
  anim_frames = 3;

  sp1_UpdateNow();
}

static void print_fishes(uint8_t clean) {
    for (idx = 0; idx != 8; ++idx) {
        if (clean == 1) {
            // used for simulating the animation with udg
            sp1_PrintAtInv( udgxs[idx], udgys[idx],  INK_BLACK | PAPER_CYAN, ' ');
        } else if (floor_holes[FISHES_HORIZ_DIR][idx] == RIGHT) {
            sp1_PrintAtInv( udgxs[idx], udgys[idx],  INK_BLACK | PAPER_CYAN, 'F');
        } else if (floor_holes[FISHES_HORIZ_DIR][idx] == LEFT) {
            sp1_PrintAtInv( udgxs[idx], udgys[idx],  INK_BLACK | PAPER_CYAN, 'G');
        }
    }
}

inline void fishes_on_move() {
    print_fishes(1);
    // modify udgxs, udgxys todo direction

    for(idx = 0; idx != 8; ++idx) {
        // move to the right until reached limits
        if(floor_holes[FISHES_HORIZ_DIR][idx] == RIGHT) {
            ++udgxs[idx];
        } else {
            --udgxs[idx];
        }

        if(udgxs[idx] >= 30) {
            floor_holes[FISHES_HORIZ_DIR][idx] = LEFT;
        } else if(udgxs[idx] < 1) {
            floor_holes[FISHES_HORIZ_DIR][idx] = RIGHT;
        }
        // move up and down
        /*if(anim_frames == 0) {
            if(floor_holes[idx][FISHES_VERT_DIR] == UP) {
                floor_holes[idx][FISHES_VERT_DIR] == DOWN;
                anim_frames = 3;
            } else {
                floor_holes[idx][FISHES_VERT_DIR] == UP;
                anim_frames = 3;
            }
        } else if(random_value > 200) {
            if(floor_holes[idx][FISHES_VERT_DIR] == UP) {
                --udgys[idx];
            } else {
                ++udgys[idx];
            }
            --anim_frames;
        }*/

        // todo should do up and down, left and right
    }

    print_fishes(0);

}

void level4_loop() {
    //fishes_on_move();
}
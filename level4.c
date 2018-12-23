#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"
#include "int.h"

const uint8_t udg_watertop[] = {0xff, 0xef, 0xc5, 0x80, 0x0, 0x0, 0x0, 0x0};
const uint8_t udg_fish[] = {0x0, 0x9c, 0xbe, 0xfd, 0xff, 0xbf, 0x9e, 0x0};
const uint8_t udg_fishL[] = {0x0, 0x39, 0x7d, 0xbf, 0xff, 0xfd, 0x79, 0x0};
const uint8_t udg_eel[] = {0x0, 0x0, 0x0, 0x48, 0x36, 0x1, 0x0, 0x0};


void  print_background_level4() {
  level = 4;
  eaten_items = 8;
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
        idx_j += 2; // fishes are 3, 5, 7, 9, 11, 13, 15, 17
  }

  // eels
  sp1_PrintAt(4, 3,  INK_BLACK | PAPER_CYAN, 'E');
  sp1_PrintAt(8, 24,  INK_BLACK | PAPER_CYAN, 'E');
  sp1_PrintAt(12, 12,  INK_BLACK | PAPER_CYAN, 'E');
  sp1_PrintAt(16, 5,  INK_BLACK | PAPER_CYAN, 'E');
  sp1_PrintAt(4, 12,  INK_BLACK | PAPER_CYAN, 'E');

  level_x_max = 28;
  level_x_min = 0;

  reset_misifu_position();
  misifu.state = SWIMMING;
  // loose breathe
  misifu.draw_additional = 30;

  misifu.x = 5;
  misifu.y = 5;
  anim_frames = 3;

  sp1_UpdateNow();

  // sprite changed
  sp1_DeleteSpr_fastcall(misifu.sp);
  misifu.sp = add_sprite_swim();
}

static void get_out_of_level4(uint8_t fall) {

    sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_BLACK,
                  ' ' );

    if(fall == FALLING) {
        --lives;
        repaint_lives = 1;

        for (idx = 0; idx != 5; ++idx) {
            bit_beepfx_di_fastcall(BEEPFX_HIT_4);

            if((idx & 1) == 0) {
                zx_border(INK_BLUE);
            } else {
                zx_border(INK_WHITE);
            }
            wait();
        }
    } else if(fall == OXYGEN) {
        --lives;
    }

    if(fall == FALLING) {
        bit_beepfx_di_fastcall(BEEPFX_AWW);
    } if(fall == OXYGEN) {
        bit_beepfx_di_fastcall(BEEPFX_GULP);
    } else {
        bit_beepfx_di_fastcall(BEEPFX_SELECT_5);
    }

    sp1_DeleteSpr_fastcall(misifu.sp);
    misifu.sp = add_sprite_protar1();

    print_background_lvl1();
}

static void print_fishes(uint8_t clean) {
    for (idx = 0; idx != 8; ++idx) {
        if (clean == 1 && windows[idx].has_item != 'Z') {
            // used for simulating the animation with udg
            sp1_PrintAtInv( windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, ' ');
        } else if ( windows[idx].has_item == RIGHT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'F');
        } else if ( windows[idx].has_item == LEFT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'G');
        }
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
    }


}

static inline uint8_t map_to_fish_index() {
    if(misifu.y == 2 || misifu.y == 3) {
        return 0;
    } else if(misifu.y == 4 || misifu.y == 5) {
        return 1;
    } else if(misifu.y == 6 || misifu.y == 7) {
        return 2;
    } else if(misifu.y == 8 || misifu.y == 9) {
        return 3;
    } else if(misifu.y == 10 || misifu.y == 11) {
        return 4;
    } else if(misifu.y == 12 || misifu.y == 13) {
        return 5;
    } else if(misifu.y == 14 || misifu.y == 15) {
        return 6;
    } else if(misifu.y == 17 || misifu.y == 18) {
        return 7;
    }

    return UNDEF;
}


void detect_fish_collission() {
    idx = map_to_fish_index();

    if(abs(windows[idx].x - misifu.x) < 2 && windows[idx].has_item != 'Z') {
        windows[idx].has_item = 'Z';  // eaten fish
        repaint_lives = 1;
        // delete collided fish
        sp1_PrintAtInv(windows[idx].y, windows[idx].x, INK_BLACK | PAPER_CYAN, ' ');
        windows[idx].x = 1;
        windows[idx].y = 23;
        sp1_PrintAtInv(windows[idx].y, windows[idx].x + eaten_items, INK_GREEN | PAPER_BLACK, 'F');
        points += 5;
        bit_beepfx_di_fastcall(BEEPFX_SCORE);
        --eaten_items;

        if(eaten_items == 0) {
            get_out_of_level4(NONE);
        }
    } else {
        if(
            (abs(3 - misifu.y) < 2 && (abs(3 - misifu.x) < 2 || abs(12 - misifu.x) < 2)) ||
            (abs(7 - misifu.y) < 2 && abs(24 - misifu.x) < 2) ||
            (abs(11 - misifu.y) < 2 && abs(12 - misifu.x) < 2) ||
            (abs(15 - misifu.y) < 2 && abs(5 - misifu.x) < 2)) {
            // loose a life and out of level
            get_out_of_level4(FALLING);
            return;
        }
    }
}

void level4_loop() {
    fishes_on_move();
    detect_fish_collission();

    if(frame == 1 && misifu.y >= 1) {
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
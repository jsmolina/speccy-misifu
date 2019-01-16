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
  sp1_Invalidate(&full_screen);


  sp1_TileEntry('W', udg_watertop);
  sp1_TileEntry('A', udg_fish);
  sp1_TileEntry('B', udg_fishL);
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
        sp1_PrintAt( windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'A');
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

static void print_fishes(uint8_t clean) {
    for (idx = 0; idx != 8; ++idx) {
        if (clean == 1 && windows[idx].has_item != 'Z') {
            // used for simulating the animation with udg
            sp1_PrintAtInv( windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, ' ');
        } else if ( windows[idx].has_item == RIGHT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'A');
        } else if ( windows[idx].has_item == LEFT) {
            sp1_PrintAtInv(  windows[idx].y, windows[idx].x,  INK_BLACK | PAPER_CYAN, 'B');
        }
    }
}

inline void fishes_on_move() {
    if(frame == 1) { // 1/4 of times
        print_fishes(1);
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

        }
        print_fishes(0);
    }


}

static inline uint8_t map_to_fish_index() {
    for(idx = 0; idx != 8; ++idx) {
        if(abs(misifu.y - windows[idx].y) < 2) {
            return idx;
        }
    }

    return UNDEF;
}

static uint8_t is_misifu_in_eel(uint8_t y, uint8_t x) {
    return (abs(y - misifu.y) < 2 && abs(x - misifu.x) < 2);
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
        sp1_PrintAtInv(windows[idx].y, windows[idx].x + eaten_items, INK_GREEN | PAPER_BLACK, 'A');
        points += 5;
        bit_beepfx_di_fastcall(BEEPFX_SCORE);
        --eaten_items;

        if(eaten_items == 0) {
            get_out_of_level4(WON_LEVEL);
        }
    } else {
        if(is_misifu_in_eel(3, 3)
        || is_misifu_in_eel(3, 12)
        || is_misifu_in_eel(7, 24)
        || is_misifu_in_eel(11, 12)
        || is_misifu_in_eel(15, 5))
        {
            // loose a life and out of level
            get_out_of_level4(ELECTRIFIED);
            loose_a_live();
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
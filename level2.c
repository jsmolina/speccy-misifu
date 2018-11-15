#ifndef _LEVEL2
#define _LEVEL2
#include <sound.h>
#include "level1.h"
// AKA RATS ROOM

#include "defines.h"

/**
Returns 1 if x,y are in window position
**/
uint8_t thrown_from_window(uint8_t x, uint8_t y) {
   return (x>7 && x < 10 && y > 21 && y < 26);
}

// Candidate to be shared


void define_cheese_holes_pos() {
    // init to zero
    windows[0].y = 20; windows[0].x = 4;
    windows[1].y = 20; windows[1].x = 18;
    windows[2].y = 20; windows[2].x = 14;
    windows[3].y = 19; windows[3].x = 8;
    windows[4].y = 19; windows[4].x = 5;
    windows[5].y = 18; windows[5].x = 9;
    windows[6].y = 18; windows[6].x = 13;
    windows[7].y = 16; windows[7].x = 4;
    windows[8].y = 14; windows[8].x = 4;
    windows[9].y = 14; windows[9].x = 9;
    windows[10].y = 14; windows[10].x = 12;
    windows[11].y = 12; windows[11].x = 6;
    windows[12].y = 10; windows[12].x = 4;
    windows[13].y = 8; windows[13].x = 4;
}


static inline uint8_t map_cat_pos_in_holes() {
    if(misifu.state != FALLING) {
        return UNDEF;
    }
    // note that udgs have a -2 margin
    if(misifu.y == 20) {
        if(misifu.x == 2) {
            return 0;
        } else if(misifu.x == 16) {
            return 1;
        } else if(misifu.x == 12) {
            return 2;
        }

    } else if(misifu.y == 19) {
        if(misifu.x == 6) {
            return 3;
        } else if(misifu.x == 3) {
            return 4;
        }
    } else if(misifu.y == 18) {
        if(misifu.x == 7) {
            return 5;
        } else if(misifu.x == 11) {
            return 6;
        }
    } else if(misifu.y == 16 && misifu.x == 2) {
        return 7;
    } else if(misifu.y == 14) {
        if(misifu.x == 2) {
            return 8;
        } else if(misifu.x == 7) {
            return 9;
        } else if(misifu.x == 10) {
            return 10;
        }
    } else if(misifu.y == 12 && misifu.x == 4) {
        return 11;
    } else if (misifu.y == 10 && misifu.x == 2) {
        return 12;
    } else if(misifu.y == 8 && misifu.x == 2) {
        return 13;
    }

    return UNDEF;
}

void get_out_of_level2(uint8_t fall) {

    sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_BLACK,
                  ' ' );

    // control wether if gets out of level by having eat all mouses
    sp1_Invalidate(&full_screen);
    level = 1;
    sp1_UpdateNow();
    print_background_lvl1();
}

void detect_fall_in_hole_or_curtain() {
    idx = map_cat_pos_in_holes();

    if(idx != UNDEF) {
        misifu.in_bin = idx;
        misifu.state = CAT_IN_ROPE;

        // if window has mouse
        if(windows[idx].has_item == 'B') {
            windows[idx].has_item = 'Z'; // mark as already eaten
            // print then the mouse in the up side
            repaint_lives = 1;
            sp1_PrintAtInv(1, 1 + eaten_items, INK_BLACK | PAPER_GREEN, 'B');
            points += 5;
            bit_beepfx_di(BEEPFX_SCORE);
            --eaten_items;
        }

    } else {
        zx_border(INK_BLACK);
    }


    if (eaten_items == 0) {
        get_out_of_level2(WON_LEVEL);
    }
}

void mousies_dance_and_eat() {
    if (random_value < 4 || repaint_lives == 1) {
        repaint_lives = 0;
        // mousie holes are connected, let's keep switching
        if (random_value > 2) {
            left = 'A';
            right = 'B';
        } else {
            left = 'B';
            right = 'A';
        }
        // only switch now if not eaten
        if(windows[5].has_item != 'Z' && windows[8].has_item != 'Z') {
            windows[5].has_item = left; windows[8].has_item = right;
        }

        if(windows[10].has_item != 'Z' && windows[4].has_item != 'Z') {
            windows[10].has_item = left; windows[4].has_item = right;
        }

        if(windows[13].has_item != 'Z' && windows[9].has_item != 'Z') {
            windows[13].has_item = left; windows[9].has_item = right;
        }

        if(windows[12].has_item != 'Z' && windows[6].has_item != 'Z') {
            windows[12].has_item = left; windows[6].has_item = right;
        }

        for(idx_j = 0; idx_j != 8; ++idx_j) {
            idx = udgxs[idx_j];
            sp1_PrintAtInv(windows[idx].y, windows[idx].x, INK_BLACK | PAPER_GREEN, windows[idx].has_item);
        }
    }
    // todo detect eat (set has_item as Z) to both holes
}

void  print_background_level2() {
  level = 2;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('C', cheese2);
  sp1_TileEntry('Z', hole_empty);

  // in this level it is used to define holes with mouse
  udgxs[0] = 5;
  udgxs[1] = 8;
  udgxs[2] = 10;
  udgxs[3] = 4;
  udgxs[4] = 13;
  udgxs[5] = 9;
  udgxs[6] = 12;
  udgxs[7] = 6;

  print_room_walls();

  aux_object.offset = AUX_BROOM;

  define_cheese_holes_pos();

  for (idx = 3; idx != 20; ++idx) {

    for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j, idx, PAPER_GREEN, 'C');
    }
  }
  // paint holes
  for (idx = 0; idx != 14; ++idx) {
    sp1_PrintAt( windows[idx].y, windows[idx].x, INK_BLACK | PAPER_GREEN, 'A');
  }
  reset_misifu_position();
  eaten_items = 4;
}



#endif

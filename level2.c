#ifndef _LEVEL2
#define _LEVEL2
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

void detect_fall_in_hole_or_curtain() {
    idx = map_cat_pos_in_holes();

    if(idx != UNDEF) {
        misifu.in_bin = idx;
        misifu.state = CAT_IN_ROPE;
        //zx_border(INK_GREEN);
    } else {
        zx_border(INK_BLACK);
    }
}

void mousies_dance_and_eat() {
    if (random_value < 4) {
        // mousie holes are connected, let's keep switching
        if (random_value > 2) {
            windows[5].has_item = 'A'; windows[8].has_item = 'B';
            windows[10].has_item = 'A'; windows[4].has_item = 'B';
            windows[13].has_item = 'A'; windows[9].has_item = 'B';
            windows[12].has_item = 'A'; windows[6].has_item = 'B';
        } else {
            windows[5].has_item = 'B'; windows[8].has_item = 'A';
            windows[10].has_item = 'B'; windows[4].has_item = 'A';
            windows[13].has_item = 'B'; windows[9].has_item = 'A';
            windows[12].has_item = 'B'; windows[6].has_item = 'A';
        }
        for(idx_j = 0; idx_j != 8; ++idx_j) {
            idx = udgxs[idx_j];
            sp1_PrintAtInv(windows[idx].y, windows[idx].x, INK_BLACK | PAPER_GREEN, windows[idx].has_item);
        }
    }
    // todo detect eat (set has_item as Z) to both holes
}


void print_room_walls() {
  // in this level it is used to define holes with mouse
  udgxs[0] = 5;
  udgxs[1] = 10;
  udgxs[2] = 13;
  udgxs[3] = 12;
  udgxs[4] = 8;
  udgxs[5] = 4;
  udgxs[6] = 9;
  udgxs[7] = 6;
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  sp1_TileEntry('J', curtain);
  sp1_TileEntry('N', udg_win2); // full square

  for(idx = 0; idx != 3; ++idx) {
    // upper left
    sp1_PrintAt( 3 + idx, idx,  INK_BLACK | PAPER_RED, 'H');
    // down left diagonal
    sp1_PrintAt( 20 - idx, idx, INK_BLACK | PAPER_RED, 'I');
    // upper right
    sp1_PrintAt( 5 - idx, 29 + idx,  INK_BLACK | PAPER_RED, 'I');
    // down right
    sp1_PrintAt( 18 + idx, 29 + idx,  INK_BLACK | PAPER_RED, 'H');
  }

  // draw vertical wall
  for (idx = 6; idx != 18; ++idx) {
    sp1_PrintAt( idx, 3, INK_BLACK | PAPER_RED, 'F');
    sp1_PrintAt( idx, 29,  INK_BLACK | PAPER_RED, 'F');
  }

  // draw horizontal wall
  for (idx = 3; idx != 29; ++idx) {
    sp1_PrintAt( 5, idx, INK_BLACK | PAPER_RED, 'G');
    sp1_PrintAt( 17, idx, INK_BLACK | PAPER_RED, 'G');
  }

  for (idx = 8; idx != 11; ++idx) {
    sp1_PrintAt( idx, 20, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( idx, 21, INK_RED | PAPER_GREEN, 'J');

    // x=8, 9 and y=22-25
    if (idx != 10) {
        sp1_PrintAt( idx, 22,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 23,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 24,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 25,  PAPER_BLACK, 'N');
    }

    sp1_PrintAt( idx, 26, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( idx, 27, INK_RED | PAPER_GREEN, 'J');
  }

  reset_misifu_position();
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

  print_room_walls();
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

}



#endif

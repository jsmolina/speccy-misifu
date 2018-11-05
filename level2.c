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
    for(idx_j = 0; idx_j != 5; ++idx_j) {
        for(idx = 0; idx != 24; ++idx) {
            floor_holes[idx_j][idx] = 0;
        }
    }
    /*
    windows[3].x = 20; windows[3].y = 18;
    windows[5].x = 20; windows[5].y = 14;
    windows[6].x = 18; windows[6].y = 13;
    windows[10].x = 14; windows[10].y = 12;
    windows[0].x = 18; windows[0].y = 9;
    windows[9].x = 14; windows[9].y = 8;
    windows[2].x = 19; windows[2].y = 8;
    windows[11].x = 12; windows[11].y = 6;
    windows[4].x = 19; windows[4].y = 5;
    windows[1].x = 20; windows[1].y = 4;
    windows[7].x = 16; windows[7].y = 4;
    windows[8].x = 14; windows[8].y = 4;
    windows[12].x = 10; windows[12].y = 4;
    windows[13].x = 8; windows[13].y = 4;
    */
    // y=4, x = 8
    floor_holes[0][8] = 1;
    floor_holes[0][10] = 1;
    floor_holes[0][14] = 1;
    floor_holes[0][16] = 1;
    floor_holes[0][20] = 1;
    // y = 5
    floor_holes[1][19] = 1;
    // y = 6
    floor_holes[2][12] = 1;
    // y = 8
    floor_holes[3][19] = 1;
    floor_holes[3][14] = 1;
    // y = 9
    floor_holes[4][18] = 1;

}


void detect_fall_in_hole_or_curtain() {
    // todo implement
    // misifu.state = CAT_IN_ROPE;
}


void print_room_walls() {
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

  print_room_walls();
  define_cheese_holes_pos();

  for (idx = 3; idx != 20; ++idx) {

    for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j, idx, PAPER_GREEN, 'C');
    }
  }
  // paint holes
  /*for (idx = 0; idx != 14; ++idx) {
    sp1_PrintAt( windows[idx].x, windows[idx].y, INK_BLACK | PAPER_GREEN, 'A');
  }*/
  // todo paint cheese here

}



#endif

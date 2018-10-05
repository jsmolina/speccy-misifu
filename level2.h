#ifndef _LEVEL2
#define _LEVEL2
// AKA RATS ROOM

#include <defines.h>

/**
Returns 1 if x,y are in window position
**/
uint8_t thrown_from_window(uint8_t x, uint8_t y) {
   return (x>7 && x < 10 && y > 21 && y < 26);
}

// Candidate to be shared


void define_cheese_holes_pos() {
    windows[0].x = 18; windows[0].y = 9;
    windows[1].x = 20; windows[1].y = 4;
    windows[2].x = 19; windows[2].y = 8;
    windows[3].x = 20; windows[3].y = 18;
    windows[4].x = 19; windows[4].y = 5;
    windows[5].x = 20; windows[5].y = 14;
    windows[6].x = 18; windows[6].y = 13;
    windows[7].x = 16; windows[7].y = 4;
    windows[8].x = 14; windows[8].y = 4;
    windows[9].x = 14; windows[9].y = 8;
    windows[10].x = 14; windows[10].y = 12;
    windows[11].x = 12; windows[11].y = 6;
    windows[12].x = 10; windows[12].y = 4;
    windows[13].x = 8; windows[13].y = 4;
}


void print_room_walls() {
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  sp1_TileEntry('J', curtain);
  sp1_TileEntry('N', udg_win2); // full square

  for(index = 0; index != 3; ++index) {
    // upper left
    sp1_PrintAt( 3 + index, index, INK_RED | PAPER_BLACK, 'H');
    // down left diagonal
    sp1_PrintAt( 20 - index, index, INK_RED | PAPER_BLACK, 'I');
    // upper right
    sp1_PrintAt( 5 - index, 29 + index, INK_RED | PAPER_BLACK, 'I');
    // down right
    sp1_PrintAt( 18 + index, 29 + index, INK_RED | PAPER_BLACK, 'H');
  }

  // draw vertical wall
  for (index = 6; index != 18; ++index) {
    sp1_PrintAt( index, 3, INK_RED | PAPER_BLACK, 'F');
    sp1_PrintAt( index, 29, INK_RED | PAPER_BLACK, 'F');
  }

  // draw horizontal wall
  for (index = 3; index != 29; ++index) {
    sp1_PrintAt( 5, index, INK_RED | PAPER_BLACK, 'G');
    sp1_PrintAt( 17, index, INK_RED | PAPER_BLACK, 'G');
  }

  for (index = 8; index != 11; ++index) {
    sp1_PrintAt( index, 20, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( index, 21, INK_RED | PAPER_GREEN, 'J');

    // x=8, 9 and y=22-25
    if (index != 10) {
        sp1_PrintAt( index, 22, INK_RED | PAPER_BLACK, 'N');
        sp1_PrintAt( index, 23, INK_RED | PAPER_BLACK, 'N');
        sp1_PrintAt( index, 24, INK_RED | PAPER_BLACK, 'N');
        sp1_PrintAt( index, 25, INK_RED | PAPER_BLACK, 'N');
    }

    sp1_PrintAt( index, 26, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( index, 27, INK_RED | PAPER_GREEN, 'J');
  }
}

void  print_background_level2() {
  uint8_t j;


  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED,
                  ' ' );

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('C', cheese2);

  print_room_walls();
  define_cheese_holes_pos();

  for (index = 3; index != 20; ++index) {

    for (j = index + 1; j != 21; ++j) {
        sp1_PrintAt( j, index, PAPER_GREEN, 'C');
    }
  }
  // paint holes
  for (index = 0; index != 14; ++index) {
    sp1_PrintAt( windows[index].x, windows[index].y, INK_GREEN | PAPER_BLACK, 'A');
  }
  // todo paint cheese here

}




#endif

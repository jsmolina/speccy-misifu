#include "level3.h"
#include "defines.h"

void paint_cupid(uint8_t row, uint8_t col) {
    sp1_PrintAt( row, col, INK_RED | PAPER_GREEN, 'C');
    sp1_PrintAt( row, col + 1, INK_RED | PAPER_GREEN, 'D');
    sp1_PrintAt( row, col + 2, INK_RED | PAPER_GREEN, 'E');

    sp1_PrintAt( row + 1, col, INK_RED | PAPER_GREEN, 'F');
    sp1_PrintAt( row + 1, col + 1, INK_RED | PAPER_GREEN, 'G');
    sp1_PrintAt( row + 1, col + 2, INK_RED | PAPER_GREEN, 'H');

    sp1_PrintAt( row + 2, col, INK_RED | PAPER_GREEN, 'I');
    sp1_PrintAt( row + 2, col + 1, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( row + 2, col + 2, INK_RED | PAPER_GREEN, 'K');
}

void  print_background_level3() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_RED | PAPER_GREEN,
                  ' ' );

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', heart1);
  sp1_TileEntry('B', heart2);

  sp1_TileEntry('C', cupid11);
  sp1_TileEntry('D', cupid12);
  sp1_TileEntry('E', cupid13);

  sp1_TileEntry('F', cupid21);
  sp1_TileEntry('G', cupid22);
  sp1_TileEntry('H', cupid23);

  sp1_TileEntry('I', cupid31);
  sp1_TileEntry('J', cupid32);
  sp1_TileEntry('K', cupid33);

  // vertical cupids
  for(idx=0; idx < 23; idx=idx+3) {
     paint_cupid(idx, 0);
     paint_cupid(idx, 29);
  }

  for(idx_j=3; idx_j < 27; idx_j=idx_j+3) {
    paint_cupid(0, idx_j);
  }

    sp1_PrintAt( 23, 6, INK_RED | PAPER_GREEN, 'B');

  for(idx=23; idx > 3; idx = idx - 4) {
     for (idx_j=4; idx_j != 28; ++idx_j ) {
        sp1_PrintAt( idx, idx_j, INK_RED | PAPER_GREEN, 'B');
     }
  }

  misifu.x = 4;
  misifu.y = FLOOR_Y;
}


void detect_fall_in_hearts() {
    // heart levels are in 19, 15, 11, 7
    if (misifu.state == FALLING) {
        if(misifu.y == 17) {
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE;
            misifu.offset = BORED;
        } else if(misifu.y == 13) {
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE1;
            misifu.offset = BORED;
        } else if(misifu.y == 9) {
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE2;
            misifu.offset = BORED;
        } else if(misifu.y == 5) {
            misifu.state = CAT_ON_HIGH;
            misifu.draw_additional = CAT_IN_ROPE3;
            misifu.offset = BORED;
        }
    }
}

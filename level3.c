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
  // frame = floor
  frame = 4;

  for(idx=23; idx > 3; idx = idx - 4) {
    x = idx_j - 4;

     for (idx_j=4; idx_j != 28; ++idx_j ) {
        floor_holes[frame][idx_j - 4] = floor_holes_defaults[frame][idx_j - 4];
        if (floor_holes[frame][idx_j - 4] == 1) {
            sp1_PrintAt( idx, idx_j, INK_RED | PAPER_GREEN, 'B');
        } else {
            sp1_PrintAt( idx, idx_j, INK_BLUE | PAPER_GREEN, 'A');
        }
     }
     --frame;
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

void throw_cupid_arrow() {
    // arrow should remove tiles (and redraw them)
    // if arrow object is hidden, decide to throw it or not
    if (aux_object.x == 33 && random_value < 33 && (random_value & 1) == 0) {
        aux_object.x = random_value;
        aux_object.y = 0;

        if(aux_object.x > 16) {
            horizontal_direction = LEFT;
        } else {
            horizontal_direction = RIGHT;
        }
    }

    if (aux_object.y < 25) {
        ++aux_object.y;
        if (horizontal_direction == RIGHT) {
            ++aux_object.x;
            aux_object.offset = LEFTC1;

        } else {
            --aux_object.x;
            aux_object.offset = LEFTC2;

        }

        // hearts y are 23, 19, 15, 11, 7
        if(aux_object.y == 23) {
            idx_j = 4;
        } else if(aux_object.y == 19) {
            idx_j = 3;
        } else if(aux_object.y == 15) {
            idx_j = 2;
        } else if(aux_object.y == 11) {
            idx_j = 1;
        } else if (aux_object.y == 7) {
            idx_j = 0;
        } else {
            idx_j = UNDEF;
        }

        if(idx_j < 5 && aux_object.x > 3 && aux_object.x < 27) {
            // broke the heart :(
            sp1_PrintAtInv( aux_object.y, aux_object.x,  INK_BLUE | PAPER_GREEN, 'A');
            // todo reset these values floor_holes to ones at the paint of the level to defaults
            floor_holes[idx_j][aux_object.x] = 0;
        }

        // todo detect collision with 'red' hearts
    } else {
        // out of screen
        aux_object.x = 33;
    }
    sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, aux_object.x, 0, 0);
}
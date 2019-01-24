#include "level3.h"
#include "defines.h"
#include "level1.h"
#include "int.h"
#include <stdlib.h>
#include <sound.h> // for bit_beepfx()

// level 3 hearts
const uint8_t heart1[] = {0x0, 0x66, 0xef, 0xc7, 0xf3, 0x3a, 0x0, 0x0};
const uint8_t heart2[] = {0x66, 0xef, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0};
const uint8_t cupid11[] = {0x0, 0x0, 0x0, 0xe, 0xf, 0x1f, 0x3f, 0x7f};
const uint8_t cupid12[] = {0x0, 0x0, 0x0, 0x7, 0x1f, 0xdf, 0xff, 0xff};
const uint8_t cupid13[] = {0x0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0x80, 0xd0};
const uint8_t cupid21[] = {0x7f, 0x7f, 0x7e, 0x38, 0x1, 0x1, 0x1, 0x33};
const uint8_t cupid22[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc};
const uint8_t cupid23[] = {0xd8, 0x9c, 0x8e, 0xee, 0xfe, 0xe6, 0x76, 0x1e};
const uint8_t cupid31[] = {0x3f, 0x6e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t cupid32[] = {0x78, 0x60, 0x60, 0xe0, 0xe0, 0x0, 0x0, 0x0};
const uint8_t cupid33[] = {0x7e, 0xf8, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0};


// use tiles
const uint8_t catheaven1[] = {0x60, 0xc3, 0xc7, 0xef, 0x7e, 0x1e, 0x18, 0x1c};
const uint8_t catheaven2[] = {0x4, 0xcc, 0xea, 0xff, 0x7e, 0x1c, 0xc, 0xe};



static void paint_cupid(uint8_t row, uint8_t col) {
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


void print_background_level_last() {
  level = 10;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_RED | PAPER_GREEN,
                  ' ' );
  zx_border(INK_BLACK);

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

  sp1_TileEntry('L', catheaven1);
  sp1_TileEntry('M', catheaven2);

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
        random_value = rand();
        if(frame == 4 || (random_value & 1) == 0 ) {
            floor_holes[frame][idx_j - 4] = 1;
            sp1_PrintAt( idx, idx_j, INK_RED | PAPER_GREEN, 'B');
        } else {
            floor_holes[frame][idx_j - 4] = 0;
            sp1_PrintAt( idx, idx_j, INK_BLUE | PAPER_GREEN, 'A');
        }

     }
     --frame;
  }

  misifu.x = 4;
  misifu.y = FLOOR_Y;
  udgxs[0] = udgxs[1] = udgxs[2] = udgxs[3] = 5;
  level_x_max = 25;
  level_x_min = 3;
  sp1_UpdateNow();
}


/**
 hearts y are 23, 19, 15, 11, 7
**/
static inline uint8_t lvl3_y_to_idj(uint8_t y) {

    if(y == 5) {
        return 0;
    } else if(y == 9) {
        return 1;
    } else if(y == 13) {
        return 2;
    } else if(y == 17) {
        return 3;
    } else if (y == FLOOR_Y) {
        return 4;
    } else {
        return UNDEF;
    }
}


void detect_fall_in_hearts() {
    idx_j = lvl3_y_to_idj(misifu.y);
    if (idx_j == UNDEF) {
        return;
    }

    idx = misifu.x - 1;
    // todo this is not always working, maybe related to painting?
    if (floor_holes[idx_j][idx] == 0) {
        misifu.state = FALLING;
        if (misifu.y >= FLOOR_Y) {
            get_out_of_level_generic(FALLING);
            return;
        }
    } else if (floor_holes[idx_j][idx] == 1 && misifu.state == FALLING) {
        if(idx_j == 0) {
            get_out_of_level_generic(LEVELFINISHED); // yayyy
            return;
        }
        zx_border(INK_BLACK);
        misifu.state = CAT_ON_HIGH;
        misifu.draw_additional = CAT_IN_ROPE;
        misifu.offset = BORED;
    }
}


static void print_heavencats(uint8_t clean) {
    idx_j = 6;
    for (idx = 0; idx != 4; ++idx) {
        if (clean == 1) {
            // used for simulating the animation with udg
            sp1_PrintAtInv( idx_j, udgxs[idx],  PAPER_GREEN, ' ');
            sp1_PrintAtInv( idx_j, udgxs[idx] + 1,  PAPER_GREEN, ' ');
        } else {
            sp1_PrintAtInv( idx_j, udgxs[idx],  INK_BLACK | PAPER_GREEN, 'L');
            sp1_PrintAtInv( idx_j, udgxs[idx] + 1,  INK_BLACK  | PAPER_GREEN, 'M');
        }
        idx_j += 4;
    }
}


inline void heavencat_on_move() {
    // clean
    print_heavencats(1);

    if(frame == 3) {
        idx_j = random_value % 4;
        ++udgxs[idx_j];
        if(udgxs[idx_j] > 25) {
            // if reaching right, return left
            udgxs[idx_j] = 5;
        }
    }

    // repaint
    print_heavencats(0);

    // detect collision with misifu
    idx_j = lvl3_y_to_idj(misifu.y);
    if(idx_j != UNDEF && abs(misifu.x - udgxs[idx_j]) < 2) {
        misifu.state = FALLING;
        bit_beepfx_di_fastcall(BEEPFX_HIT_1);
    }

    // saves lot of memory to use udg in this animation
}

void throw_cupid_arrow() {
    // arrow should remove tiles (and redraw them)
    // if arrow object is hidden, decide to throw it or not
    if (aux_object.x == 33 && random_value < 33 && (random_value & 1) == 0) {
        aux_object.x = random_value;
        aux_object.y = 0;

        if(aux_object.x > 16) {
            horizontal_direction = LEFT;
            aux_object.offset = AUX_ARROWLEFT;
        } else {
            horizontal_direction = RIGHT;
            aux_object.offset = AUX_ARROWRIGHT;
        }
    }

    if (aux_object.y < 25) {
        ++aux_object.y;
        if (horizontal_direction == RIGHT) {
            ++aux_object.x;
        } else {
            --aux_object.x;

        }

        // hearts y are 23, 19, 15, 11, 7
        idx_j = lvl3_y_to_idj(aux_object.y - 2);

        if(idx_j < 5 && aux_object.x > 3 && aux_object.x < 27) {
            // broke the heart :(
            sp1_PrintAtInv( aux_object.y, aux_object.x, INK_BLUE | PAPER_GREEN, 'A');
            // todo +1 or -1?
            floor_holes[idx_j][aux_object.x + 1] = 0;
        }
    } else {
        // out of screen
        aux_object.x = 33;
    }
    sp1_MoveSprAbs(aux_object.sp, &full_screen,(void*) aux_object.offset, aux_object.y, aux_object.x, 0, 0);

    heavencat_on_move();
}

#include "level3.h"
#include "defines.h"
#include "level1.h"
#include "int.h"
#include <stdlib.h>
#include <sound.h> // for bit_beepfx()

#define RED_GREEN_BRIGHT INK_RED | PAPER_GREEN | BRIGHT


#define UDG_HEART1 128
#define UDG_HEART2 129
#define UDG_CUPID11 130
#define UDG_CUPID12 131
#define UDG_CUPID13 132
#define UDG_CUPID21 133
#define UDG_CUPID22 134
#define UDG_CUPID23 135
#define UDG_CUPID31 136
#define UDG_CUPID32 137
#define UDG_CUPID33 138
#define UDG_CATHEAVEN1 139
#define UDG_CATHEAVEN2 140

#define LAST_TILES_LEN  13
#define LAST_TILES_BASE  128

const uint8_t last[] = {
    0x00, 0x66, 0xef, 0xc7, 0xf3, 0x3a, 0x00, 0x00, // y:0, x:0 (128)
    0x66, 0xef, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00, // y:0, x:1 (129)
    0x00, 0x00, 0x00, 0x0e, 0x0f, 0x1f, 0x3f, 0x7f, // y:0, x:2 (130)
    0x00, 0x00, 0x00, 0x07, 0x1f, 0xdf, 0xff, 0xff, // y:0, x:3 (131)
    0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 0xd0, // y:0, x:4 (132)
    0x7f, 0x7f, 0x7e, 0x38, 0x01, 0x01, 0x01, 0x33, // y:0, x:5 (133)
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, // y:0, x:6 (134)
    0xd8, 0x9c, 0x8e, 0xee, 0xfe, 0xe6, 0x76, 0x1e, // y:0, x:7 (135)
    0x3f, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // y:0, x:8 (136)
    0x78, 0x60, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, // y:0, x:9 (137)
    0x7e, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, // y:0, x:10 (138)
    0x60, 0xc3, 0xc7, 0xef, 0x7e, 0x1e, 0x18, 0x1c, // y:0, x:11 (139)
    0x04, 0xcc, 0xea, 0xff, 0x7e, 0x1c, 0x0c, 0x0e, // y:0, x:12 (140)
};


static void paint_cupid(uint8_t row, uint8_t col) {
    sp1_PrintAt( row, col, RED_GREEN_BRIGHT, UDG_CUPID11);
    sp1_PrintAt( row, col + 1, RED_GREEN_BRIGHT, UDG_CUPID12);
    sp1_PrintAt( row, col + 2, RED_GREEN_BRIGHT, UDG_CUPID13);

    sp1_PrintAt( row + 1, col, RED_GREEN_BRIGHT, UDG_CUPID21);
    sp1_PrintAt( row + 1, col + 1, RED_GREEN_BRIGHT, UDG_CUPID22);
    sp1_PrintAt( row + 1, col + 2, RED_GREEN_BRIGHT, UDG_CUPID23);

    sp1_PrintAt( row + 2, col, RED_GREEN_BRIGHT, UDG_CUPID31);
    sp1_PrintAt( row + 2, col + 1, RED_GREEN_BRIGHT, UDG_CUPID32);
    sp1_PrintAt( row + 2, col + 2, RED_GREEN_BRIGHT, UDG_CUPID33);
}

static void assign_holes() {
    if(frame == 4 || (random_value & 1) == 0 ) {
        // as it has 24 X positions
        floor_holes[frame][idx_j - 4] = 1;
        sp1_PrintAt( idx, idx_j, RED_GREEN_BRIGHT, UDG_HEART2);
    } else {
        floor_holes[frame][idx_j - 4] = 0;
        sp1_PrintAt( idx, idx_j, INK_BLUE | PAPER_GREEN | BRIGHT, UDG_HEART1);
    }
}

void print_background_level_last() {
  level = 10;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_GREEN | BRIGHT,
                  ' ' );
  zx_border(INK_BLACK);

  sp1_Invalidate(&full_screen);

  uint8_t *pt = last;

  for (idx = 0; idx < LAST_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LAST_TILES_BASE + idx, pt);
  }
  
  // vertical cupids
  for(idx=0; idx < 23; idx=idx+3) {
     paint_cupid(idx, 0);
     paint_cupid(idx, 29);
  }

  for(idx_j=3; idx_j < 27; idx_j=idx_j+3) {
    paint_cupid(0, idx_j);
  }

  frame = 6;
  for(idx_j = 0; idx_j != 4; ++idx_j) {
      windows[idx_j].x = (rand() % 19) + 5;
      windows[idx_j].y = frame;
      frame += 4;
  }

    sp1_PrintAt( 23, 6, RED_GREEN_BRIGHT, UDG_HEART2);
  // frame = floor
  frame = 4;

  for(idx=23; idx != 3; idx = idx - 4) {

     for (idx_j=4; idx_j != 28; ++idx_j) {
        random_value = rand();
        assign_holes();
        ++idx_j;
        assign_holes();

     }
     --frame;
  }

  misifu.x = 4;
  misifu.y = FLOOR_Y;
  level_x_max = 25;
  level_x_min = 4;
  aux_object.offset = AUX_ARROWLEFT;
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
    /***
    floor holes start at 0 to save memory, thus position -4 is position zero really (fck memory)
    012345678
    ----xxxff
    ***/
    idx = misifu.x - 3;
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
        misifu.state = CAT_ON_HIGH;
        misifu.draw_additional = CAT_IN_ROPE;
        misifu.offset = BORED;
    }
}

static inline uint8_t rand_cat_to_move() {
    if(random_value < 50) {
        return 0;
    } else if(random_value < 100) {
        return 1;
    } else if(random_value < 150) {
        return 2;
    } else  {
        return 3;
    }
}

static void print_heavencat(uint8_t to_print1, uint8_t to_print2) {
    sp1_PrintAtInv( windows[idx_j].y, windows[idx_j].x, PAPER_GREEN | BRIGHT, to_print1);
    sp1_PrintAtInv( windows[idx_j].y, windows[idx_j].x + 1, PAPER_GREEN | BRIGHT, to_print2);
}

void throw_cupid_arrow() {
    // arrow should remove tiles (and redraw them)
    // if arrow object is hidden, decide to throw it or not
    if (aux_object.x == 33 && random_value > 2 && random_value < 27 && (tick & 1) == 0) {
        aux_object.x = random_value;
        aux_object.y = 0;

        if(aux_object.x > 16) {
            aux_object.offset = AUX_ARROWLEFT;
        } else {
            aux_object.offset = AUX_ARROWRIGHT;
        }
    }

    if (aux_object.y < 25) {
        ++aux_object.y;
        if((random_value & 1) == 0) {
            if (aux_object.offset == AUX_ARROWRIGHT) {
                ++aux_object.x;
            } else {
                --aux_object.x;
            }
        }

        // hearts y are 23, 19, 15, 11, 7
        idx_j = lvl3_y_to_idj(aux_object.y - 2);

        if(idx_j < 5 && aux_object.x > 3 && aux_object.x < 27) {
            // broke the heart :(
            idx = aux_object.x;
            floor_holes[idx_j][idx - 4] = 0;
            sp1_PrintAtInv( aux_object.y, idx, INK_BLACK | PAPER_GREEN | BRIGHT, UDG_HEART1);
        }
    } else {
        // out of screen
        aux_object.x = 33;
    }
    sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, aux_object.x, 0, 0);

    if(abs(misifu.x - aux_object.x) < 2 && abs(misifu.y - aux_object.y) < 2) {
        misifu.state = FALLING;
    }

    //heavencat_on_move()
    idx_j = rand_cat_to_move();
    if(idx_j != UNDEF) {
        print_heavencat(' ', ' ');
        ++windows[idx_j].x;
        if(windows[idx_j].x > 25) {
            // if reaching right, return left
            windows[idx_j].x = 5;
        }
        print_heavencat(UDG_CATHEAVEN1, UDG_CATHEAVEN2);
    }

    // detect collision with misifu
    idx_j = lvl3_y_to_idj(misifu.y);
    if(idx_j < 4 && abs(misifu.x - windows[idx_j].x) < 2) {
        misifu.state = FALLING;
        bit_beepfx_di_fastcall(BEEPFX_HIT_1);
    }
}

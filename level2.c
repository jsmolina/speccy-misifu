#ifndef _LEVEL2
#define _LEVEL2
#include <sound.h>
#include <stdlib.h>
#include "level1.h"
#include <input.h>
// AKA RATS ROOM

#include "defines.h"

// level 2 cheese
const uint8_t hole_empty[] = {0x3c, 0x46, 0x9f, 0xbf, 0xbf, 0xbf, 0x5e, 0x3c};
const uint8_t hole_mouse[] = {0x3c, 0x7e, 0x99, 0x81, 0xd5, 0xc3, 0x66, 0x3c};
const uint8_t cheese2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


void define_cheese_holes_pos() {
    // init to zero
    idx = 0;
    assign_window_pos(19, 4);
    assign_window_pos(19, 18);
    assign_window_pos(19, 14);
    assign_window_pos(18, 8);
    assign_window_pos(18, 5);
    assign_window_pos(17, 9);
    assign_window_pos(17, 13);
    assign_window_pos(15, 4);
    assign_window_pos(13, 4);
    assign_window_pos(13, 9);
    assign_window_pos(13, 12);
    assign_window_pos(11, 6);
    assign_window_pos(9, 4);
    assign_window_pos(7, 4);
}


static inline uint8_t map_cat_pos_in_holes() {

    for(idx = 0; idx != 14; ++idx) {
        if(misifu.y == windows[idx].y && misifu.x == (windows[idx].x - 1)) {
            return idx;
        }
    }

    return UNDEF;
}


void detect_fall_in_hole_or_curtain() {
    idx = map_cat_pos_in_holes();

    if(idx != UNDEF) {
        misifu.state = CAT_IN_ROPE;

        // if window has mouse
        if(windows[idx].has_item == 'B') {
            windows[idx].has_item = 'Z'; // mark as already eaten
            // print then the mouse in the up side
            repaint_lives = 1;
            sp1_PrintAtInv(1, 1 + eaten_items, INK_BLACK | PAPER_GREEN, 'B');
            bit_beepfx_di_fastcall(BEEPFX_SCORE);
            --eaten_items;
        }

    }

    detect_cat_in_window(0);

    if (eaten_items == 0) {
        get_out_of_level_generic(WON_LEVEL);
    }
}


static void move_misifu(uint8_t index) {
    first_keypress = index;
    misifu.x = windows[index].x - 1;
    misifu.y = windows[index].y - 1;
    misifu.state = FALLING;
}

void level2_loop() {
    // dance mousies, dance!
    if (random_value < 4 || repaint_lives == 1) {
        repaint_lives = 0;
        // mousie holes are connected, let's keep switching
        if (random_value > 2) {
            idx = 'A';
            idx_j = 'B';
        } else {
            idx = 'B';
            idx_j = 'A';
        }
        // only switch now if not eaten
        if(windows[5].has_item != 'Z' && windows[8].has_item != 'Z') {
            windows[5].has_item = idx; windows[8].has_item = idx_j;
        }

        if(windows[10].has_item != 'Z' && windows[4].has_item != 'Z') {
            windows[10].has_item = idx; windows[4].has_item = idx_j;
        }

        if(windows[13].has_item != 'Z' && windows[9].has_item != 'Z') {
            windows[13].has_item = idx; windows[9].has_item = idx_j;
        }

        if(windows[12].has_item != 'Z' && windows[6].has_item != 'Z') {
            windows[12].has_item = idx; windows[6].has_item = idx_j;
        }

        for(idx_j = 0; idx_j != 8; ++idx_j) {
            idx = udgxs[idx_j];
            sp1_PrintAtInv(windows[idx].y, windows[idx].x, INK_BLACK | PAPER_GREEN, windows[idx].has_item);
        }
    }

    if ((in & IN_STICK_FIRE) && first_keypress == 0) {
        idx = map_cat_pos_in_holes();
        if(idx == 5) {
            move_misifu(8);
        } else if(idx == 8) {
            move_misifu(5);
        } else if(idx == 10) {
            move_misifu(4);
        } else if(idx == 4) {
            move_misifu(10);
        } else if(idx == 13) {
            move_misifu(9);
        } else if(idx == 9) {
            move_misifu(13);
        } else if(idx == 12) {
            move_misifu(6);
        } else if(idx == 6) {
            move_misifu(12);
        }
    }

    if(!(in & IN_STICK_FIRE)) {
        first_keypress = 0;
    }

    move_broom();
    dog_checks();
}

void  print_background_level2() {
  level = 2;
  first_keypress = 0;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED,
                  ' ' );
  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('C', cheese2);
  sp1_TileEntry('Z', hole_empty);
  sp1_TileEntry('D', queso_textura);
  sp1_TileEntry('E', queso_diagonal);

  define_silla_udgs();

  // in this level it is used to define holes with mouse
  udgxs[0] = 5;
  udgxs[1] = 8;
  udgxs[2] = 10;
  udgxs[3] = 4;
  udgxs[4] = 13;
  udgxs[5] = 9;
  udgxs[6] = 12;
  udgxs[7] = 6;

  print_room_walls(20, PAPER_RED, INK_GREEN);

  define_cheese_holes_pos();

  for (idx = 3; idx != 20; ++idx) {

    for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j - 1, idx, PAPER_GREEN, 'C');
    }
  }

  // paint diagonal
  idx = 3;
  for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
      sp1_PrintAt( idx_j - 1, idx, PAPER_RED | INK_GREEN, 'E');
       ++idx;
  }


  // paint holes
  for (idx = 0; idx != 14; ++idx) {
    sp1_PrintAt( windows[idx].y, windows[idx].x, INK_BLACK | PAPER_GREEN, 'A');
    sp1_PrintAt( windows[idx].y, windows[idx].x - 1, INK_BLACK | PAPER_GREEN, 'D');
  }

  // paint the chair
  paint_chair(17, 22, PAPER_RED, INK_GREEN);
  paint_table(17, 26, PAPER_RED, INK_GREEN);

  eaten_items = 4;

  aux_object.y = 5;
  aux_object.x = 5;
  repaint_lives = 1;
  level_x_max = 28;
  level_x_min = 1;
  reset_misifu_position();
}


#endif

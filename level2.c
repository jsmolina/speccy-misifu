#ifndef _LEVEL2
#define _LEVEL2
#include <sound.h>
#include <stdlib.h>
#include "level1.h"
#include <input.h>
// AKA RATS ROOM
#include "defines.h"
#define TOTAL_COORDS_HOLES 12


const uint8_t coords_queso [] = {0x2f, 0x4f, 0xff, 0x14, 0x42, 0xff,
                                0x25, 0x63, 0x4f, 0x5f, 0x84, 0x33,
                                0x27, 0xdf, 0x53};
const uint8_t coords_holes [] = {0x01, 0xaa,
                                0x21, 0x61,
                                0x81, 0xb2,
                                0x66, 0xa6,
                                0x43, 0x69, 0xb2, 0xb5};
// level 2 cheese
const uint8_t hole_empty[] = {0x3c, 0x46, 0x9f, 0xbf, 0xbf, 0xbf, 0x5e, 0x3c};
const uint8_t hole_mouse[] = {0x3c, 0x7e, 0x99, 0x81, 0xd5, 0xc3, 0x66, 0x3c};



static inline uint8_t map_cat_pos_in_holes() {

    for(idx = 0; idx != 14; ++idx) {
        if(misifu.y == windows[idx].y && misifu.x == (windows[idx].x - 1)) {
            return idx;
        }
    }

    return UNDEF;
}


void detect_fall_in_hole_or_curtain() {

    if(idx != UNDEF) {
        misifu.state = CAT_IN_ROPE;

        // if window has mouse
        if(windows[idx].has_item == 'B') {
            windows[idx].has_item = 'Z'; // mark as already eaten
            // print then the mouse in the up side
            repaint_lives = 1;
            sp1_PrintAtInv(1, 1 + eaten_items, BACKGROUND_GREEN, 'B');
            bit_beepfx_di_fastcall(BEEPFX_SCORE);
            --eaten_items;
        }

    }

    detect_cat_in_window(0);

    if (eaten_items == 0) {
        get_out_of_level_generic(WON_LEVEL);
    }
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
            idx = floor_holes[0][idx_j];
            sp1_PrintAtInv(windows[idx].y, windows[idx].x, BACKGROUND_GREEN, windows[idx].has_item);
        }
    }

    idx = map_cat_pos_in_holes();

    if (misifu.state == FALLING) {
        detect_fall_in_hole_or_curtain();
    }

    if ((in & IN_STICK_FIRE) && first_keypress == 0) {
        if(idx == 5) {
            first_keypress = 8;
        } else if(idx == 8) {
            first_keypress = 5;
        } else if(idx == 10) {
            first_keypress = 4;
        } else if(idx == 4) {
            first_keypress = 10;
        } else if(idx == 13) {
            first_keypress = 9;
        } else if(idx == 9) {
            first_keypress = 13;
        } else if(idx == 12) {
            first_keypress = 6;
        } else if(idx == 6) {
            first_keypress = 12;
        }
        if(first_keypress != 0) {
            misifu.x = windows[first_keypress].x - 1;
            misifu.y = windows[first_keypress].y - 1;
            misifu.state = FALLING;
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
                  INK_BLACK | PAPER_RED | BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);

  uint8_t *queso_text = tiles_lvl1 + 8; // cheese text is at second row of level 1 tiles

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('Z', hole_empty);
  sp1_TileEntry('D', queso_text);
  sp1_TileEntry('E', queso_diagonal);

  // in this level it is used to define holes with mouse
  floor_holes[0][0] = 5;
  floor_holes[0][1] = 8;
  floor_holes[0][2] = 10;
  floor_holes[0][3] = 4;
  floor_holes[0][4] = 13;
  floor_holes[0][5] = 9;
  floor_holes[0][6] = 12;
  floor_holes[0][7] = 6;

  print_room_walls(20, PAPER_RED, INK_GREEN);

  //define_cheese_holes_pos();
  idx = 0;
  // 0
  assign_window_pos(19, 4);
  // 1
  assign_window_pos(19, 18);
  // 2
  assign_window_pos(19, 14);
  // 3
  assign_window_pos(18, 8);
  // 4
  assign_window_pos(18, 5);
  // 5
  assign_window_pos(17, 9);
  // 6
  assign_window_pos(17, 13);
  //7
  assign_window_pos(15, 4);
  //8
  assign_window_pos(13, 4);
  //9
  assign_window_pos(13, 9);
  //10
  assign_window_pos(13, 12);
  //11
  assign_window_pos(11, 6);
  //12
  assign_window_pos(9, 4);
  //13
  assign_window_pos(7, 4);

  // paint the rest
  for (idx = 3; idx != 20; ++idx) {

    for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j - 1, idx, PAPER_GREEN | BRIGHT, ' ');
    }
  }

  // paint diagonal
  idx = 3;
  for (idx_j = 2; idx_j != 20; ++idx_j) {
      sp1_PrintAt( idx_j, idx, PAPER_RED | INK_GREEN | BRIGHT, 'E');
       ++idx;
  }

  // paint holes
  idx_j = 5;
  for (idx = 0; idx != 15; ++idx) {
    if(idx != 14) {
        sp1_PrintAt( windows[idx].y, windows[idx].x, BACKGROUND_GREEN, 'A');
    }
    // texture
    x = 2 + ((coords_queso[idx] & 0xF0) >> 4);
    if(x != 17) { // 15 + 2
        sp1_PrintAt(idx_j, x, BACKGROUND_GREEN, 'D');
    }
    if((coords_queso[idx] & 0x0F) != 15) {
        x += (coords_queso[idx] & 0x0F);
        sp1_PrintAt(idx_j, x, BACKGROUND_GREEN, 'D');
    }
    ++idx_j;
    //
  }

  // paint the chair
  paint_chair(17, 22, PAPER_RED, INK_GREEN | BRIGHT);
  paint_table(17, 26, PAPER_RED, INK_GREEN | BRIGHT);

  eaten_items = 4;

  aux_object.y = 5;
  aux_object.x = 5;
  repaint_lives = 1;
  level_x_max = 28;
  level_x_min = 1;
  reset_misifu_position();
}


#endif

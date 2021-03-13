#ifndef _LEVEL2
#define _LEVEL2
#include <sound.h>
#include <stdlib.h>
#include "level1.h"
#include <input.h>
// AKA RATS ROOM
#include "defines.h"

#define UDG_HOLE_MOUSE 65
#define UDG_HOLE_EMPTY 66
#define UDG_SCORE 67
#define UDG_QUESO_DIAG 68
#define UDG_QUESO_TEXT 'T'

#define TOTAL_COORDS_HOLES 11
#define TOTAL_COORDS_QUESO 25
#define DESFASE_Y 6
#define TOTAL_MOUSES 4

#define EATEN_MOUSE 25

#define LEVEL2_TILES_LEN 4
#define LEVEL2_TILES_BASE 65
#define BACKGROUND_CHEESE INK_BLACK | PAPER_YELLOW | BRIGHT

const uint8_t coords_queso [] = {0x0f, 0x2f, 0xf2, 0xf0, 0x31, 0xff, 0x12, 0x31, 0xff, 0x31, 0x32, 0xff, 0x14, 0x15,
                                0xf0, 0x25, 0x5f, 0x31, 0x25, 0xff, 0x25, 0x35, 0xf1, 0x35, 0x50};

const uint8_t coords_holes [] =  {0x35, 0xb1, 0x01, 0x66, 0x83, 0xcd, 0x32, 0xb8, 0x61, 0x89, 0xc5};

// level 2 cheese
const uint8_t level2[] = {
    0x3c, 0x7e, 0x99, 0x81, 0xd5, 0xc3, 0x66, 0x3c, // y:0, x:0 (65)
    0x3c, 0x46, 0x9f, 0xbf, 0xbf, 0xbf, 0x5e, 0x3c, // y:0, x:1 (66)
    0x9c, 0x80, 0xd5, 0xc1, 0x63, 0x41, 0x41, 0x81, // y:0, x:2 (67)
    0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, // y:0, x:3 (68)
};


static inline uint8_t map_cat_pos_in_holes() {

    for(idx = 0; idx != TOTAL_COORDS_HOLES; ++idx) { // 4 mouses
        idx_j = coords_holes[idx];
        if(misifu.y == (DESFASE_Y + ((idx_j & 0xF0) >> 4)) && misifu.x == (2 + (idx_j & 0x0F))) {
            return idx;
        }
    }

    return UNDEF;
}


void detect_fall_in_hole_or_curtain() {

    if(idx != UNDEF) {
        misifu.state = CAT_IN_ROPE;

        // if window has mouse
        for(idx_j = 0; idx_j != 4; ++idx_j) {
            // if a mouse is active in one of the holes
            if(floor_holes[0][idx_j] == idx && floor_holes[0][idx_j] != EATEN_MOUSE) {
                sp1_PrintAtInv(
                    DESFASE_Y + ((coords_holes[idx] & 0xF0) >> 4),
                    3 + (coords_holes[idx] & 0x0F),
                    BACKGROUND_CHEESE, UDG_HOLE_EMPTY);
                repaint_lives = 1;
                floor_holes[0][idx_j] = EATEN_MOUSE;
                sp1_PrintAtInv(1, 3 + (eaten_items + eaten_items), INK_RED | PAPER_GREEN | BRIGHT, UDG_SCORE);
                bit_beepfx_di_fastcall(BEEPFX_SCORE);
                ++eaten_items;
                total_points += 10;
            }
        }

    }


    if (eaten_items == TOTAL_MOUSES) {
        get_out_of_level_generic(WON_LEVEL);
    }
}


void level2_loop() {
    // dance mousies, dance!
    if (random_value < 4 || repaint_lives == 1) {
        repaint_lives = 0;
        // switch mouses
        for(idx_j = 0; idx_j != 4; ++idx_j) {
            idx = floor_holes[0][idx_j];
            if (idx == EATEN_MOUSE) {
                continue;
            }
            // quitar cera, digoo raton
            sp1_PrintAtInv(
                DESFASE_Y + ((coords_holes[idx] & 0xF0) >> 4),
                3 + (coords_holes[idx] & 0x0F),
                BACKGROUND_CHEESE, UDG_HOLE_EMPTY);

            if((idx & 1) == 0) { // par: siguiente impar (0 -> 1, 2 -> 3, 4 -> 5, 6 -> 7)
                ++floor_holes[0][idx_j];
            } else { // impar: anterior par (1 -> 0, 3 -> 2, 5 -> 4, 7 -> 6)
                --floor_holes[0][idx_j];
            }
            idx = floor_holes[0][idx_j];
            // poner raton
            sp1_PrintAtInv(
                DESFASE_Y + ((coords_holes[idx] & 0xF0) >> 4),
                3 + (coords_holes[idx] & 0x0F),
                BACKGROUND_CHEESE, UDG_HOLE_MOUSE);
        }
    }

    idx = map_cat_pos_in_holes();

    if (misifu.state == FALLING) {
        detect_fall_in_hole_or_curtain();
    }

    if ((in & IN_STICK_FIRE) && first_keypress == 0 && idx < 8) {
        // cuidado con que idx no se utilice despues de esto
        if((idx & 1) == 0) {
            ++idx;
        } else {
            --idx;
        }

        misifu.x =  2 + (coords_holes[idx] & 0x0F);
        misifu.y = DESFASE_Y + ((coords_holes[idx] & 0xF0) >> 4) - 1;
        misifu.state = FALLING;
        first_keypress = 1;
    }

    if(!(in & IN_STICK_FIRE)) {
        first_keypress = 0;
    }

    move_broom();
    dog_checks();
    detect_cat_in_window(0);
}

void  print_background_level2() {
  level = 2;
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED | BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);

  uint8_t *queso_text = tiles_lvl1 + 8; // cheese text is at second row of level 1 tiles
  sp1_TileEntry(UDG_QUESO_TEXT, queso_text);

  uint8_t *pt = level2;
  for (idx = 0; idx < LEVEL2_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LEVEL2_TILES_BASE + idx, pt);
  }

  print_room_walls(20, PAPER_RED, INK_GREEN);

  // paint the main cheese
  for (idx = 3; idx != 20; ++idx) {
    for (idx_j = idx + 1; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j - 1, idx, PAPER_YELLOW | BRIGHT, ' ');
    }
  }

  // paint diagonal
  idx = 3;
  for (idx_j = 2; idx_j != 20; ++idx_j) {
      sp1_PrintAt( idx_j, idx, PAPER_RED | INK_YELLOW | BRIGHT, UDG_QUESO_DIAG);
       ++idx;
  }
  // in this level it is used to define holes have a mouse
  idx_j = 1;
  for(idx = 0; idx != 4; ++idx) { // 4 mouses
    floor_holes[0][idx] = idx_j; // indexes of coords_holes
    sp1_PrintAtInv(1, 2 + idx_j, INK_RED | PAPER_BLACK | BRIGHT, UDG_SCORE);
    idx_j += 2;
  }

  // paint holes
  for (idx = 0; idx != TOTAL_COORDS_HOLES; ++idx) {
        if(idx < 8 && (idx & 1) == 1) { // mouses start on even holes
            // variable reusage -memory savings-, sorry!
            first_keypress = UDG_HOLE_MOUSE;
        } else {
            first_keypress = UDG_HOLE_EMPTY;
        }
        sp1_PrintAt(
            DESFASE_Y + ((coords_holes[idx] & 0xF0) >> 4),
            3 + (coords_holes[idx] & 0x0F),
            BACKGROUND_CHEESE, first_keypress);
  }

  // paint textures
  idx_j = 4;
  x = 3;
  for(idx = 0; idx!= TOTAL_COORDS_QUESO; ++idx) {
    // texture
    first_keypress = ((coords_queso[idx] & 0xF0) >> 4);

    if(first_keypress != 15) {
        x += first_keypress;
        sp1_PrintAt(idx_j, x, BACKGROUND_CHEESE, UDG_QUESO_TEXT);
    } else {
        // line jump
        ++idx_j;
        x = 3;
    }
    first_keypress = (coords_queso[idx] & 0x0F);

    if(first_keypress != 15) {
        x += first_keypress;
        sp1_PrintAt(idx_j, x, BACKGROUND_CHEESE, UDG_QUESO_TEXT);
    } else {
        // line jump
        ++idx_j;
        x = 3;
    }
  }
  first_keypress = 0;


  // paint the chair
  paint_chair(22, PAPER_RED | INK_CYAN | BRIGHT);
  paint_table(26, PAPER_RED | INK_CYAN | BRIGHT);

  eaten_items = 0;

  aux_object.y = 5;
  aux_object.x = 5;
  repaint_lives = 1;
  level_x_max = 28;
  level_x_min = 1;
  reset_misifu_position();
}


#endif

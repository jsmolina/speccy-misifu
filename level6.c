#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"
#define GREEN_RED_BRIGHT INK_GREEN | PAPER_RED | BRIGHT

#define CHAIR1 1
#define CHAIR2 3
#define UDG_JAULA_DERECHA_ROTA 65
#define UDG_JAULA_DERECHA 66
#define UDG_JAULA_IZQUIERDA 67
#define LEVEL6_TILES_LEN  7
#define LEVEL6_TILES_BASE  65
#define CAGE_FIRST_POS 17
#define CAGE_FIRST_POS_RIGHT 18
#define CAGE_SECOND_POS 18
#define CAGE_THIRD_POS 19
#define CAGE_FOURTH_POS 20

#define BIRD_RIGHT 0
#define BIRD_RIGHT2 32
#define BIRD_LEFT 64
#define BIRD_LEFT2 96

const uint8_t level6[] = {
    0x00, 0xf0, 0x2c, 0x22, 0x02, 0x82, 0x12, 0xfe, // y:0, x:0 (65)
    0xf0, 0x4c, 0x22, 0x2e, 0xf2, 0x12, 0x12, 0xfe, // y:0, x:1 (66)
    0x1f, 0x65, 0x89, 0xe9, 0x9f, 0x91, 0x91, 0xff, // y:0, x:2 (67)
};


void  print_background_level6() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  PAPER_RED | BRIGHT,
                  ' ' );
  sp1_Invalidate(&full_screen);
  level = 6;
  uint8_t *pt = level6;
  for (idx = 0; idx < LEVEL6_TILES_LEN; idx++, pt += 8) {
      sp1_TileEntry(LEVEL6_TILES_BASE + idx, pt);
  }

  level_x_max = 27;
  level_x_min = 1;

  print_room_walls(20, PAPER_RED, INK_GREEN);
  // paint the chair
  paint_chair(12, PAPER_RED | INK_GREEN | BRIGHT);
  paint_chair2(23, PAPER_RED | INK_GREEN | BRIGHT);
  paint_table( 17, PAPER_RED | INK_GREEN | BRIGHT);
  paint_lamp(5, PAPER_RED | INK_GREEN | BRIGHT);
  // 18, 27
  eaten_items = CAGE_FIRST_POS; // 3 hits are needed to throw cage
  sp1_PrintAt(17, CAGE_FIRST_POS, PAPER_RED | INK_WHITE | BRIGHT, UDG_JAULA_IZQUIERDA);
  sp1_PrintAt(17, CAGE_FIRST_POS_RIGHT, PAPER_RED | INK_WHITE | BRIGHT, UDG_JAULA_DERECHA);
  paint_portrait(GREEN_RED_BRIGHT);
  reset_misifu_position();
  windows[0].x = CAGE_FOURTH_POS;
  windows[0].y = 15;
  bincat_appears = UP;
  bincat_in_bin = LEFT;

  birdsp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 2, 0, 0);
  sp1_AddColSpr(birdsp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);
}

void level6_loop() {
    move_broom();

    detect_fall_in_chair(22, CHAIR1);
    detect_fall_in_chair(12, CHAIR2);

    if(eaten_items != CAGE_FOURTH_POS) {
        if(misifu.y == 17 && (misifu.x >= (eaten_items - 1) && misifu.x <= eaten_items)) {
            // eaten_items = CAGE_FIRST_POS
            for(idx = 0; idx != 2; ++idx) {
                sp1_PrintAtInv(17, eaten_items, PAPER_RED | INK_BLACK | BRIGHT, ' ');
                sp1_PrintAtInv(17, eaten_items + idx, PAPER_RED | INK_BLACK | BRIGHT, ' ');
            }
            ++eaten_items;
            idx_j = 17;
            if(eaten_items == CAGE_FOURTH_POS) {
                idx_j = FLOOR_Y;
            }
            sp1_PrintAtInv(idx_j, eaten_items, PAPER_RED | INK_WHITE | BRIGHT, UDG_JAULA_IZQUIERDA);
            x = UDG_JAULA_DERECHA;
            if(eaten_items == CAGE_FOURTH_POS) {
                --x;
            }
            sp1_PrintAtInv(idx_j, eaten_items + 1, PAPER_RED | INK_WHITE | BRIGHT, x);
            misifu.state = FALLING;
            bit_beepfx_di_fastcall(BEEPFX_DROP_1);
        }
    } else {
        detect_fall_in_table(9);

        if(bincat_appears == UP && random_value < 252) {
            --windows[0].y;
        } else {
            ++windows[0].y;
        }

        if(bincat_in_bin == LEFT && random_value < 252) {
            --windows[0].x;
            x = BIRD_LEFT;
        } else {
            ++windows[0].x;
            x = BIRD_RIGHT;
        }

        if(windows[0].x > 28) {
            bincat_in_bin = LEFT;
            windows[0].x = 28;
        }
        if(windows[0].x <= 1) {
            bincat_in_bin = RIGHT;
            windows[0].x = 1;
        }

        if(windows[0].y > 14) {
            bincat_appears = UP;
            windows[0].y = 14;
        }

        if(windows[0].y <= 1) {
            windows[0].y = 1;
            bincat_appears = DOWN;
        }

        if((windows[0].y == (misifu.y + 1) || windows[0].y == misifu.y) && windows[0].x == misifu.x + 1) {
            get_out_of_level_generic(WON_LEVEL); // yayy
            return;
        }
        if (frame < FRAME_CHANGE) {
            x += 32; // space between frames
        }

        sp1_MoveSprAbs(birdsp, &full_screen, (int)sprite_bird1 + x, windows[0].y, windows[0].x, 0, 0);
    }

    dog_checks();
    detect_cat_in_window(0);
}

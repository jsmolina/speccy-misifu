#include <stdlib.h>
#include <sound.h>
#include "defines.h"
#include "level1.h"
#define GREEN_RED_BRIGHT INK_GREEN | PAPER_RED | BRIGHT

#define UDG_CUADRO_SUPERIOR_IZQUIERDA 65
#define UDG_CUADRO_SUPERIOR_DERECHA 66
#define UDG_CUADRO_INFERIOR_IZQUIERDA 67
#define UDG_CUADRO_INFERIOR_DERECHA 68
#define UDG_JAULA_DERECHA_ROTA 69
#define UDG_JAULA_DERECHA 70
#define UDG_JAULA_IZQUIERDA 71
#define LEVEL6_TILES_LEN  7
#define LEVEL6_TILES_BASE  65
#define CAGE_FIRST_POS 17
#define CAGE_FIRST_POS_RIGHT 18
#define CAGE_SECOND_POS 18
#define CAGE_THIRD_POS 19

const uint8_t level6[] = {
    0xff, 0x80, 0xbf, 0xbc, 0xb8, 0xb3, 0xb4, 0xb1, // y:0, x:0 (65)
    0xff, 0x01, 0xfd, 0x3d, 0x1d, 0xcd, 0x2d, 0x0d, // y:0, x:1 (66)
    0xa5, 0xa7, 0xa6, 0x83, 0x84, 0x8f, 0x80, 0xff, // y:0, x:2 (67)
    0xa5, 0xe5, 0x65, 0xc1, 0x21, 0xf1, 0x01, 0xff, // y:0, x:3 (68)
    0x00, 0xf0, 0x2c, 0x22, 0x02, 0x82, 0x12, 0xfe, // y:0, x:4 (69)
    0xf0, 0x4c, 0x22, 0x2e, 0xf2, 0x12, 0x12, 0xfe, // y:0, x:5 (70)
    0x1f, 0x65, 0x89, 0xe9, 0x9f, 0x91, 0x91, 0xff, // y:0, x:6 (71)
};

inline void paint_portrait() {
    x = UDG_CUADRO_SUPERIOR_IZQUIERDA;
    for(idx_j = 10; idx_j != 12; ++idx_j) {
        for(idx = 10; idx != 12; ++idx) {
            sp1_PrintAt(idx_j, idx, GREEN_RED_BRIGHT, x);
            ++x;
        }
    }
}

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
  paint_chair( 12, PAPER_RED | INK_GREEN | BRIGHT);
  paint_chair2(23, PAPER_RED | INK_GREEN | BRIGHT );
  paint_table( 17, PAPER_RED | INK_GREEN | BRIGHT);
  paint_lamp(5, PAPER_RED | INK_GREEN | BRIGHT);
  // 18, 27
  eaten_items = CAGE_FIRST_POS; // 3 hits are needed to throw cage
  sp1_PrintAt(17, CAGE_FIRST_POS, PAPER_RED | INK_WHITE | BRIGHT, UDG_JAULA_IZQUIERDA);
  sp1_PrintAt(17, CAGE_FIRST_POS_RIGHT, PAPER_RED | INK_WHITE | BRIGHT, UDG_JAULA_DERECHA);
  paint_portrait();
  reset_misifu_position();

}

void level6_loop() {
    move_broom();

    check_chair_and_table();
    // bincat_appears, bincat_in_bin
    //check_cage_and_bird();
    // todo think on moving cage
    if(eaten_items != CAGE_THIRD_POS) {
        if( misifu.y == 17 && (misifu.x >= eaten_items && misifu.x <= (eaten_items + 1))) {
            /*windows[0].has_item = RIGHT;
            misifu.state = FALLING;
            sp1_PrintAtInv(17, 26, GREEN_RED_BRIGHT, ' ');
            sp1_PrintAtInv(17, 27, GREEN_RED_BRIGHT, ' ');
            bit_beepfx_di_fastcall(BEEPFX_DROP_1);
            sp1_PrintAt(FLOOR_Y, 26, GREEN_RED_BRIGHT, 'C');
            sp1_PrintAt(FLOOR_Y, 27, GREEN_RED_BRIGHT, 'D');*/
            zx_border(INK_RED);
            misifu.state = FALLING;
        }
    } else {
       /*
            ++windows[0].x;
            if(windows[0].x > 28) {
                ++windows[0].y;
                windows[0].x = 0;
            }

            if(windows[0].y > 19) {
                windows[0].y = 7;
            }

            if(abs(windows[0].y - misifu.y) < 2 && abs(windows[0].x - misifu.x) < 2) {
                get_out_of_level_generic(WON_LEVEL); // yayy
                return;
            }
            if (frame < FRAME_CHANGE) {
                windows[1].x = BIRD_OFFSET;
            } else {
                windows[1].x = BIRD_OFFSET2;
            }

            sp1_MoveSprAbs(bincatsp, &full_screen, (int)sprite_bincat1 +windows[1].x, windows[0].y, windows[0].x, 0, 0);
            */
    }

    detect_cat_in_window(0);
    //dog_checks();
}

#include "defines.h"

const uint8_t udg_fishtank1[] = {0x3f, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x7};
const uint8_t udg_fishtank2[] = {0xfc, 0xce, 0xff, 0xff, 0x93, 0xfe, 0xf8, 0xe0};

void  print_background_level4() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_MAGENTA,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);

  // O R S T U V
  define_silla_udgs();

  sp1_TileEntry('A', udg_fishtank1);
  sp1_TileEntry('B', udg_fishtank2);

  print_room_walls(12, PAPER_MAGENTA, INK_CYAN);

  // paint the chair
  paint_chair(17, 10, PAPER_MAGENTA, INK_CYAN);

  // 17,22
  paint_table(17, 22, PAPER_MAGENTA, INK_CYAN);
  // fishtank
  sp1_PrintAt( 17, 22,  INK_CYAN | PAPER_MAGENTA, 'A');
  sp1_PrintAt( 17, 23,  INK_CYAN | PAPER_MAGENTA, 'B');

  reset_misifu_position();

  aux_object.y = 5;
  aux_object.x = 5;
  aux_object.offset = AUX_BROOM;
  repaint_lives = 1;

  level_x_max = 28;
  level_x_min = 0;

  sp1_UpdateNow();


  misifu.state = NONE;
}

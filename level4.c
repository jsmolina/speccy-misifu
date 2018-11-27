#include "defines.h"

void  print_background_level4() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_MAGENTA,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);


  define_silla_udgs();

  print_room_walls(PAPER_MAGENTA, INK_CYAN);

  // paint the chair
  paint_chair(17, 22, PAPER_MAGENTA, INK_CYAN);

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

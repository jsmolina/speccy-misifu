#include "defines.h"

void  print_background_level4() {
    sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_MAGENTA,
                  ' ' );
    sp1_Invalidate(&full_screen);

    define_silla_udgs();

    print_room_walls(PAPER_MAGENTA);

    zx_border(INK_BLACK);

    paint_chair(17, 15, PAPER_MAGENTA);

    sp1_UpdateNow();
}
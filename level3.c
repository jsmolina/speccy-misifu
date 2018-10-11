#include "level3.h"
#include "defines.h"


void  print_background_level3() {
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_GREEN,
                  ' ' );

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', heart1);
  sp1_TileEntry('B', heart2);


}
#include <stdlib.h>
#include "defines.h"

const uint8_t udg_watertop[] = {0xff, 0xef, 0xc5, 0x80, 0x0, 0x0, 0x0, 0x0};
const uint8_t udg_fish[] = {0x0, 0x9c, 0xbe, 0xfd, 0xff, 0xbf, 0x9e, 0x0};
const uint8_t udg_fishL[] = {0x0, 0x39, 0x7d, 0xbf, 0xff, 0xfd, 0x79, 0x0};
const uint8_t udg_eel[] = {0x0, 0x0, 0x0, 0x48, 0x36, 0x1, 0x0, 0x0};


void  print_background_level4() {
  level = 4;
  // todo cat should not take too much or get out of breath... level timer
  // swimming state always here
  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_MAGENTA | PAPER_CYAN,
                  ' ' );
  zx_border(INK_BLACK);
  sp1_Invalidate(&full_screen);


  sp1_TileEntry('W', udg_watertop);
  sp1_TileEntry('F', udg_fish);
  sp1_TileEntry('G', udg_fish);
  sp1_TileEntry('E', udg_eel);

  // paint watertop (once)
  for(idx = 0; idx != 32; ++idx) {
    sp1_PrintAt( 0, idx,  INK_BLACK | PAPER_CYAN, 'W');
  }

  // udgxs, udgys are fishes. Mod is slow, but helps reduce code and paint might be slow.
  for(idx = 0; idx != 8; ++idx) {
        udgxs[idx] = rand() % 28;
        udgys[idx] = rand() % 22;

        sp1_PrintAt( udgxs[idx], udgys[idx],  INK_BLACK | PAPER_CYAN, 'F');
  }

  // now eels
  for(idx = 0; idx != 5; ++idx) {
       // paint eels... if there's an overlap... bad luck
       floor_holes[idx][0] = rand() % 28;
       floor_holes[idx][1] = rand() % 22;

       sp1_PrintAt( floor_holes[idx][0], floor_holes[idx][1],  INK_BLACK | PAPER_CYAN, 'E');
  }

  level_x_max = 28;
  level_x_min = 0;

  reset_misifu_position();
  misifu.state = SWIMMING;

  misifu.x = 5;
  misifu.y = 5;

  sp1_UpdateNow();
}

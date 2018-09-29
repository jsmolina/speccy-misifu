#ifndef _LEVEL2
#define _LEVEL2

#include <defines.h>
#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>


unsigned char hole_empty[] = {0xc3, 0x81, 0x0, 0x0, 0x0, 0x0, 0x81, 0xc3};
unsigned char hole_mouse[] = {0xc3, 0xa5, 0x18, 0x3c, 0x5a, 0x18, 0xa5, 0xc3};
unsigned char cheese1[] = {0xff, 0xff, 0x3f, 0x7, 0xc0, 0xf8, 0xff, 0xff};
unsigned char cheese2[] = {0xff, 0xff, 0xff, 0x71, 0x61, 0xf7, 0xff, 0xff};
unsigned char cheese3[] = {0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};

unsigned char wall1[] = {0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef};
unsigned char wall2[] = {0xff, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0xff};
unsigned char wall3[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
unsigned char wall4[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

void  print_background_level2() {
  uint8_t i;


  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED,
                  ' ' );

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('C', cheese1);
  sp1_TileEntry('D', cheese2);
  sp1_TileEntry('E', cheese3);
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  // draw vertical call
  for (i = 9; i != 16; ++i) {
    sp1_PrintAt( 9, 4, INK_CYAN | PAPER_BLACK, 'F');
  }
}

#endif

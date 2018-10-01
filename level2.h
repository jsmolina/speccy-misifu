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

unsigned char wall1[] = {0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f};
unsigned char wall2[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0};
unsigned char wall3[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
unsigned char wall4[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

void print_room_walls() {
  uint8_t i;
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  for(i = 0; i != 3; ++i) {
    // upper left
    sp1_PrintAt( 3 + i, i, INK_RED | PAPER_BLACK, 'H');
    // down left diagonal
    sp1_PrintAt( 20 - i, i, INK_RED | PAPER_BLACK, 'I');
    // upper right
    sp1_PrintAt( 5 - i, 29 + i, INK_RED | PAPER_BLACK, 'I');
    // down right
    sp1_PrintAt( 18 + i, 29 + i, INK_RED | PAPER_BLACK, 'H');
  }

  // draw vertical wall
  for (i = 6; i != 18; ++i) {
    sp1_PrintAt( i, 3, INK_RED | PAPER_BLACK, 'F');
    sp1_PrintAt( i, 29, INK_RED | PAPER_BLACK, 'F');
  }

  // draw horizontal wall
  for (i = 3; i != 29; ++i) {
    sp1_PrintAt( 5, i, INK_RED | PAPER_BLACK, 'G');
    sp1_PrintAt( 17, i, INK_RED | PAPER_BLACK, 'G');
  }
}

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

  print_room_walls();

  // todo paint cheese here

}

#endif

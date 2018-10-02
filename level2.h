#ifndef _LEVEL2
#define _LEVEL2

#include <defines.h>
#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>


unsigned char hole_empty[] = {0xc3, 0x81, 0x0, 0x0, 0x0, 0x0, 0x81, 0xc3};
unsigned char hole_mouse[] = {0xc3, 0xa5, 0x18, 0x3c, 0x5a, 0x18, 0xa5, 0xc3};
unsigned char cheese2[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
unsigned char curtain[] = {0x7e, 0x9c, 0xe3, 0xff, 0xff, 0x7e, 0x9c, 0xe3};

unsigned char wall1[] = {0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f};
unsigned char wall2[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0};
unsigned char wall3[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
unsigned char wall4[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

uint8_t _hole_pos(uint8_t row, uint8_t col) {
    if (row == 6 && col == 4) {
        return 1;
    } else if (row == 8 && col == 6) {
        return 1;
    } else if (row == 11 && col == 7) {
        return 1;
    } else if (row == 12 && col == 6) {
        return 1;
    }

    return 0;
}

void print_room_walls() {
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  sp1_TileEntry('J', curtain);
  sp1_TileEntry('N', udg_win2); // full square

  for(index = 0; index != 3; ++index) {
    // upper left
    sp1_PrintAt( 3 + index, index, INK_RED | PAPER_BLACK, 'H');
    // down left diagonal
    sp1_PrintAt( 20 - index, index, INK_RED | PAPER_BLACK, 'I');
    // upper right
    sp1_PrintAt( 5 - index, 29 + index, INK_RED | PAPER_BLACK, 'I');
    // down right
    sp1_PrintAt( 18 + index, 29 + index, INK_RED | PAPER_BLACK, 'H');
  }

  // draw vertical wall
  for (index = 6; index != 18; ++index) {
    sp1_PrintAt( index, 3, INK_RED | PAPER_BLACK, 'F');
    sp1_PrintAt( index, 29, INK_RED | PAPER_BLACK, 'F');
  }

  // draw horizontal wall
  for (index = 3; index != 29; ++index) {
    sp1_PrintAt( 5, index, INK_RED | PAPER_BLACK, 'G');
    sp1_PrintAt( 17, index, INK_RED | PAPER_BLACK, 'G');
  }

  for (index = 8; index != 10; ++index) {
    sp1_PrintAt( index, 20, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( index, 21, INK_RED | PAPER_GREEN, 'J');

    sp1_PrintAt( index, 22, INK_RED | PAPER_BLACK, 'N');
    sp1_PrintAt( index, 23, INK_RED | PAPER_BLACK, 'N');
    sp1_PrintAt( index, 24, INK_RED | PAPER_BLACK, 'N');
    sp1_PrintAt( index, 25, INK_RED | PAPER_BLACK, 'N');

    sp1_PrintAt( index, 26, INK_RED | PAPER_GREEN, 'J');
    sp1_PrintAt( index, 27, INK_RED | PAPER_GREEN, 'J');
  }
  sp1_PrintAt( 10, 20, INK_RED | PAPER_GREEN, 'J');
  sp1_PrintAt( 10, 21, INK_RED | PAPER_GREEN, 'J');
  sp1_PrintAt( 10, 26, INK_RED | PAPER_GREEN, 'J');
  sp1_PrintAt( 10, 27, INK_RED | PAPER_GREEN, 'J');


}

void  print_background_level2() {
  uint8_t j;


  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_RED,
                  ' ' );

  sp1_Invalidate(&full_screen);

  sp1_TileEntry('A', hole_empty);
  sp1_TileEntry('B', hole_mouse);
  sp1_TileEntry('C', cheese2);

  print_room_walls();

  for (index = 3; index != 20; ++index) {

    for (j = index + 1; j != 21; ++j) {
        if (_hole_pos(j, index) == 1) {
            sp1_PrintAt( j, index, INK_GREEN | PAPER_BLACK, 'A');
        } else {
            sp1_PrintAt( j, index, INK_GREEN | PAPER_BLACK, 'C');
        }
    }
  }
  // todo paint cheese here

}

#endif

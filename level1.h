#ifndef _LEVEL1
#define _LEVEL1

#include <defines.h>
#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>

struct freesprite windows[12];

const uint8_t bin_places[] = {
0, 1, 2, 3,
0, 1, 2, 3,
0, 1, 2, 3,
0, 0, 0, 0,
0, 0, 0, 0,
1, 2, 3, 0,
1, 2, 3, 0,
0, 0, 0, 0};


uint8_t udg_valla1[] = {0xff, 0x9f, 0x8f, 0x87, 0x81, 0x81, 0x81, 0x81};
uint8_t udg_valla2[] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
uint8_t udg_valla3[] = {0xff, 0xe1, 0xe1, 0x81, 0x81, 0x81, 0x81, 0x81};
uint8_t udg_valla4[] = {0xef, 0x8f, 0x83, 0x83, 0x83, 0x81, 0x81, 0x81};

const uint8_t cubo_down1[] = {0xab, 0xd5, 0xaa, 0xd5, 0xfe, 0x31, 0xe, 0x1};
const uint8_t cubo_down2[] = {0xff, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0x0, 0xff};
const uint8_t cubo_down3[] = {0xa9, 0x57, 0xa5, 0x5b, 0xf3, 0x8c, 0xf8, 0x80};
const uint8_t cubo_middle1[] = {0x9e, 0xa5, 0xa5, 0xba, 0x9d, 0xcf, 0xb1, 0xde};
const uint8_t cubo_middle2[] = {0x0, 0xff, 0x52, 0xad, 0x52, 0xff, 0xff, 0x0};
const uint8_t cubo_middle3[] = {0x7d, 0xa9, 0xad, 0x5d, 0xfd, 0x7b, 0x8d, 0x7f};

const uint8_t cubotop1[] = {0x0, 0x0, 0x33, 0x4f, 0x9f, 0xbf, 0x9f, 0xcf};
const uint8_t cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
const uint8_t cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

uint8_t udg_rope[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd2};
unsigned char udg_win1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d}; // with rope
unsigned char udg_win2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char udg_win3[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

uint8_t udg_c[] = {0x62, 0x42, 0x4e, 0x4e, 0x4e, 0x62, 0x72, 0x7e};
uint8_t udg_a[] = {0x72, 0x60, 0x4c, 0x40, 0x18, 0x12, 0x12, 0x7e};
uint8_t udg_t[] = {0x60, 0x2, 0x12, 0x72, 0x78, 0x78, 0x78, 0x7e};

// todo add udg for numbers (score, lives)

void  print_cubo(uint8_t x) {
  uint8_t y;

  y = 22;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'L');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'D');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'E');
  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');
  // only second bin is higher
  if(x == HIGHER_BIN_X) {
      --y;
      sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');

      --y;
      sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'F');
      sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'G');
      sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'H');
  }

  --y;
  sp1_PrintAt(y, x, INK_BLACK | PAPER_MAGENTA, 'I');
  sp1_PrintAt(y, x + 1, INK_BLACK | PAPER_MAGENTA, 'J');
  sp1_PrintAt(y, x + 2, INK_BLACK | PAPER_MAGENTA, 'K');

  --y;
  for (y = y; y != 15; y--) {
    sp1_PrintAt( y, x, PAPER_CYAN, 'V');
    sp1_PrintAt( y, x + 1, PAPER_CYAN, 'V');
    sp1_PrintAt( y, x + 2, PAPER_CYAN, 'V');
  }
  sp1_PrintAt(y, x, PAPER_CYAN, 'W');
  sp1_PrintAt(y, x + 1, PAPER_CYAN, 'W');
  sp1_PrintAt(y, x + 2, PAPER_CYAN, 'X');
}


void paint_window(uint8_t num, uint16_t colour) {

  for (x = windows[num].x; x != windows[num].x + 5; ++x) {
    // top is equal
    sp1_PrintAtInv(windows[num].y, x, colour, 'N');
    if (num > 7) {
        // bottom varies
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'O');
    } else {
        sp1_PrintAtInv(windows[num].y + 1, x, colour, 'M');
    }
  }
}

void  print_background() {
  uint8_t x, y, count;

  count = 0;

  sp1_TileEntry('V', udg_valla2);  // middle of fence
  sp1_TileEntry('W', udg_valla1);  // top of fence
  sp1_TileEntry('X', udg_valla3); // another top of fence
  sp1_TileEntry('Y', udg_valla4); // another top of fence
  sp1_TileEntry('L', cubo_down1);
  sp1_TileEntry('D', cubo_down2);
  sp1_TileEntry('E', cubo_down3);
  sp1_TileEntry('F', cubo_middle1);
  sp1_TileEntry('G', cubo_middle2);
  sp1_TileEntry('H', cubo_middle3);
  sp1_TileEntry('I', cubotop1);
  sp1_TileEntry('J', cubotop2);
  sp1_TileEntry('K', cubotop3);
  sp1_TileEntry('C', udg_c);
  sp1_TileEntry('A', udg_a);
  sp1_TileEntry('T', udg_t);

  sp1_TileEntry('R', udg_rope); // da rope
  sp1_TileEntry('M', udg_win1); // bottom with rope
  sp1_TileEntry('N', udg_win2); // full square
  sp1_TileEntry('O', udg_win3); // bottom without rope

  count = 0;
  // paint valla
  for (x = 0; x!=MAX_X; ++x) {

      if (bin_places[x] == 0) {
          if (x % 2 == 0) {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'W');
          } else if (x % 3 == 0) {
            sp1_PrintAt(15, x,  PAPER_CYAN, 'Y');
          } else {
             sp1_PrintAt(15, x,  PAPER_CYAN, 'X');
          }

          for (y=16; y!=21; ++y)
          {
              sp1_PrintAt( y, x,  PAPER_CYAN, 'V');
          }
      } else if (bin_places[x] == 1) {
          ++count;
          print_cubo(x);
      }
  }
  sp1_PrintAt( 17, 29, INK_CYAN | PAPER_BLACK, 'C');
  sp1_PrintAt( 18, 30,  INK_CYAN | PAPER_BLACK, 'A');
  sp1_PrintAt( 19, 31,  INK_CYAN | PAPER_BLACK, 'T');

  // paint the ropes
  for (x=0; x != MAX_X; ++x) {
    sp1_PrintAt(9, x, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(5, x, INK_BLACK | PAPER_MAGENTA, 'R');
    sp1_PrintAt(1, x, INK_BLACK | PAPER_MAGENTA, 'R');
  }


   y = 4;
   x = 2;
   // define how to paint windows
   for(count = 0; count != 12; ++count) {
      windows[count].x = x;
      windows[count].y = y;
      x = x + 8;
      if (x >= 32) {
        x = 2;
        y = y + 4;
      }

      paint_window(count, PAPER_CYAN);
   }

}


#endif

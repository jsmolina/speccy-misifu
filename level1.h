#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>

const unsigned char bin_places[] = {
0, 1, 2, 2,
0, 1, 2, 2,
0, 1, 2, 2,
0, 0, 0, 0,
0, 0, 0, 0,
1, 2, 2, 0,
1, 2, 2, 0,
0, 0, 0, 0};

const unsigned char udg_valla1[] = {0x0, 0x60, 0x70, 0x78, 0x7e, 0x7e, 0x7e, 0x7e};
const unsigned char udg_valla2[] = {0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e};
const unsigned char udg_valla3[] = {0x0, 0x1e, 0x1e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e};
const unsigned char udg_valla4[] = {0x10, 0x70, 0x7c, 0x7c, 0x7c, 0x7e, 0x7e, 0x7e};

const unsigned char cubo_down1[] = {0xab, 0xd5, 0xaa, 0xd5, 0xfe, 0x31, 0xe, 0x1};
const unsigned char cubo_down2[] = {0xff, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0x0, 0xff};
const unsigned char cubo_down3[] = {0xa9, 0x57, 0xa5, 0x5b, 0xf3, 0x8c, 0xf8, 0x80};
const unsigned char cubo_middle1[] = {0x9e, 0xa5, 0xa5, 0xba, 0x9d, 0xcf, 0xb1, 0xde};
const unsigned char cubo_middle2[] = {0x0, 0xff, 0x52, 0xad, 0x52, 0xff, 0xff, 0x0};
const unsigned char cubo_middle3[] = {0x7d, 0xa9, 0xad, 0x5d, 0xfd, 0x7b, 0x8d, 0x7f};

const unsigned char cubotop1[] = {0x0, 0x0, 0x33, 0x4f, 0x9f, 0xbf, 0x9f, 0xcf};
const unsigned char cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
const unsigned char cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

void  print_cubo(unsigned char x) {
  unsigned char x1 = x + 1;
  unsigned char x2 = x + 2;
  unsigned char y;

  sp1_PrintAt(22, x, INK_BLACK | PAPER_MAGENTA, 'C');
  sp1_PrintAt(22, x1, INK_BLACK | PAPER_MAGENTA, 'D');
  sp1_PrintAt(22, x2, INK_BLACK | PAPER_MAGENTA, 'E');
  sp1_PrintAt(21, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(21, x1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(21, x2, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(20, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(20, x1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(20, x2, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(19, x, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(19, x1, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(19, x2, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(18, x, INK_BLACK | PAPER_MAGENTA, 'I');
  sp1_PrintAt(18, x1, INK_BLACK | PAPER_MAGENTA, 'J');
  sp1_PrintAt(18, x2, INK_BLACK | PAPER_MAGENTA, 'K');

  for (y = 17; y != 14; y--) {
    sp1_PrintAt( y, x, INK_CYAN | PAPER_MAGENTA, 'V');
    sp1_PrintAt( y, x1, INK_CYAN | PAPER_MAGENTA, 'V');
    sp1_PrintAt( y, x2, INK_CYAN | PAPER_MAGENTA, 'V');
  }
  sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'W');
  sp1_PrintAt(14, x1, INK_CYAN | PAPER_MAGENTA, 'W');
  sp1_PrintAt(14, x2, INK_CYAN | PAPER_MAGENTA, 'X');
}

void  print_background() {
    unsigned char x, y;



  sp1_TileEntry('V', udg_valla2);  // middle of fence
  sp1_TileEntry('W', udg_valla1);  // top of fence
  sp1_TileEntry('X', udg_valla3); // another top of fence
  sp1_TileEntry('Y', udg_valla4); // another top of fence
  sp1_TileEntry('C', cubo_down1);
  sp1_TileEntry('D', cubo_down2);
  sp1_TileEntry('E', cubo_down3);
  sp1_TileEntry('F', cubo_middle1);
  sp1_TileEntry('G', cubo_middle2);
  sp1_TileEntry('H', cubo_middle3);
  sp1_TileEntry('I', cubotop1);
  sp1_TileEntry('J', cubotop2);
  sp1_TileEntry('K', cubotop3);
  // paint valla
  for (x = 0; x!=MAX_X; x++) {

      if (bin_places[x] == 0) {
          if (x % 2 == 0) {
             sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'W');
          } else if (x % 3 == 0) {
            sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'Y');
          } else {
             sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'X');
          }

          for (y=15; y!=21; ++y)
          {
              sp1_PrintAt( y, x, INK_CYAN | PAPER_MAGENTA, 'V');
          }
      } else if (bin_places[x] == 1) {
          print_cubo(x);
      }
  }

}
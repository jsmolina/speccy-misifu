#pragma output REGISTER_SP = 0xD000


#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>
#include <input.h>



struct sp1_Rect full_screen = {0, 0, 32, 24};

int main()
{
  struct sp1_ss  *catr1sp;

  unsigned char x, y, draw, frame, frame_malo, initial_jump_y, jump_direction;
  unsigned char x_malo;
  unsigned char malo_appears = 0;
  unsigned int   animation_offset;

  unsigned char udg_valla1[] = {0x0, 0x60, 0x70, 0x78, 0x7e, 0x7e, 0x7e, 0x7e};
  unsigned char udg_valla2[] = {0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e};
  unsigned char udg_valla3[] = {0x0, 0x1e, 0x1e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e};
  unsigned char cubo_down1[] = {0xab, 0xd5, 0xaa, 0xd5, 0xfe, 0x31, 0xe, 0x1};
  unsigned char cubo_down2[] = {0xff, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0x0, 0xff};
  unsigned char cubo_down3[] = {0xa9, 0x57, 0xa5, 0x5b, 0xf3, 0x8c, 0xf8, 0x80};
  unsigned char cubo_middle1[] = {0x9e, 0xa5, 0xa5, 0xba, 0x9d, 0xcf, 0xb1, 0xde};
  unsigned char cubo_middle2[] = {0x0, 0xff, 0x52, 0xad, 0x52, 0xff, 0xff, 0x0};
  unsigned char cubo_middle3[] = {0x7d, 0xa9, 0xad, 0x5d, 0xfd, 0x7b, 0x8d, 0x7f};

  unsigned char cubotop1[] = {0x0, 0x0, 0x33, 0x4f, 0x9f, 0xbf, 0x9f, 0xcf};
  unsigned char cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
  unsigned char cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );
  sp1_TileEntry('V', udg_valla2);  // middle of fence
  sp1_TileEntry('W', udg_valla1);  // top of fence
  sp1_TileEntry('X', udg_valla3); // another top of fence
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
  for (x = 0; x!=4; x++) {
      if (x % 2 == 0) {
            sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'W');
      } else {
            sp1_PrintAt(14, x, INK_CYAN | PAPER_MAGENTA, 'X');
      }
      for (y=15; y!=21; ++y)
      {
          sp1_PrintAt( y, x, INK_CYAN | PAPER_MAGENTA, 'V');
      }
  }
  sp1_PrintAt(22, 4, INK_BLACK | PAPER_MAGENTA, 'C');
  sp1_PrintAt(22, 5, INK_BLACK | PAPER_MAGENTA, 'D');
  sp1_PrintAt(22, 6, INK_BLACK | PAPER_MAGENTA, 'E');
  sp1_PrintAt(21, 4, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(21, 5, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(21, 6, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(20, 4, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(20, 5, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(20, 6, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(19, 4, INK_BLACK | PAPER_MAGENTA, 'F');
  sp1_PrintAt(19, 5, INK_BLACK | PAPER_MAGENTA, 'G');
  sp1_PrintAt(19, 6, INK_BLACK | PAPER_MAGENTA, 'H');

  sp1_PrintAt(18, 4, INK_BLACK | PAPER_MAGENTA, 'I');
  sp1_PrintAt(18, 5, INK_BLACK | PAPER_MAGENTA, 'J');
  sp1_PrintAt(18, 6, INK_BLACK | PAPER_MAGENTA, 'K');

  for (y = 17; y != 14; y--) {
  sp1_PrintAt( y, 4, INK_CYAN | PAPER_MAGENTA, 'V');
  sp1_PrintAt( y, 5, INK_CYAN | PAPER_MAGENTA, 'V');
  sp1_PrintAt( y, 6, INK_CYAN | PAPER_MAGENTA, 'V');
  }
  sp1_PrintAt(14, 4, INK_CYAN | PAPER_MAGENTA, 'W');
  sp1_PrintAt(14, 5, INK_CYAN | PAPER_MAGENTA, 'W');
  sp1_PrintAt(14, 6, INK_CYAN | PAPER_MAGENTA, 'X');



  sp1_Invalidate(&full_screen);

  catr1sp = add_sprite_protar1();


  draw = NO_DRAW;

  x=0;
  y=FLOOR_Y;
  x_malo = 22;
  frame = 0;
  frame_malo = 0;
  initial_jump_y = 0;
  jump_direction = 0;
  animation_offset=0;
  sp1_MoveSprPix(catr1sp, &full_screen, (void*)1, x++, y);

  while(1)
  {
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT) ) {
        draw = JUMPING;
        initial_jump_y = y;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && x<28) {
            jump_direction = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && x>0) {
            jump_direction = JUMP_LEFT;
        } else {
            jump_direction = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && x<28 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_RIGHT;
        ++x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && x > 0 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_LEFT;
        --x;
    }

    frame = (frame + 1) % 4;


    //sp1_MoveSprPix(catr1sp, &full_screen, (void*)(animation_offset), x, y);
    sp1_MoveSprAbs(catr1sp, &full_screen, (void*) animation_offset,y, x, 0, 0);

    if (draw == NO_DRAW && frame == 3) {
        animation_offset = BORED;
    } else if (draw == WALKING_RIGHT) {
        if (frame < 2) {
            animation_offset = RIGHTC1;
        } else if (frame < 4) {
            animation_offset = RIGHTC2;
        }
        draw = NO_DRAW;
    } else if (draw == WALKING_LEFT) {
        if (frame < 2) {
            animation_offset = LEFTC1;
        } else if (frame < 4) {
            animation_offset = LEFTC2;
        }
        draw = NO_DRAW;
    } else if (draw == JUMPING) {
        y--;

        if(jump_direction == JUMP_RIGHT) {
            ++x;
            animation_offset = JRIGHTC1;
        }  else if(jump_direction == JUMP_LEFT && x > 0) {
            --x;
            animation_offset = JLEFTC1;
        } else {
            animation_offset = JUMPINGC1;
        }

        if (initial_jump_y - y >= 8 || x > 28) {
            draw = FALLING;
        }
    } else if (draw == FALLING) {
        ++y;
        animation_offset = JUMPINGC1;
        if(y == FLOOR_Y) {
            draw = NO_DRAW;
            animation_offset = BORED;
        }
    }

    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

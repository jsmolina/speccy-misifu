#pragma output REGISTER_SP = 0xD000


#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>


struct sp1_Rect full_screen = {0, 0, 32, 24};

int main()
{
  struct sp1_ss  *catr1sp;

  unsigned char x, y, draw, frame, frame_malo, initial_jump_y, jump_direction;
  unsigned char x_malo;
  unsigned char malo_appears = 0;
  unsigned char   animation_offset;

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_WHITE,
                  'X' );
  sp1_Invalidate(&full_screen);

  catr1sp = add_sprite_protar1();


  draw = WALKING_RIGHT;

  x=0;
  y=FLOOR_Y;
  x_malo = 22;
  frame = 0;
  frame_malo = 0;
  initial_jump_y = 0;
  jump_direction = 0;
  animation_offset=0;

  while(1)
  {

    if (draw == WALKING_RIGHT) {
        if (frame==0) {
            animation_offset = 24;
            frame = 1;
        } else {
            animation_offset = 0;
            frame = 0;
        }
        // (struct sp1_ss *s,struct sp1_Rect *clip,void *frame,uint16_t x,uint16_t y)
        sp1_MoveSprPix(catr1sp, &full_screen, 0, x++, 0);
        // todo *frame animation_offset should be 16 + 8 (but mask counts for this offset and then is 48?)
        // sp1_MoveSprPix(catr1sp, &full_screen, (void*)(animation_offset + DELTA), x++, 0);

    }



    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

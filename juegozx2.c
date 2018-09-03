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

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_WHITE,
                  'X' );
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

        if(in_key_pressed(IN_KEY_SCANCODE_p)) {
            jump_direction = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o)) {
            jump_direction = JUMP_LEFT;
        } else {
            jump_direction = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p) && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_RIGHT;
        ++x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o) && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_LEFT;
        --x;
    }

    if (draw != NO_DRAW) {
        frame = (frame + 1) % 4;
    }
    sp1_MoveSprPix(catr1sp, &full_screen, (void*)(animation_offset), x, y);


    if (draw == WALKING_RIGHT) {
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
        y = y - 2;

        if(jump_direction == JUMP_RIGHT) {
            ++x;
            animation_offset = JRIGHTC1;
        }  else if(jump_direction == JUMP_LEFT && x > 0) {
            --x;
            animation_offset = JLEFTC1;
        } else {
            animation_offset = JUMPINGC1;
        }

        if (initial_jump_y - y >= 32) {
            draw = FALLING;
        }
    } else if (draw == FALLING) {
        y = y +2;;
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

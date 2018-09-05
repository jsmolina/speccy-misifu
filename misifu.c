#pragma output REGISTER_SP = 0xD000


#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>
#include <input.h>
#include <level1.h>

extern unsigned char abs2(unsigned char v);

struct sp1_Rect full_screen = {0, 0, 32, 24};

int main()
{
  struct sp1_ss  *catr1sp;
  struct sp1_ss  *dogr1sp;

  unsigned char x, y, draw, frame, frame_malo, initial_jump_y, jump_direction;
  unsigned char x_malo;
  unsigned char malo_appears = 0;
  unsigned int   animation_offset;
  unsigned char malo_animation_offset;
  unsigned char fighting_frames = 0;
  unsigned char cat_in_bin = 0;

  unsigned char first_keypress = 0;

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );

  print_background();

  sp1_Invalidate(&full_screen);

  catr1sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();

  draw = NO_DRAW;

  x=0;
  y=FLOOR_Y;
  x_malo = 22;
  frame = 0;
  frame_malo = 0;
  initial_jump_y = 0;
  jump_direction = 0;
  animation_offset = RIGHTC1;
  malo_animation_offset = DOG1;
  sp1_MoveSprPix(catr1sp, &full_screen, (void*)1, x++, y);

  while(1)
  {

    if (malo_appears != 1 && first_keypress != 0) {
        malo_appears = rand() % 500;
    }
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
        if (first_keypress == 0) {
            first_keypress = frame;
            srand(first_keypress);
        }

        draw = WALKING_RIGHT;
        ++x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && x > 0 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_LEFT;
        --x;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a)) {
        // todo automate in random with mod
        malo_appears = 1;
        x_malo = MAX_X;
    }

    frame = (frame + 1) % 4;

    // paint 'prota here'
    sp1_MoveSprAbs(catr1sp, &full_screen, (void*) animation_offset, y, x, 0, 0);

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

        if(bin_places[x] > 0 && y == 17) {
            // stop falling
            draw = NO_DRAW;
            cat_in_bin = x;
        }

        if(y == FLOOR_Y) {
            draw = NO_DRAW;
            animation_offset = BORED;
        }
    }

    // cat falls appart from bin
    if (y < FLOOR_Y && cat_in_bin != 0) {
        if (bin_places[x] == 0) {
            draw = FALLING;
            cat_in_bin = 0;
        }
    }

    // time for doggy checks
    if (draw != FIGHTING && malo_appears == 1) {
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) malo_animation_offset, FLOOR_Y, x_malo, 0, 0);

        --x_malo;

        if (x_malo <= 0) {
            malo_appears = 0;
            x_malo = 33;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) malo_animation_offset, FLOOR_Y, x_malo, 0, 0);
        }

        if (frame < 2) {
            malo_animation_offset = DOG1;
        } else if (frame < 4) {
            // todo fighting will be 49 + 48
            malo_animation_offset = DOG2;
        }

        // detects collission malo->misifu
        if( abs(x - x_malo) < 3 && y > 18) {
            malo_appears = 0;
            draw = FIGHTING;
            y = FLOOR_Y;
            fighting_frames = 20;
            // hide cat
            x = 33;
        }
    }

    if (draw == FIGHTING) {
        if (frame < 2) {
            malo_animation_offset = DOGFIGHTING1;
        } else if (frame < 4) {
            // todo fighting will be 49 + 48
            malo_animation_offset = DOGFIGHTING2;
        }

        --fighting_frames;
        if (fighting_frames <= 0) {
            draw = NO_DRAW;
            malo_appears = 0;
            x_malo = 33;
            x = 0;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) malo_animation_offset, FLOOR_Y, x_malo, 0, 0);
            // todo remove one live
        } else {
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) malo_animation_offset, FLOOR_Y, x_malo, 0, 0);
        }
    }

    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

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
  struct sp1_ss  *bincatsp;

  unsigned char x, y, draw, frame, frame_malo, initial_jump_y, draw_additional;
  unsigned char x_malo;
  unsigned char malo_appears = NONE;
  unsigned char r_bincat = 0;
  unsigned char bincat_in_bin = NONE;
  unsigned int  cat_offset;
  unsigned char dog_offset;
  // keeps animation frames when something takes longer
  unsigned char anim_frames = 0;
  unsigned char cat_in_bin = NONE;

  unsigned char first_keypress = NONE;

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );

  print_background();

  sp1_Invalidate(&full_screen);

  catr1sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();

  draw = NONE;

  x=0;
  y=FLOOR_Y;
  x_malo = 22;
  frame = 0;
  frame_malo = 0;
  initial_jump_y = 0;
  draw_additional = 0;
  cat_offset = RIGHTC1;
  dog_offset = DOG1;

  while(1)
  {

    if (malo_appears != YES && first_keypress != NONE) {
        malo_appears = rand() % 500;
    }
    
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT) ) {
        draw = JUMPING;
        initial_jump_y = y;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && x<28) {
            draw_additional = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && x>0) {
            draw_additional = JUMP_LEFT;
        } else {
            draw_additional = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && x<28 && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        if (first_keypress == NONE) {
            first_keypress = frame;
            srand(first_keypress);
        }

        draw = WALKING_RIGHT;
        ++x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && x > 0 && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT)) {
        draw = WALKING_LEFT;
        --x;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a)) {
        // todo automate in random with mod
        malo_appears = YES;
        x_malo = MAX_X;
    }

    frame = (frame + 1) % 4;

    // paint 'prota here'
    sp1_MoveSprAbs(catr1sp, &full_screen, (void*) cat_offset, y, x, 0, 0);

    // decide new FSM draw status
    if (draw == NONE && frame == 3) {
        cat_offset = BORED;
    } else if (draw == WALKING_RIGHT) {
        if (frame < 2) {
            cat_offset = RIGHTC1;
        } else if (frame < 4) {
            cat_offset = RIGHTC2;
        }
        draw = NONE;
    } else if (draw == WALKING_LEFT) {
        if (frame < 2) {
            cat_offset = LEFTC1;
        } else if (frame < 4) {
            cat_offset = LEFTC2;
        }
        draw = NONE;
    } else if (draw == JUMPING) {
        y--;

        if(draw_additional == JUMP_RIGHT) {
            ++x;
            cat_offset = JRIGHTC1;
        }  else if(draw_additional == JUMP_LEFT && x > 0) {
            --x;
            cat_offset = JLEFTC1;
        } else {
            cat_offset = JUMPINGC1;
        }

        if (initial_jump_y - y >= 8 || x > 28) {
            draw = FALLING;
            draw_additional = NONE;
        }
    } else if (draw == FALLING) {
        ++y;
        cat_offset = JUMPINGC1;

        // detect falling over bin
        if(bin_places[x] > 0 && y == 17) {
            // stop falling
            draw = NONE;
            draw_additional = CAT_IN_BIN;
            // store that it is on first bin pos so collide will trollcat is easier
            cat_in_bin = x - (bin_places[x] - 1);
        }

        if(y == FLOOR_Y) {
            draw = NONE;
            cat_offset = BORED;
        }
    }

    // cat falls appart from bin
    if (draw_additional == CAT_IN_BIN && y < FLOOR_Y && cat_in_bin != NONE) {
        if (bin_places[x] == NONE) {
            draw = FALLING;
            draw_additional = NONE;
            cat_in_bin = NONE;
        }
    }

    // time for doggy checks
    if (draw != FIGHTING && malo_appears == YES) {
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);

        --x_malo;

        if (x_malo <= 0) {
            malo_appears = NONE;
            x_malo = 33;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }

        if (frame < 2) {
            dog_offset = DOG1;
        } else if (frame < 4) {
            // todo fighting will be 49 + 48
            dog_offset = DOG2;
        }

        // detects collission malo->misifu
        if( abs(x - x_malo) < 3 && y > 18) {
            malo_appears = NONE;
            draw = FIGHTING;
            y = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            x = 33;
        }
    }

    if (draw == FIGHTING) {
        if (frame < 2) {
            dog_offset = DOGFIGHTING1;
        } else if (frame < 4) {
            dog_offset = DOGFIGHTING2;
        }

        --anim_frames;
        if (anim_frames <= 0) {
            draw = NONE;
            malo_appears = NONE;
            x_malo = 33;
            x = 0;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
            // todo remove one live
        } else {
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }
    }

    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

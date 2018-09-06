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
  struct sp1_ss  *bincatsp = NULL;

  unsigned char x, y, draw, frame, frame_malo, initial_jump_y, draw_additional;
  unsigned char x_malo;
  unsigned char bincat_appears = NONE;
  unsigned char enemy_apears = NONE;
  unsigned char bincat_in_bin = NONE;
  unsigned int  cat_offset;
  unsigned char dog_offset;
  // keeps animation frames when something takes longer
  unsigned char anim_frames = 0;
  unsigned char anim_frames_bincat = 0;
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
  draw_additional = NONE;
  cat_offset = RIGHTC1;
  dog_offset = DOG1;

  while(1)
  {
    // check if dog should appear
    if (enemy_apears != YES && first_keypress != NONE) {
        enemy_apears = rand() % 500;
    }
    // checks if bincat should appear and where
    if (bincat_appears != YES && first_keypress != NONE) {
        bincat_in_bin = rand() % 32;
        // less probable
        if(enemy_apears == 1 && bin_places[bincat_in_bin] == 1) {
            bincat_appears = YES;
            bincatsp = add_sprite_bincat();
            anim_frames_bincat = 20;
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, 16, bincat_in_bin, 0, 0);

            // cat falls if cat_in_bin is the same of bincat_in_bin
            // todo not working
            if (bincat_in_bin == cat_in_bin) {
                draw = FALLING;
            }
        } else {
            bincat_in_bin = NONE;
        }
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
        draw = FALLING;
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
        } else if(y == 12) {
            draw = NONE;
            draw_additional = CAT_IN_FENCE;
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
    if (draw != FIGHTING && enemy_apears == YES) {
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);

        --x_malo;

        if (x_malo <= 0) {
            enemy_apears = NONE;
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
            enemy_apears = NONE;
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
            enemy_apears = NONE;
            x_malo = 33;
            x = 0;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
            // todo remove one live
        } else {
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }
    }
    // delete bincat after some frames
    if (bincat_appears == YES) {
        --anim_frames_bincat;
        if (anim_frames_bincat < 1 && bincatsp != NULL) {
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, 16, 33, 0, 0);
            sp1_DeleteSpr_fastcall(bincatsp);
            bincat_appears = NONE;
            bincat_in_bin = 0;
        }
    }

    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

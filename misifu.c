#pragma output REGISTER_SP = 0xD000


#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>
#include <input.h>
#include <level1.h>

extern uint8_t abs2(uint8_t v);

struct sp1_Rect full_screen = {0, 0, 32, 24};


struct row_clothes {
    struct sp1_ss* sp;
    uint8_t col;
};

int main()
{
  struct sp1_ss  *catr1sp;
  struct sp1_ss  *dogr1sp;
  struct sp1_ss  *bincatsp = NULL;

  // row1 clothes
  //struct sp1_ss* clothesrow1[] = {NULL, NULL, NULL, NULL};
  //uint8_t clothescols[] = {1, 10, 18, 26};

  struct row_clothes row1clothes[4];


  uint8_t x_prota, y_prota, draw, frame, frame_malo, initial_jump_y, draw_additional;
  uint8_t x_malo;
  uint8_t bincat_appears = NONE;
  uint8_t enemy_apears = NONE;
  uint8_t row1_moving = NONE;
  uint8_t bincat_in_bin = NONE;
  unsigned int  cat_offset;
  uint8_t dog_offset;
  // keeps animation frames when something takes longer
  uint8_t anim_frames = 0;
  uint8_t anim_frames_bincat = 0;
  uint8_t cat_in_bin = NONE;

  uint8_t first_keypress = NONE;

  uint8_t index = 0;

  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );

  print_background();

  sp1_Invalidate(&full_screen);

  catr1sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();
  bincatsp = add_sprite_bincat();


  // row 1 clothes
  row1clothes[0].col = 1;
  row1clothes[0].sp = add_sprite_clothes1();
  row1clothes[1].col = 10;
  row1clothes[1].sp = add_sprite_clothes2();
  row1clothes[2].col = 18;
  row1clothes[2].sp = add_sprite_clothes1();
  row1clothes[3].col = 26;
  row1clothes[3].sp = add_sprite_clothes2();

  draw = NONE;

  x_prota=0;
  y_prota=FLOOR_Y;
  x_malo = 22;
  frame = 0;
  frame_malo = 0;
  initial_jump_y = 0;
  draw_additional = NONE;
  cat_offset = RIGHTC1;
  dog_offset = DOG1;

  row1_moving = 10;


  while(1)
  {
    // move clothes to the right
    if (rand() % 50 == 1 && row1_moving == NONE) {
        row1_moving = 5;
    } else if (row1_moving != NONE) {
        --row1_moving;
        // check if clothes should move
        for (index = 0; index != 4; ++index) {
            row1clothes[index].col = (row1clothes[index].col + 1) % 30;
            sp1_MoveSprAbs(row1clothes[index].sp, &full_screen, 0, 10, row1clothes[index].col, 0, 0);
        }
    }

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
            anim_frames_bincat = 20;

            if (bincat_in_bin == HIGHER_BIN_X) {
                // reused as row and also number of frames appearing
                anim_frames_bincat = 15;
            } else {
                anim_frames_bincat = 17;
            }
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, anim_frames_bincat, bincat_in_bin, 0, 0);
            anim_frames_bincat = 40;

            // cat falls if cat_in_bin is the same of bincat_in_bin
            if (bincat_in_bin == cat_in_bin) {
                draw = FALLING;
            }
        } else {
            bincat_in_bin = NONE;
        }
    }
    
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (y_prota > 0) && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT || draw == CAT_IN_ROPE) ) {
        draw = JUMPING;
        cat_in_bin = NONE;
        initial_jump_y = y_prota;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && x_prota<28) {
            draw_additional = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && x_prota>0) {
            draw_additional = JUMP_LEFT;
        } else {
            draw_additional = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && x_prota<28 && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT || draw == CAT_IN_ROPE)) {
        if (first_keypress == NONE) {
            first_keypress = frame;
            srand(first_keypress);
        }
        if (draw != CAT_IN_ROPE) {
            draw = WALKING_RIGHT;
        } else {
            if (frame < 2) {
              cat_offset = JUMPINGC1;
            } else if (frame < 4) {
              cat_offset = JUMPINGC2;
            }
        }
        ++x_prota;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && x_prota > 0 && (draw == NONE || draw == WALKING_LEFT || draw == WALKING_RIGHT || draw == CAT_IN_ROPE)) {
        if (draw != CAT_IN_ROPE) {
            draw = WALKING_LEFT;
        } else {
            if (frame < 2) {
              cat_offset = JUMPINGC1;
            } else if (frame < 4) {
              cat_offset = JUMPINGC2;
            }
        }
        --x_prota;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a) && y_prota < FLOOR_Y) {
        draw = FALLING;
        cat_in_bin = NONE;
    }

    frame = (frame + 1) % 4;

    // paint 'prota here'
    sp1_MoveSprAbs(catr1sp, &full_screen, (void*) cat_offset, y_prota, x_prota, 0, 0);

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
        y_prota--;

        if(draw_additional == JUMP_RIGHT) {
            ++x_prota;
            cat_offset = JRIGHTC1;
        }  else if(draw_additional == JUMP_LEFT && x_prota > 0) {
            --x_prota;
            cat_offset = JLEFTC1;
        } else {
            cat_offset = JUMPINGC1;
        }

        if (y_prota == 1) {
            y_prota = 1;
            draw = CAT_IN_ROPE;
        } else if (initial_jump_y - y_prota == 5 || x_prota > 28) {
            draw = FALLING;
            draw_additional = NONE;
        }
    } else if (draw == FALLING) {
        ++y_prota;
        cat_offset = JUMPINGC1;

        // detect falling over bin
        if(bin_places[x_prota] > 0 && (y_prota == 16 || y_prota == 18) ) {
            cat_in_bin = x_prota - (bin_places[x_prota] - 1);

            if (cat_in_bin == HIGHER_BIN_X && y_prota == 16) {
                // stop falling
                draw = NONE;
                draw_additional = CAT_IN_BIN;
            } else if (cat_in_bin != HIGHER_BIN_X && y_prota == 18) {
                draw = NONE;
                draw_additional = CAT_IN_BIN;

            }
            // store that it is on first bin pos so collide will trollcat is easier
        } else if(y_prota == 13) {
            draw = NONE;
            draw_additional = CAT_IN_FENCE;
        // now check ropes TODO check ropes clothes are not colliding
        } else if(y_prota == 9) {
            draw = CAT_IN_ROPE;
        } else if(y_prota == 5) {
            draw = CAT_IN_ROPE;
        }

        if(y_prota >= FLOOR_Y) {
            y_prota = FLOOR_Y;
            draw = NONE;
            cat_offset = BORED;
        }
    }

    // cat falls appart from bin
    if (draw_additional == CAT_IN_BIN && y_prota < FLOOR_Y && cat_in_bin != NONE) {
        if (bin_places[x_prota] == NONE) {
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
        if( abs(x_prota - x_malo) < 3 && y_prota > 18) {
            enemy_apears = NONE;
            draw = FIGHTING;
            y_prota = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            x_prota = 33;
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
            x_prota = 0;
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
            // todo remove one live
        } else {
            sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
        }
    }

    // delete bincat after some frames
    if (bincat_appears == YES) {
        --anim_frames_bincat;

        // cat falls if cat_in_bin is the same of bincat_in_bin
        if (bincat_in_bin == cat_in_bin) {
            draw = FALLING;
        }

        if (anim_frames_bincat < 1 && bincatsp != NULL) {
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, 16, 33, 0, 0);
            bincat_appears = NONE;
            bincat_in_bin = 0;
        }
    }

    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

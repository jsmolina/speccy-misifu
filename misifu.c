#pragma output REGISTER_SP = 0xD000


#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>
#include <input.h>
#include <level1.h>

struct sp1_Rect full_screen = {0, 0, 32, 24};



int main()
{
  zx_border(INK_BLACK);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_WHITE | PAPER_MAGENTA,
                  ' ' );

  print_background();

  sp1_Invalidate(&full_screen);

  misifu.in_bin = NONE;
  misifu.sp = add_sprite_protar1();
  misifu.x = 0;
  misifu.y = FLOOR_Y;
  misifu.initial_jump_y = 0;
  misifu.draw_additional = NONE;
  misifu.offset = RIGHTC1;
  misifu.state = NONE;

  dogr1sp = add_sprite_dogr1();
  bincatsp = add_sprite_bincat();

  aux_object.sp = add_sprite_auxiliar();
  aux_object.x = 0;
  aux_object.y = 0;


  // row 1 clothes
  row1clothes[0].col = 1;
  row1clothes[0].sp = add_sprite_clothes1();
  row1clothes[1].col = 10;
  row1clothes[1].sp = add_sprite_clothes2();
  row1clothes[2].col = 18;
  row1clothes[2].sp = add_sprite_clothes1();
  row1clothes[3].col = 26;
  row1clothes[3].sp = add_sprite_clothes2();

  // row 2 clothes
  row2clothes[0].col = 5;
  row2clothes[0].sp = add_sprite_clothes1();
  row2clothes[1].col = 18;
  row2clothes[1].sp = add_sprite_clothes2();

  x_malo = 22;
  frame = 0;
  dog_offset = DOG1;

  row1_moving = 10;


  while(1)
  {
    random_value = rand() % 500;

    // check keys
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (misifu.y > 0) && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT || misifu.state == CAT_IN_ROPE) ) {
        misifu.state = JUMPING;
        misifu.in_bin = NONE;
        misifu.initial_jump_y = misifu.y;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && misifu.x < 28) {
            misifu.draw_additional = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && misifu.x>0) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && misifu.x < 28 && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT)) {
        if (first_keypress == NONE) {
            first_keypress = random_value;
            srand(first_keypress);
        }
        misifu.state = WALKING_RIGHT;
        ++misifu.x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && misifu.x > 0 && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT)) {
        misifu.state = WALKING_LEFT;
        --misifu.x;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a) && misifu.y < FLOOR_Y) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }

    // now take decisions
    // move clothes to the right
    if (random_value % 50 == 1 && row1_moving == NONE) {
        row1_moving = 5;
    } else if (row1_moving != NONE) {
        --row1_moving;
        // check if clothes should move
        for (index = 0; index != 4; ++index) {
            row1clothes[index].col = (row1clothes[index].col + 1) % 30;
            sp1_MoveSprAbs(row1clothes[index].sp, &full_screen, 0, 10, row1clothes[index].col, 0, 0);

            if(misifu.draw_additional == CAT_IN_ROPE1) {
                ++misifu.x;
            }
        }

        for (index = 0; index != 2; ++index) {
            --row2clothes[index].col;
            if (row2clothes[index].col < 2) {
                row2clothes[index].col = 28;
            }
            sp1_MoveSprAbs(row2clothes[index].sp, &full_screen, 0, 6, row2clothes[index].col, 0, 0);
            if(misifu.draw_additional == CAT_IN_ROPE2) {
                --misifu.x;
            }
        }

    }

    // decide if window should open
    // OPEN
    if (opened_window_frames == NONE) {
        opened_window = random_value % 120;
        if(opened_window < 12) {
            // makes the window to be opened for about 20 frames
            opened_window_frames = 50;
            paint_window(opened_window, PAPER_BLACK);
        }
    } else {
        --opened_window_frames;
    }
    // end of windows
    if (opened_window_frames == 1) {
        paint_window(opened_window, PAPER_CYAN);
        opened_window = NONE;
        opened_window_frames = NONE;
    }

    // check if dog should appear
    if (enemy_apears != YES && first_keypress != NONE) {
        enemy_apears = random_value % 500;
    }
    // checks if bincat should appear and where
    if (bincat_appears != YES && misifu.in_bin != NONE) {
        bincat_in_bin = bin_places2[rand() % 6];
        // less probable
        if(bincat_in_bin != NONE) {
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

            // cat falls if misifu.in_bin is the same of bincat_in_bin
            if (bincat_in_bin == misifu.in_bin) {
                misifu.state = FALLING;
            }
        } else {
            bincat_in_bin = NONE;
        }
    }

    // decide new FSM draw status
    if (misifu.state == NONE && frame == 3) {
        misifu.offset = BORED;
    } else if (misifu.state == WALKING_RIGHT) {
        if (frame < 2) {
            misifu.offset = RIGHTC1;
        } else if (frame < 4) {
            misifu.offset = RIGHTC2;
        }
        misifu.state = NONE;
    } else if (misifu.state == WALKING_LEFT) {
        if (frame < 2) {
            misifu.offset = LEFTC1;
        } else if (frame < 4) {
            misifu.offset = LEFTC2;
        }
        misifu.state = NONE;
    } else if (misifu.state == JUMPING) {
        --misifu.y;

        if(misifu.draw_additional == JUMP_RIGHT) {
            ++misifu.x;
            misifu.offset = JRIGHTC1;
        }  else if(misifu.draw_additional == JUMP_LEFT && misifu.x > 0) {
            --misifu.x;
            misifu.offset = JLEFTC1;
        } else {
            misifu.offset = JUMPINGC1;
        }

        if (misifu.y <= 1) {
            misifu.y = 1;
            misifu.state = CAT_IN_ROPE;
        } else if (misifu.initial_jump_y - misifu.y == 5 || misifu.x > 28) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
        }
    } else if (misifu.state == FALLING) {
        ++misifu.y;
        misifu.offset = JUMPINGC1;

        // detect falling over bin
        if(misifu.y == 16 || misifu.y == 18) {
            misifu.in_bin = is_in_bin(misifu.x);
            // store that it is on first bin pos so collide will bincat is easier
            //misifu.in_bin = misifu.x - (bin_places[misifu.x] - 1);
            if (misifu.in_bin != NONE) {
                if (misifu.in_bin == HIGHER_BIN_X && misifu.y == 16) {
                    // stop falling
                    misifu.state = NONE;
                    misifu.draw_additional = CAT_IN_BIN;
                } else if (misifu.in_bin != HIGHER_BIN_X && misifu.y == 18) {
                    misifu.state = NONE;
                    misifu.draw_additional = CAT_IN_BIN;

                }
            }
        } else if(misifu.y == 13) {
            misifu.state = NONE;
            misifu.draw_additional = CAT_IN_FENCE;
        // now check ropes TODO check ropes clothes are not colliding
        } else if(misifu.y == 9) {
            misifu.state = CAT_IN_ROPE;
            misifu.draw_additional = CAT_IN_ROPE1;
        } else if(misifu.y == 5) {
            misifu.state = CAT_IN_ROPE;
            misifu.draw_additional = CAT_IN_ROPE2;
        }

        if(misifu.y >= FLOOR_Y) {
            misifu.y = FLOOR_Y;
            misifu.state = NONE;
            misifu.offset = BORED;
        }
    } else if(misifu.state == CAT_IN_ROPE) {
        if(misifu.x >= MAX_X || misifu.x < 1) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
        }
    }

    // cat falls appart from bin
    if (misifu.draw_additional == CAT_IN_BIN && misifu.y < FLOOR_Y && misifu.in_bin != NONE) {
        if (is_in_bin(misifu.x) == NONE) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
            misifu.in_bin = NONE;
        }
    }

    // time for doggy checks
    if (misifu.state != FIGHTING && enemy_apears == YES) {
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
        if( abs(misifu.x - x_malo) < 3 && misifu.y > 18) {
            enemy_apears = NONE;
            misifu.state = FIGHTING;
            misifu.y = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            misifu.x = 33;
        }
    }

    if (misifu.state == FIGHTING) {
        if (frame < 2) {
            dog_offset = DOGFIGHTING1;
        } else if (frame < 4) {
            dog_offset = DOGFIGHTING2;
        }

        --anim_frames;
        if (anim_frames < 1) {
            misifu.state = NONE;
            misifu.x = 0;
            enemy_apears = NONE;
            x_malo = 33;
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
        if (bincat_in_bin == misifu.in_bin) {
            misifu.state = FALLING;
            misifu.in_bin = NONE;
        }

        if (anim_frames_bincat < 1 && bincatsp != NULL) {
            sp1_MoveSprAbs(bincatsp, &full_screen, (void*)1, 16, 33, 0, 0);
            bincat_appears = NONE;
            bincat_in_bin = 0;
        }
    }


    frame = (frame + 1) % 4;

    // paint 'prota here'
    sp1_MoveSprAbs(misifu.sp, &full_screen, (void*) misifu.offset, misifu.y, misifu.x, 0, 0);


    z80_delay_ms(50);
    sp1_UpdateNow();
  }
}

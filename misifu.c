#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include <intrinsic.h> // for intrinsic_di()
#include <sound.h> // for bit_beepfx()
#include <string.h>
#include "int.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "defines.h"
#include "ay/ay_music.h"
#include "ay/vt_sound.h"

void check_keys()
{
    // checks keys
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (misifu.y > level_x_min[level]) && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT || misifu.state == CAT_IN_ROPE || misifu.state ==CAT_ON_HIGH) ) {
        misifu.state = JUMPING;
        misifu.in_bin = NONE;
        misifu.initial_jump_y = misifu.y;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && misifu.x < level_x_max[level]) {
            misifu.draw_additional = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && misifu.x > level_x_min[level]) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && misifu.x < level_x_max[level] && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        if (first_keypress == NONE) {
            first_keypress = tick;
            srand(first_keypress);
        }
        misifu.state = WALKING_RIGHT;
        ++misifu.x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && misifu.x > level_x_min[level] && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        misifu.state = WALKING_LEFT;
        --misifu.x;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a) && misifu.y < FLOOR_Y) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }

    if (in_key_pressed(IN_KEY_SCANCODE_3)) {
        level = 3;
        print_background_level3();
        sp1_UpdateNow();
    } else if (in_key_pressed(IN_KEY_SCANCODE_1)) {
        level = 1;
        print_background_lvl1();
        sp1_UpdateNow();
    } else if (in_key_pressed(IN_KEY_SCANCODE_2)) {
        level = 2;
        print_background_level2();
        sp1_UpdateNow();
    }
}


void dog_checks() {
// time for doggy checks
    if (misifu.state != FIGHTING && enemy_apears == YES) {

        --x_malo;


        if (frame < 2) {
            dog_offset = DOG1;
        } else if (frame < 4) {
            // todo fighting will be 49 + 48
            dog_offset = DOG2;
        }

        // detects collission malo->misifu
        if (x_malo <= 0) {
            enemy_apears = NONE;
            x_malo = 33;
        } else if( abs(misifu.x - x_malo) < 3 && misifu.y > 18) {
            enemy_apears = NONE;
            misifu.state = FIGHTING;
            misifu.y = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            misifu.x = 33;
        }
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);

    }

    if (misifu.state == FIGHTING) {
        if (frame < 2) {
            dog_offset = DOGFIGHTING1;
        } else if (frame < 4) {
            dog_offset = DOGFIGHTING2;
        }

        --anim_frames;
        if (anim_frames == 0) {
            loose_a_live();
            reset_misifu_position();
            enemy_apears = NONE;
            x_malo = 33;
            // todo remove one live
        }
        sp1_MoveSprAbs(dogr1sp, &full_screen, (void*) dog_offset, FLOOR_Y, x_malo, 0, 0);
    }
    // check if dog should appear
    if (enemy_apears != YES && first_keypress != NONE) {
        enemy_apears = random_value % 100;
    }

}



int main()
{
  initialize_ay();
  zx_border(INK_BLACK);

  // interrupt mode 2
  setup_int();

  add_sprites_for_all_levels();

  reset_misifu_position();

  x_malo = 22;
  frame = 0;
  dog_offset = DOG1;

  row1_moving = 10;

  if (level == 1) {
    print_background_lvl1();
  } else if(level == 2) {
    print_background_level2();
  } else if(level == 3) {
    print_background_level3();
  }

  intrinsic_ei();

  while(1)
  {
    check_keys();

    random_value = rand();

    if (level == 1) {
        move_clothes();
        anim_windows();
        check_bincat();
        dog_checks();
    } else if (level == 2) {
        mousies_dance_and_eat();
    } else if (level == 3) {
        throw_cupid_arrow();
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

        if(misifu.draw_additional == JUMP_RIGHT && misifu.x < level_x_max[level]) {
            ++misifu.x;
            misifu.offset = JRIGHTC1;
        }  else if(misifu.draw_additional == JUMP_LEFT && misifu.x > level_x_min[level]) {
            --misifu.x;
            misifu.offset = JLEFTC1;
        } else {
            misifu.offset = JUMPINGC1;
        }

        if (level == 1) {
            if (misifu.y <= 1) {
                misifu.y = 1;
                misifu.state = CAT_IN_ROPE;
                misifu.draw_additional = CAT_IN_ROPE3;
            }
        }

        if (misifu.initial_jump_y - misifu.y == 5 || misifu.x > 28) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
        }
    } else if (misifu.state == FALLING) {
        ++misifu.y;
        misifu.offset = JUMPINGC1;

        if (level == 1) {
            detect_fall_in_bin();
        } else if (level == 2) {
            detect_fall_in_hole_or_curtain();
        }

        if(misifu.y >= FLOOR_Y) {
            misifu.y = FLOOR_Y;
            misifu.state = NONE;
            misifu.offset = BORED;
        }
    } else if(misifu.state == CAT_IN_ROPE) {
        if(misifu.x >= 28 || misifu.x == 0) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
        }
    }

    if (level == 1) {
        // cat falls appart from bin
        if (misifu.draw_additional == CAT_IN_BIN && misifu.y < FLOOR_Y && misifu.in_bin != NONE) {
            if (is_in_bin(misifu.x) == NONE) {
                misifu.state = FALLING;
                misifu.draw_additional = NONE;
                misifu.in_bin = NONE;
            }
        }
    } else  if (level == 3) {
        detect_fall_in_hearts();
    }


    ++frame;
    if (frame >= 4) {
        frame = 0;
    }

    // paint 'prota here'
    sp1_MoveSprAbs(misifu.sp, &full_screen, (void*) misifu.offset, misifu.y, misifu.x, 0, 0);


    wait();
    sp1_UpdateNow();
  }
}

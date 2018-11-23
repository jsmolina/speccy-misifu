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

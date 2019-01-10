#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include <sound.h> // for bit_beepfx()
#include <string.h>
#include "int.h"
#include "level1.h"
#include "level2.h"
#include "level_last.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "defines.h"


int main()
{
  zx_border(INK_BLACK);

  // interrupt mode 2
  setup_int();

  add_sprites_for_all_levels();

  reset_misifu_position();

  x_malo = 22;
  frame = 0;
  dog_offset = DOG1;

  row1_moving = 10;

  print_background_lvl1();


  // bit_beep


  all_lives_lost();

  while(1)
  {
    if(misifu.state != SWIMMING) {
        check_keys();
    } else {
        check_swim();
    }

    random_value = rand();

    // todo move this to different loops
    if (level == 1) {
        move_clothes();
        anim_windows();
        check_bincat();
        dog_checks();
        detect_fall_in_window();
    } else if (level == 2) {
        level2_loop();
    } else if (level == 3) {
        level3_loop();
    } else if(level == 4) {
        level4_loop();
    } else if(level == 10) {
        throw_cupid_arrow();
    }

    check_fsm();

    if (level == 1) {
        // cat falls appart from bin
        if (misifu.draw_additional == CAT_IN_BIN && misifu.y < FLOOR_Y && misifu.in_bin != NONE) {
            if (is_in_bin(misifu.x) == NONE) {
                misifu.state = FALLING;
                misifu.draw_additional = NONE;
                misifu.in_bin = NONE;
            }
        }
    } else if(level == 2) {
        check_chair_and_table();
    } else  if (level == 3) {
        detect_fishtank_fall_in_hole_or_curtain();
    } else if (level == 5) {
        level5_loop();
    } else if(level == 6) {
        level6_loop();
    } else if (level == 10) {
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

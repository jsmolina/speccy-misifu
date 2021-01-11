#include <z80.h>
#include <intrinsic.h>
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
#include "level7.h"
#include "defines.h"
#include "ay/ay_music.h"


extern uint8_t cartoon0[];

void show_intro() {
   __asm
   extern enable_bank_n
   di
   ; no need of pointing it if no interrupt
   ld a,0x80
   ld i,a                      ; point I at uncontended bank

   ld a,6
   call enable_bank_n          ; bank 6 in top 16k, stack moved
    __endasm;
    memcpy(16384, cartoon0, 6912);
    __asm
    extern restore_bank_0
    call restore_bank_0

    ld a,0xd0
    ld i,a                      ; restore I

    ei
    __endasm;

}

int main()
{
  uint16_t misifu_sum_offset;
  // interrupt mode 2
  setup_int();
  add_sprites_for_all_levels();
  show_intro();

  ay_vt_init(pcspeaker_module);
  intrinsic_ei();

  while(!in_key_pressed(IN_KEY_SCANCODE_SPACE)) {
    // do nothing
  }

  reset_misifu_position();

  x_malo = 22;
  frame = 0;
  dog_offset = DOG1;

  row1_moving = 10;

  print_background_lvl1();

  // bit_beep
  lives = SONG_RESTART;
  all_lives_lost();
  lives = 5;

  while(1)
  {
    in = (joy)(&joy_keys);

    if(misifu.state != SWIMMING && level != 7) {
        check_keys();
    } else if(level == 7) {
        check_level7_keys();
    } else {
        check_swim();
    }

    random_value = rand();

    // todo move this to different loops
    if (level == 1) {
        level1_loop();
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
    } else if(level == 7) {
        level7_loop();
    } else if (level == 10) {
        detect_fall_in_hearts();
    }

    ++frame_big;
    if(frame_big > FRAME_MOST) {
        frame_big = 0;
    }

    ++frame;
    if (frame >= 4) {
        frame = 0;
        if (points < 254) {
            ++points;
        }
    }

    if(paws == 1) {
        in_wait_key();
        paws = 0;
    }

    // paint 'prota here'
    if (misifu.state == SWIMMING) {
        misifu_sum_offset = (int) sprite_swim1 + misifu.offset;
    } else {
        misifu_sum_offset = (int) sprite_protar1 + misifu.offset;
    }
    sp1_MoveSprAbs(misifu.sp, &full_screen, (int) misifu_sum_offset, misifu.y - 1, misifu.x, 0, 0);


    wait();
    sp1_UpdateNow();

  }
}

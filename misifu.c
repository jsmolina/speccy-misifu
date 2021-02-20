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
    if(window_shown == 0) {
        in = (joy)(&joy_keys);
        if(misifu.state != SWIMMING && level != 7) {
            check_keys();
        } else if(level == 7) {
            check_level7_keys();
        } else {
            check_swim();
        }

        random_value = rand();

        check_fsm();

        if (level == 1) {
            level1_loop();
            // cat falls appart from bin
            if (misifu.draw_additional == CAT_IN_BIN && misifu.y < FLOOR_Y && misifu.in_bin != NONE) {
                if (is_in_bin(misifu.x) == NONE) {
                    misifu.state = FALLING;
                    misifu.draw_additional = NONE;
                    misifu.in_bin = NONE;
                }
            }
        } else if(level == 2) {
            detect_fall_in_table(0);
            detect_fall_in_chair(22, 1);
            level2_loop();
        } else  if (level == 3) {
            level3_loop();
        } else if(level == 4) {
            level4_loop();
        } else if (level == 5) {
            level5_loop();
        } else if(level == 6) {
            level6_loop();
        } else if(level == 7) {
            level7_loop();
        } else if (level == 10) {
            level10_loop();
        }


        ++frame;
        if (frame >= 4) {
            frame = 0;
            if (level_time < 254) {
                ++level_time;
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
    } else {
        --window_shown;
        if(window_shown == 0) {
            get_out_of_level_generic(FALLING);
        }
    }
    sp1_MoveSprAbs(misifu.sp, &full_screen, (int) misifu_sum_offset, misifu.y - 1, misifu.x, 0, 0);


    wait();
    sp1_UpdateNow();

  }
}

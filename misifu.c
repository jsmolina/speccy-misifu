#pragma output REGISTER_SP = 0xD000
#pragma output CRT_ORG_CODE = 33200      // org of compile
#pragma output CLIB_EXIT_STACK_SIZE  = 0         // no atexit() functions
#pragma output CLIB_STDIO_HEAP_SIZE  = 0         // no memory for files
#pragma output CLIB_FOPEN_MAX = -1 // do not create open files list

#include <z80.h>
#include <stdlib.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <defines.h>
#include <input.h>
#include <intrinsic.h> // for intrinsic_di()
#include <sound.h> // for bit_beepfx()
#include <string.h>
#include "level1.h"
#include "level2.h"



unsigned char  joys;
udk_t          joykeys;        // holds keys selected for keyboard joystick

#ifdef __SDCC
uint16_t (*joyfunc)(udk_t *);  // pointer to joystick function
#endif

#ifdef __SCCZ80
void *joyfunc;                 // pointer to joystick function
#endif



void check_keys() {
    joys = (joyfunc) (&joykeys);
    // checks keys
    // allow jump in directions
    if ((IN_STICK_UP & joys) && (misifu.y > 0) && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT || misifu.state == CAT_IN_ROPE) ) {
        misifu.state = JUMPING;
        misifu.in_bin = NONE;
        misifu.initial_jump_y = misifu.y;

        if((IN_STICK_RIGHT & joys) && misifu.x < 28) {
            misifu.draw_additional = JUMP_RIGHT;
        } else if((IN_STICK_LEFT & joys) && misifu.x>0) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_UP;
        }
    } else if ((IN_STICK_RIGHT & joys)   && misifu.x < 28 && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT)) {
        if (first_keypress == NONE) {
            first_keypress = random_value;
            srand(first_keypress);
        }
        misifu.state = WALKING_RIGHT;
        ++misifu.x;
    } else if((IN_STICK_LEFT & joys)  && misifu.x > 0 && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT)) {
        misifu.state = WALKING_LEFT;
        --misifu.x;
    } else if ((IN_STICK_DOWN & joys)  && misifu.y < FLOOR_Y) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }
}


void reset_misifu_position() {
  misifu.in_bin = NONE;
  misifu.x = 0;
  misifu.y = FLOOR_Y;
  misifu.initial_jump_y = 0;
  misifu.draw_additional = NONE;
  misifu.offset = RIGHTC1;
  misifu.state = NONE;
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


// Function to Set Up Keyboard as a Joystick

void setupkeyboard(void)
{
   joyfunc = in_stick_keyboard;

   joykeys.fire  = IN_KEY_SCANCODE_SPACE;
   joykeys.left  = IN_KEY_SCANCODE_o;
   joykeys.right = IN_KEY_SCANCODE_p;
   joykeys.up    = IN_KEY_SCANCODE_q;
   joykeys.down  = IN_KEY_SCANCODE_a;
}

int main()
{
   // interrupts are already disabled by the CRT
  im2_init((void *)0xd000); // place z80 in im2 mode with interrupt vector table located at 0xd000
  memset((void *)0xd000, 0xd1, 257); // initialize 257-byte im2 vector table with all 0xd1 bytes
  z80_bpoke(0xd1d1, 0xfb);    // POKE instructions at address 0xd1d1 (interrupt service routine entry)
  z80_bpoke(0xd1d2, 0xed);
  z80_bpoke(0xd1d3, 0x4d);    // instructions for EI; RETI

  intrinsic_ei();             // enable interrupts without impeding optimizer


  zx_border(INK_BLACK);

  if (level == 1) {
    print_background_lvl1();
  } else if(level == 2) {
    print_background_level2();
  }



  misifu.sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();
  bincatsp = add_sprite_bincat();

  aux_object.sp = add_sprite_auxiliar();
  aux_object.x = 0;
  aux_object.y = 0;
  aux_object.offset = RIGHTC1;

  reset_misifu_position();

  add_row_clothes();

  x_malo = 22;
  frame = 0;
  dog_offset = DOG1;

  row1_moving = 10;


   // Set up Joystick/Keyboard

  joys = 0;
  setupkeyboard();


  while(1)
  {
    random_value = rand();

    check_keys();
    if (level == 1) {
        move_clothes();
        anim_windows();
        check_bincat();
        dog_checks();
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

    // cat falls appart from bin
    if (misifu.draw_additional == CAT_IN_BIN && misifu.y < FLOOR_Y && misifu.in_bin != NONE) {
        if (is_in_bin(misifu.x) == NONE) {
            misifu.state = FALLING;
            misifu.draw_additional = NONE;
            misifu.in_bin = NONE;
        }
    }


    frame = (frame + 1) % 4;

    // paint 'prota here'
    sp1_MoveSprAbs(misifu.sp, &full_screen, (void*) misifu.offset, misifu.y, misifu.x, 0, 0);


    z80_delay_ms(20);
    sp1_UpdateNow();
  }
}

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>


#define BIN_Y1 15
#define BIN_Y2 16
#define NO_DRAW 0
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define FIGHTING 5
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#define FLOOR_Y 21
#define DELTA 1

#define IN_KEY_SCANCODE_o 0x2df
#define IN_KEY_SCANCODE_p 0x1df
#define IN_KEY_SCANCODE_q 0x1fb
#define IN_KEY_SCANCODE_a 0x1fd
#define IN_KEY_SCANCODE_SPACE 0x017f


extern unsigned char sprite_protar1[];
extern unsigned char sprite_protar2[];
extern unsigned char sprite_protar3[];
extern unsigned char sprite_protar4[];



struct sp1_ss * add_sprite_protar1() {
  struct sp1_ss * sp;
   sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_protar1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  return sp;
}

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>

#define NONE 0
#define YES 1
#define BIN_Y1 15
#define BIN_Y2 16
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define FIGHTING 5
#define CAT_IN_ROPE 6
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#define CAT_IN_BIN 3
#define CAT_IN_FENCE 4
#define FLOOR_Y 21
#define RIGHTC1 1
#define RIGHTC2 65
#define LEFTC1 129
#define LEFTC2 193
#define JLEFTC1 257
#define JRIGHTC1 321
#define JUMPINGC1 385
#define BORED 449
#define JUMPINGC2 513

#define DOG1 1
#define DOG2 49
#define DOGFIGHTING1 97
#define DOGFIGHTING2 145

#define MAX_X 32

#define IN_KEY_SCANCODE_o 0x2df
#define IN_KEY_SCANCODE_p 0x1df
#define IN_KEY_SCANCODE_q 0x1fb
#define IN_KEY_SCANCODE_a 0x1fd
#define IN_KEY_SCANCODE_SPACE 0x017f


extern unsigned char sprite_protar1[];
extern unsigned char sprite_protar2[];
extern unsigned char sprite_protar3[];
extern unsigned char sprite_protar4[];

extern unsigned char sprite_dog1[];
extern unsigned char sprite_dog2[];
extern unsigned char sprite_dog3[];
extern unsigned char sprite_dog4[];

extern unsigned char sprite_bincat1[];
extern unsigned char sprite_bincat2[];
extern unsigned char sprite_bincat3[];

extern unsigned char sprite_clothes1[];
extern unsigned char sprite_clothes2[];
extern unsigned char sprite_clothes3[];
extern unsigned char sprite_clothes4[];
extern unsigned char sprite_clothes5[];
extern unsigned char sprite_clothes6[];
extern unsigned char sprite_clothes7[];
extern unsigned char sprite_clothes8[];


extern unsigned char sprite_clothes21[];
extern unsigned char sprite_clothes22[];
extern unsigned char sprite_clothes23[];
extern unsigned char sprite_clothes24[];
extern unsigned char sprite_clothes25[];



void initialiseColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_BLACK;
}


void initialiseDogColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_BLUE;
}

void initialiseClothesColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_WHITE;
}


inline struct sp1_ss * add_sprite_protar1() {
  struct sp1_ss * sp;
   sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_protar1, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar2, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar3, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar4, 1);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

inline struct sp1_ss * add_sprite_dogr1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_dog1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseDogColour);

  return sp;
}

inline struct sp1_ss * add_sprite_bincat() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_bincat1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_bincat2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_bincat3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

struct sp1_ss * add_sprite_clothes1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_clothes1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes4, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes5, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes6, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes7, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes8, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseClothesColour);

  return sp;
}

inline struct sp1_ss * add_sprite_clothes2() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_clothes21, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes22, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes23, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes24, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes25, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseClothesColour);

  return sp;
}

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

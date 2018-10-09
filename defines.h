#ifndef _DEFINES_H
#define _DEFINES_H

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
#define CAT_IN_ROPE1 7
#define CAT_IN_ROPE2 8
#define CAT_IN_ROPE3 9
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#define CAT_IN_BIN 3
#define CAT_IN_FENCE 4
#define HIGHER_BIN_X 5
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

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define DOG1 1
#define DOG2 49
#define DOGFIGHTING1 97
#define DOGFIGHTING2 145

#define MAX_X 32

struct sp1_Rect full_screen = {0, 0, 32, 24};


extern uint8_t sprite_protar1[];
extern uint8_t sprite_protar2[];
extern uint8_t sprite_protar3[];
extern uint8_t sprite_protar4[];

extern uint8_t sprite_dog1[];
extern uint8_t sprite_dog2[];
extern uint8_t sprite_dog3[];
extern uint8_t sprite_dog4[];

extern uint8_t sprite_bincat1[];
extern uint8_t sprite_bincat2[];
extern uint8_t sprite_bincat3[];

extern uint8_t sprite_clothes1[];
extern uint8_t sprite_clothes2[];
extern uint8_t sprite_clothes3[];
extern uint8_t sprite_clothes4[];
extern uint8_t sprite_clothes5[];
extern uint8_t sprite_clothes6[];
extern uint8_t sprite_clothes7[];
extern uint8_t sprite_clothes8[];


extern uint8_t sprite_clothes21[];
extern uint8_t sprite_clothes22[];
extern uint8_t sprite_clothes23[];
extern uint8_t sprite_clothes24[];
extern uint8_t sprite_clothes25[];

extern uint8_t auxiliar1[];
extern uint8_t auxiliar2[];
extern uint8_t auxiliar3[];
extern uint8_t auxiliar4[];

struct prota misifu;
struct freesprite aux_object;
struct sp1_ss  *dogr1sp;
struct sp1_ss  *bincatsp = NULL;

struct row_clothes row1clothes[2];
struct row_clothes row2clothes[2];
unsigned char udg_win2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


// shared vars
uint8_t x, y;


// game required vars
uint8_t frame;
uint8_t x_malo;
uint8_t bincat_appears = NONE;
uint8_t enemy_apears = NONE;
uint8_t row1_moving = NONE;
uint8_t bincat_in_bin = NONE;
uint8_t dog_offset;
// keeps animation frames when something takes longer
uint8_t anim_frames = 0;
uint8_t anim_frames_bincat = 0;

uint8_t first_keypress = NONE;

uint8_t idx = 0;

uint8_t random_value = 0;

uint8_t opened_window = NONE;
uint8_t opened_window_frames = NONE;
uint8_t level = 1;


// level 2
const uint8_t hole_empty[] = {0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c};
const uint8_t hole_mouse[] = {0x3c, 0x5a, 0xe7, 0xc3, 0xa5, 0xe7, 0x5a, 0x3c};
const uint8_t cheese2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t curtain[] = {0x7e, 0x9c, 0xe3, 0xff, 0xff, 0x7e, 0x9c, 0xe3};

const uint8_t wall1[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
const uint8_t wall2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
const uint8_t wall3[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
const uint8_t wall4[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

// level 1
const uint8_t udg_valla1[] = {0xff, 0x9f, 0x8f, 0x87, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla2[] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla3[] = {0xff, 0xe1, 0xe1, 0x81, 0x81, 0x81, 0x81, 0x81};
const uint8_t udg_valla4[] = {0xef, 0x8f, 0x83, 0x83, 0x83, 0x81, 0x81, 0x81};

const uint8_t cubo_down1[] = {0xab, 0xd5, 0xaa, 0xd5, 0xfe, 0x31, 0xe, 0x1};
const uint8_t cubo_down2[] = {0xff, 0x55, 0xaa, 0x55, 0xaa, 0xff, 0x0, 0xff};
const uint8_t cubo_down3[] = {0xa9, 0x57, 0xa5, 0x5b, 0xf3, 0x8c, 0xf8, 0x80};
const uint8_t cubo_middle1[] = {0x9e, 0xa5, 0xa5, 0xba, 0x9d, 0xcf, 0xb1, 0xde};
const uint8_t cubo_middle2[] = {0x0, 0xff, 0x52, 0xad, 0x52, 0xff, 0xff, 0x0};
const uint8_t cubo_middle3[] = {0x7d, 0xa9, 0xad, 0x5d, 0xfd, 0x7b, 0x8d, 0x7f};

const uint8_t cubotop1[] = {0x0, 0x0, 0x33, 0x4f, 0x9f, 0xbf, 0x9f, 0xcf};
const uint8_t cubotop2[] = {0x31, 0xff, 0x0, 0xe0, 0xfc, 0xff, 0xff, 0xff};
const uint8_t cubotop3[] = {0xb0, 0x58, 0x8b, 0x10, 0x0, 0xf8, 0xff, 0xfb};

const uint8_t udg_rope[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd2};
const uint8_t  udg_win1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2d}; // with rope
const uint8_t  udg_win3[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

const uint8_t udg_c[] = {0x62, 0x42, 0x4e, 0x4e, 0x4e, 0x62, 0x72, 0x7e};
const uint8_t udg_a[] = {0x72, 0x60, 0x4c, 0x40, 0x18, 0x12, 0x12, 0x7e};
const uint8_t udg_t[] = {0x60, 0x2, 0x12, 0x72, 0x78, 0x78, 0x78, 0x7e};


// variable used for free objects (e.g. kitchen object thrown from window)
uint8_t vertical_direction;
uint8_t horizontal_direction;

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


struct sp1_ss * add_sprite_protar1() {
  struct sp1_ss * sp;
   sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_protar1, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar2, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar3, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar4, 1);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

struct sp1_ss * add_sprite_dogr1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_dog1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseDogColour);

  return sp;
}

struct sp1_ss * add_sprite_bincat() {
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
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_clothes1, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes2, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes3, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes4, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes5, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes6, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes7, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes8, 2);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 2);

  sp1_IterateSprChar(sp, initialiseClothesColour);

  return sp;
}

struct sp1_ss * add_sprite_clothes2() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_clothes21, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes22, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes23, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes24, 2);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_clothes25, 2);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 2);

  sp1_IterateSprChar(sp, initialiseClothesColour);

  return sp;
}

struct sp1_ss * add_sprite_auxiliar() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)auxiliar1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 2);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}


struct row_clothes {
    struct sp1_ss* sp;
    uint8_t col;
};

struct prota {
    struct sp1_ss* sp;
    uint8_t x;
    uint8_t y;
    uint8_t initial_jump_y;
    uint8_t draw_additional;
    unsigned int  offset;
    uint8_t in_bin;
    uint8_t state;
};

struct freesprite {
    struct sp1_ss* sp;
    uint8_t  offset;
    uint8_t y;
    uint8_t x;
};

struct udgstruct {
    uint8_t y;
    uint8_t x;
};

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

#endif

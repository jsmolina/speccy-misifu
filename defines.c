#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include "defines.h"

struct sp1_Rect full_screen = {0, 0, 32, 24};

uint8_t level_x_max[4] = {0, 28, 28, 25};
uint8_t level_x_min[4] = {0, 0,  0,  3};


struct prota misifu;
struct freesprite aux_object;
struct sp1_ss  *dogr1sp;
struct sp1_ss  *bincatsp = NULL;

struct row_clothes row1clothes[2];
struct row_clothes row2clothes[2];
unsigned char udg_win2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


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
uint8_t idx_j;


uint8_t random_value = 0;

uint8_t opened_window = NONE;
uint8_t opened_window_frames = NONE;
uint8_t level = 1;

// level 3 hearts
const uint8_t heart1[] = {0x0, 0x66, 0xef, 0xc7, 0xf3, 0x3a, 0x0, 0x0};
const uint8_t heart2[] = {0x66, 0xef, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0};
const uint8_t cupid11[] = {0x0, 0x0, 0x0, 0xe, 0xf, 0x1f, 0x3f, 0x7f};
const uint8_t cupid12[] = {0x0, 0x0, 0x0, 0x7, 0x1f, 0xdf, 0xff, 0xff};
const uint8_t cupid13[] = {0x0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0x80, 0xd0};
const uint8_t cupid21[] = {0x7f, 0x7f, 0x7e, 0x38, 0x1, 0x1, 0x1, 0x33};
const uint8_t cupid22[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc};
const uint8_t cupid23[] = {0xd8, 0x9c, 0x8e, 0xee, 0xfe, 0xe6, 0x76, 0x1e};
const uint8_t cupid31[] = {0x3f, 0x6e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t cupid32[] = {0x78, 0x60, 0x60, 0xe0, 0xe0, 0x0, 0x0, 0x0};
const uint8_t cupid33[] = {0x7e, 0xf8, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0};

// hearts holes
uint8_t floor_holes[5][24];

const uint8_t floor_holes_defaults[][24] = {
    {1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1},
    {0,0,1,1,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1},
    {0,0,0,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1}};

// level 2 cheese
const uint8_t hole_empty[] = {0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c};
const uint8_t hole_mouse[] = {0x3c, 0x5a, 0xe7, 0xc3, 0xa5, 0xe7, 0x5a, 0x3c};
const uint8_t cheese2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t curtain[] = {0x7e, 0x9c, 0xe3, 0xff, 0xff, 0x7e, 0x9c, 0xe3};

const uint8_t wall1[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
const uint8_t wall2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
const uint8_t wall3[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
const uint8_t wall4[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

// level 1
struct udgstruct windows[14];
const uint8_t bin_places2[] = {NONE, 1, 5, 9, 20, 24};

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
// todo add udg for numbers (score, lives)

const uint8_t udg_c[] = {0x62, 0x42, 0x4e, 0x4e, 0x4e, 0x62, 0x72, 0x7e};
const uint8_t udg_a[] = {0x72, 0x60, 0x4c, 0x40, 0x18, 0x12, 0x12, 0x7e};
const uint8_t udg_t[] = {0x60, 0x2, 0x12, 0x72, 0x78, 0x78, 0x78, 0x7e};


// variable used for free objects (e.g. kitchen object thrown from window)
uint8_t vertical_direction;
uint8_t horizontal_direction;

static void initialiseColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_BLACK;
}


static void initialiseDogColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_BLUE;
}

static void initialiseClothesColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_WHITE;
}


static void initialisePinkColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_MAGENTA;
}



static struct sp1_ss * add_sprite_protar1() {
  struct sp1_ss * sp;
   sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_protar1, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar2, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar3, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_protar4, 1);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

static struct sp1_ss * add_sprite_dogr1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_dog1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_dog4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseDogColour);

  return sp;
}

static struct sp1_ss * add_sprite_bincat() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)sprite_bincat1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_bincat2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)sprite_bincat3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

static struct sp1_ss * add_sprite_clothes1() {
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

static struct sp1_ss * add_sprite_clothes2() {
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

static struct sp1_ss * add_sprite_auxiliar() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)auxiliar1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)auxiliar4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 2);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}


void add_sprites_for_all_levels() {
  misifu.sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();
  bincatsp = add_sprite_bincat();

  aux_object.sp = add_sprite_auxiliar();
  aux_object.x = 0;
  aux_object.y = 0;
  aux_object.offset = RIGHTC1;


  // row 1 clothes
  row1clothes[0].col = 1;
  row1clothes[0].sp = add_sprite_clothes2();
  row1clothes[1].col = 18;
  row1clothes[1].sp = add_sprite_clothes1();

  // row 2 clothes
  row2clothes[0].col = 1;
  row2clothes[0].sp = add_sprite_clothes1();
  row2clothes[1].col = 18;
  row2clothes[1].sp = add_sprite_clothes1();

}

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

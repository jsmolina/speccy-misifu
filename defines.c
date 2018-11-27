#include <z80.h>
#include <input.h>
#include <stdlib.h>
#include "int.h"
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <sound.h> // for bit_beepfx()
#include "defines.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"


struct sp1_Rect full_screen = {0, 0, 32, 24};

// 28 and 3 for level = 3
uint8_t level_x_max;
uint8_t level_x_min;


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
char left;
char right;
uint8_t eaten_items;
uint8_t frame;
uint8_t x_malo;
uint8_t bincat_appears = NONE;
uint8_t enemy_apears = NONE;
uint8_t row1_moving = NONE;
uint8_t bincat_in_bin = NONE;
uint8_t dog_offset;
// keeps animation frames when something takes longer
uint8_t anim_frames = 0;

// used for udg animations (e.g. heaven cats, eel, ...)
uint8_t udgxs[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t udgys[] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t first_keypress = NONE;

uint8_t idx = 0;
uint8_t idx_j;


uint8_t random_value = 0;

uint8_t opened_window = NONE;
uint8_t opened_window_frames = NONE;
uint8_t level = 1;
uint8_t lives = 5;
uint8_t repaint_lives = 0;
uint16_t points = 0;


// hearts holes
uint8_t floor_holes[5][24];


const uint8_t curtain[] = {0x81, 0x63, 0x1c, 0x0, 0x0, 0x81, 0x63, 0x1c};

const uint8_t wall1[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
const uint8_t wall2[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff};
const uint8_t wall3[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
const uint8_t wall4[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};



const uint8_t udg_sillaL[] = {0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70};
const uint8_t udg_sillaR[] = {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7};
const uint8_t udg_sillaLM[] = {0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x70, 0x70};
const uint8_t udg_sillaRM[] = {0xff, 0xff, 0xff, 0x7, 0x7, 0x7, 0x7, 0x7};

const uint8_t mesatop[] = {0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff};
const uint8_t mesapata[] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};

// level 1
struct udgstruct windows[14];
const uint8_t bin_places2[] = {NONE, 1, 5, 9, 20, 24};


// use tiles
const uint8_t catheaven1[] = {0x60, 0xc3, 0xc7, 0xef, 0x7e, 0x1e, 0x18, 0x1c};
const uint8_t catheaven2[] = {0x4, 0xcc, 0xea, 0xff, 0x7e, 0x1c, 0xc, 0xe};

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
  sp = sp1_CreateSpr(SP1_DRAW_OR1LB, SP1_TYPE_1BYTE, 3, (int)sprite_bincat1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_OR1,    SP1_TYPE_1BYTE, (int)sprite_bincat2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_OR1,    SP1_TYPE_1BYTE, (int)sprite_bincat3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_OR1RB,  SP1_TYPE_1BYTE, 0, 0);

  sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}


static struct sp1_ss * add_sprite_clothes2() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_XOR1LB, SP1_TYPE_1BYTE, 3, (int)sprite_clothes21, 2);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)sprite_clothes22, 2);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)sprite_clothes23, 2);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)sprite_clothes24, 2);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)sprite_clothes25, 2);

  sp1_AddColSpr(sp, SP1_DRAW_XOR1RB,  SP1_TYPE_1BYTE, 0, 2);

  sp1_IterateSprChar(sp, initialiseClothesColour);

  return sp;
}

static struct sp1_ss * add_sprite_auxiliar() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_XOR1LB, SP1_TYPE_1BYTE, 3, (int)auxiliar1, 0);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)auxiliar2, 0);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)auxiliar3, 0);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, (int)auxiliar4, 0);

  sp1_AddColSpr(sp, SP1_DRAW_XOR1RB,  SP1_TYPE_1BYTE, 0, 2);

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
  row1clothes[1].sp = add_sprite_clothes2();

  // row 2 clothes
  row2clothes[0].col = 1;
  row2clothes[0].sp = add_sprite_clothes2();
  row2clothes[1].col = 18;
  row2clothes[1].sp = add_sprite_clothes2();

}

void loose_a_live() {
    // todo make sound

    if(lives > 0) {
        --lives;
        bit_beepfx_di(BEEPFX_DROP_1);
    } else {
        // reached zero on lives
        lives = 5;
        points = 0;
        bit_beepfx_di(BEEPFX_BOOM_1);
    }
    repaint_lives = 1;
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

void print_room_walls(uint16_t paper_color, uint16_t ink_color) {
  sp1_TileEntry('F', wall1);
  sp1_TileEntry('G', wall2);
  sp1_TileEntry('H', wall3);
  sp1_TileEntry('I', wall4);

  sp1_TileEntry('J', curtain);
  sp1_TileEntry('N', udg_win2); // full square

  for(idx = 0; idx != 3; ++idx) {
    // upper left
    sp1_PrintAt( 3 + idx, idx,  INK_BLACK | paper_color, 'H');
    // down left diagonal
    sp1_PrintAt( 20 - idx, idx, INK_BLACK | paper_color, 'I');
    // upper right
    sp1_PrintAt( 5 - idx, 29 + idx,  INK_BLACK | paper_color, 'I');
    // down right
    sp1_PrintAt( 18 + idx, 29 + idx,  INK_BLACK | paper_color, 'H');
  }

  // draw vertical wall
  for (idx = 6; idx != 18; ++idx) {
    sp1_PrintAt( idx, 3, INK_BLACK | paper_color, 'F');
    sp1_PrintAt( idx, 29,  INK_BLACK | paper_color, 'F');
  }

  // draw horizontal wall
  for (idx = 3; idx != 29; ++idx) {
    sp1_PrintAt( 5, idx, INK_BLACK | paper_color, 'G');
    sp1_PrintAt( 17, idx, INK_BLACK | paper_color, 'G');
  }

  for (idx = 8; idx != 11; ++idx) {
    sp1_PrintAt( idx, 20, ink_color | paper_color, 'J');
    sp1_PrintAt( idx, 21, ink_color | paper_color, 'J');

    // x=8, 9 and y=22-25
    if (idx != 10) {
        sp1_PrintAt( idx, 22,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 23,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 24,  PAPER_BLACK, 'N');
        sp1_PrintAt( idx, 25,  PAPER_BLACK, 'N');
    }

    sp1_PrintAt( idx, 26, ink_color | paper_color, 'J');
    sp1_PrintAt( idx, 27, ink_color | paper_color, 'J');
  }

}

// void page(uint8_t bank) {
//     GLOBAL_ZX_PORT_7FFD = 0x10+bank;
// 	IO_7FFD = 0x10 + bank;
// }

void check_keys()
{
    // checks keys
    // allow jump in directions
    if (in_key_pressed(IN_KEY_SCANCODE_q) && (misifu.y > level_x_min) && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT || misifu.state == CAT_IN_ROPE || misifu.state ==CAT_ON_HIGH) ) {
        misifu.state = JUMPING;
        misifu.in_bin = NONE;
        misifu.initial_jump_y = misifu.y;

        if(in_key_pressed(IN_KEY_SCANCODE_p) && misifu.x < level_x_max) {
            misifu.draw_additional = JUMP_RIGHT;
        } else if(in_key_pressed(IN_KEY_SCANCODE_o) && misifu.x > level_x_min) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_UP;
        }
    } else if (in_key_pressed(IN_KEY_SCANCODE_p)  && misifu.x < level_x_max && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        if (first_keypress == NONE) {
            first_keypress = tick;
            srand(first_keypress);
        }
        misifu.state = WALKING_RIGHT;
        ++misifu.x;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)  && misifu.x > level_x_min && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        misifu.state = WALKING_LEFT;
        --misifu.x;
    } else if (in_key_pressed(IN_KEY_SCANCODE_a) && misifu.y < FLOOR_Y) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }  else if (in_key_pressed(IN_KEY_SCANCODE_s)) {
        // todo only for testing collisions, remove later
        misifu.state = SWIMMING;
    }

    if (in_key_pressed(IN_KEY_SCANCODE_3)) {
        level = 3;
        print_background_level3();
    } else if (in_key_pressed(IN_KEY_SCANCODE_1)) {
        level = 1;
        print_background_lvl1();
    } else if (in_key_pressed(IN_KEY_SCANCODE_2)) {
        level = 2;
        print_background_level2();
    } else if (in_key_pressed(IN_KEY_SCANCODE_4)) {
        level = 5;
        print_background_level4();
    }
}

void check_swim() {
    if(in_key_pressed(IN_KEY_SCANCODE_q)) {
        --misifu.y;
    } else if(in_key_pressed(IN_KEY_SCANCODE_o)) {
        --misifu.x;
        misifu.offset = LEFTC1;
    } else if(in_key_pressed(IN_KEY_SCANCODE_p)) {
        ++misifu.x;
        misifu.offset = RIGHTC1;
    } else if(in_key_pressed(IN_KEY_SCANCODE_a)) {
        ++misifu.y;
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

static void stop_jump_if_needed(uint8_t max_jump) {
    if (misifu.initial_jump_y - misifu.y >= max_jump || misifu.x > 28) {
        misifu.state = FALLING;
        misifu.draw_additional = NONE;
    }
}

void check_fsm() {
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
    } else if (misifu.state == JUMPING_PUSHED){
        misifu.y = misifu.y - 2;
        if (misifu.draw_additional == JUMP_LEFT && misifu.x > 1) {
            misifu.x = misifu.x - 2;
        } else {
            misifu.x = misifu.x + 2;
        }
        stop_jump_if_needed(10);
    } else if (misifu.state == JUMPING) {
        --misifu.y;

        if(misifu.draw_additional == JUMP_RIGHT && misifu.x < level_x_max) {
            ++misifu.x;
            misifu.offset = JRIGHTC1;
        }  else if(misifu.draw_additional == JUMP_LEFT && misifu.x > level_x_min) {
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

        stop_jump_if_needed(5);
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
}

void define_silla_udgs() {
  sp1_TileEntry('Q', udg_sillaL);
  sp1_TileEntry('R', udg_sillaLM);
  sp1_TileEntry('S', udg_sillaRM);
  sp1_TileEntry('T', udg_sillaR);

  sp1_TileEntry('U', mesatop);
  sp1_TileEntry('V', mesapata);
}

void paint_chair(uint8_t row, uint8_t col, uint16_t paper_color, uint16_t ink_color) {
    sp1_PrintAt( row, col,  ink_color | paper_color, 'Q'); // L
    sp1_PrintAt( row + 1, col,  ink_color | paper_color, 'Q'); // L
    sp1_PrintAt( row + 2, col,  ink_color | paper_color, 'R'); // LM
    sp1_PrintAt( row + 2, col + 1,  ink_color | paper_color, 'S'); // RM
    sp1_PrintAt( row + 3, col,  ink_color | paper_color, 'Q'); // L
    sp1_PrintAt( row + 3, col + 1,  ink_color | paper_color, 'T'); // R

    sp1_PrintAt(row + 1, col + 4, ink_color |paper_color, 'U');
    sp1_PrintAt(row + 1, col + 5, ink_color |paper_color, 'U');
    sp1_PrintAt(row + 1, col + 6,  ink_color |paper_color, 'U');

    sp1_PrintAt(row + 2, col + 5,  ink_color |paper_color, 'V');
    sp1_PrintAt(row + 3, col + 5,  ink_color |paper_color, 'V');

}

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

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
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level_last.h"
#include "ay/ay_music.h"
#include <intrinsic.h> // for intrinsic_di()
#include <string.h>

#define UDG_WALL1 128
#define UDG_WALL2 129
#define UDG_WALL3 130
#define UDG_WALL4 131
#define UDG_CURTAIN 132
#define UDG_Q_BARRA_CORTINA 133
#define UDG_SILLAL 134
#define UDG_SILLALM 135
#define UDG_SILLARM 136
#define UDG_SILLAR 137
#define UDG_MESATOP 138
#define UDG_MESAPATA 139
#define UDG_MESASIDE 140
#define UDG_Q_MESABASE 141
#define UDG_WALL5 142
#define UDG_LAMP1 143
#define UDG_LAMP2 144
#define UDG_SILLA2_PARTE01 145
#define UDG_SILLA2_PARTE02 146
#define UDG_SILLA2_PARTE03 147
#define UDG_SILLA2_PARTE04 148
#define UDG_CUADRO_SUPERIOR_IZQUIERDA 149
#define UDG_CUADRO_SUPERIOR_DERECHA 150
#define UDG_CUADRO_INFERIOR_IZQUIERDA 151
#define UDG_CUADRO_INFERIOR_DERECHA 152

struct sp1_Rect full_screen = {0, 0, 32, 24};
uint8_t final_msg[] = {'l', 'o', 'v', 'e'};

// 28 and 3 for level = 3
uint8_t level_x_max;
uint8_t level_x_min;


struct prota misifu;
struct freesprite aux_object;
struct sp1_ss  *dogr1sp;
struct sp1_ss  *bincatsp = NULL;
struct sp1_ss  *birdsp = NULL;
struct sp1_ss  *fredsp = NULL;

const uint8_t heart2[] = {0x66, 0xef, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0};

#define ROOMS_TILES_LEN 25
#define ROOMS_TILES_BASE 128
#define UDG_WINDOWHOLE ROOMS_TILES_BASE + ROOMS_TILES_LEN

uint8_t rooms[] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // y:0, x:0 (128)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, // y:0, x:1 (129)
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, // y:0, x:2 (130)
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, // y:0, x:3 (131)
    0xc3, 0xff, 0xff, 0x3c, 0xc3, 0xff, 0xff, 0x3c, // y:0, x:4 (132)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0c, // y:0, x:5 (133)
    0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, // y:0, x:6 (134)
    0x77, 0x57, 0x77, 0x70, 0x70, 0x70, 0x70, 0x70, // y:0, x:7 (135)
    0xfe, 0xff, 0xff, 0x00, 0x07, 0x07, 0x07, 0x07, // y:0, x:8 (136)
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, // y:0, x:9 (137)
    0xff, 0xff, 0xff, 0x00, 0x18, 0x18, 0x18, 0x18, // y:0, x:10 (138)
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, // y:0, x:11 (139)
    0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, // y:0, x:12 (140)
    0x18, 0x18, 0x18, 0x18, 0x00, 0x3c, 0x7e, 0xff, // y:0, x:13 (141)
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, // y:0, x:14 (142)
    0xe7, 0x3c, 0xdb, 0x42, 0xdb, 0x3c, 0xe7, 0x18, // y:0, x:15 (143)
    0x00, 0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x38, // y:0, x:16 (144)
    0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, // y:0, x:17 (145)
    0xee, 0xea, 0xee, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, // y:0, x:18 (146)
    0x7f, 0xff, 0xff, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, // y:0, x:19 (147)
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, // y:0, x:20 (148)
    0xff, 0x80, 0xbf, 0xbc, 0xb8, 0xb3, 0xb4, 0xb1, // y:0, x:21 (149)
    0xff, 0x01, 0xfd, 0x3d, 0x1d, 0xcd, 0x2d, 0x0d, // y:0, x:22 (150)
    0xa5, 0xa7, 0xa6, 0x83, 0x84, 0x8f, 0x80, 0xff, // y:0, x:23 (151)
    0xa5, 0xe5, 0x65, 0xc1, 0x21, 0xf1, 0x01, 0xff, // y:0, x:24 (152)
};

uint8_t tiles_lvl1[] = {
    0x00, 0x01, 0x01, 0x7e, 0x00, 0x10, 0x10, 0xe7, // y:0, x:0 (128)
    0x00, 0x80, 0x04, 0x00, 0x08, 0x40, 0x01, 0x00, // y:0, x:1 (129)
    0x00, 0x00, 0x00, 0x26, 0x0b, 0x87, 0x10, 0x00, // y:0, x:2 (130)
    0x05, 0x0b, 0x05, 0x0b, 0x05, 0x03, 0x05, 0x0b, // y:0, x:3 (131)
    0xcf, 0x0f, 0x07, 0x0b, 0x07, 0x0b, 0x05, 0x0b, // y:0, x:4 (132)
    0xff, 0xff, 0xcf, 0xc3, 0xc5, 0x03, 0x05, 0x0b, // y:0, x:5 (133)
    0xff, 0xf3, 0x35, 0x23, 0x05, 0x03, 0x05, 0x0b, // y:0, x:6 (134)
    0xc9, 0x89, 0x86, 0xe0, 0x9f, 0x60, 0x1f, 0x00, // y:0, x:7 (135)
    0x4a, 0x46, 0x4a, 0x3c, 0x00, 0xff, 0x00, 0xff, // y:0, x:8 (136)
    0xb3, 0xd1, 0x61, 0x07, 0xf9, 0x06, 0xf8, 0x00, // y:0, x:9 (137)
    0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9, 0xa9, // y:0, x:10 (138)
    0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46, 0x4a, 0x46, // y:0, x:11 (139)
    0xb7, 0xd5, 0xb7, 0xd5, 0xb7, 0xd5, 0xb7, 0xd5, // y:0, x:12 (140)
    0x3f, 0xe2, 0x9e, 0x7f, 0x3f, 0xc3, 0xbc, 0xaf, // y:0, x:13 (141)
    0x02, 0x05, 0x02, 0x00, 0xc0, 0xf8, 0x0f, 0xff, // y:0, x:14 (142)
    0x35, 0x9b, 0x57, 0x51, 0x00, 0x00, 0x01, 0xff, // y:0, x:15 (143)
    0x01, 0x39, 0x6d, 0x61, 0x61, 0x75, 0x3d, 0x19, // y:0, x:16 (144)
    0x01, 0x1b, 0x3d, 0x65, 0x7d, 0xcd, 0xd9, 0x1b, // y:0, x:17 (145)
    0x01, 0x7d, 0xf1, 0xb3, 0x31, 0x1b, 0x19, 0x1b, // y:0, x:18 (146)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, // y:0, x:19 (147)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, // y:0, x:20 (148)
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // y:0, x:21 (149)
    0x10, 0x30, 0x38, 0x7c, 0x6f, 0x6d, 0x6f, 0x0d, // y:0, x:22 (150)
    0x18, 0x1c, 0x3e, 0x7e, 0xee, 0xee, 0xee, 0xf0, // y:0, x:23 (151)
    0x0f, 0x0d, 0x0f, 0x0d, 0x1f, 0x1e, 0x18, 0x00, // y:0, x:24 (152)
    0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0x3c, 0x0c, 0x00, // y:0, x:25 (153)
    0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x3e, 0x7c, 0x70, // y:0, x:26 (154)
    0x81, 0xe3, 0xff, 0x7e, 0x3c, 0x18, 0x00, 0x00, // y:0, x:27 (155)
    0x05, 0x0b, 0x25, 0x33, 0x35, 0x33, 0x15, 0x0b, // y:0, x:28 (156)
    0x0b, 0x15, 0x0b, 0x15, 0x0b, 0x15, 0x0b, 0x15, // y:0, x:29 (157)
};
char * chars = "0000000\0";

void print_points(uint16_t points, uint8_t row) {
    uint8_t col;
    uint8_t indice;
    utoa(points, chars, 10);
    col = 5 - strlen(chars);

    if(col != 0) {
        for(indice = 0; indice != 5; ++indice) {
            sp1_PrintAtInv(row, 25 + indice, INK_CYAN | PAPER_BLACK, '0');
        }
    }
    indice = 0;
    while(chars[indice] != '\0') {
        sp1_PrintAtInv(row, 25 + indice + col, INK_CYAN | PAPER_BLACK, chars[indice]);
        ++indice;
    }

}


// shared vars
uint8_t x, y;


// game required vars
uint8_t paws = 0;
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
//uint8_t udgxs[] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t first_keypress = NONE;

uint8_t idx = 0;
uint8_t idx_j;


uint8_t random_value = 0;

uint8_t opened_window = UNDEF;
uint8_t opened_window_frames = NONE;
uint8_t level = 1;
uint8_t lives = 0;
uint8_t last_success_level = 0;
uint8_t repaint_lives = 0;
uint8_t points = 0;
uint8_t window_shown = 0;


// hearts holes
uint8_t floor_holes[5][12];


// level 1
struct udgstruct windows[14];
const uint8_t bin_places2[] = {NONE, 1, 5, 9, 20, 24};

// variable used for free objects (e.g. kitchen object thrown from window)
uint8_t vertical_direction;
uint8_t horizontal_direction;

JOYFUNC joy;
udk_t joy_keys = { IN_KEY_SCANCODE_SPACE, IN_KEY_SCANCODE_p, IN_KEY_SCANCODE_o, IN_KEY_SCANCODE_a, IN_KEY_SCANCODE_q };
uint16_t in;

//unsigned char show_menu[] = "-1.keyboard-2.kempston-3.sinclair-v5";

extern uint8_t cartoon1[];

void show_menu() {
    __asm
    extern enable_bank_n
   di
   ld a,0x80
   ld i,a                      ; point I at uncontended bank

   ld a,4
   call enable_bank_n          ; bank 4 in top 16k, stack moved
    __endasm;
    memcpy(16384, cartoon1, 6912);
    __asm
    extern restore_bank_0
    call restore_bank_0

    ld a,0xd0
    ld i,a                      ; restore I

    ei
    __endasm;

}

void all_lives_lost() {
  show_menu();

  // ay_vt_init(pcspeaker_module);
  if(lives != SONG_RESTART) {
    ay_vt_init(pcspeaker_module);
    intrinsic_ei();
  }

  lives = 5;


  // todo think on animating the cat a bit in 'demo mode'
  while(1) {
      if(in_key_pressed(IN_KEY_SCANCODE_1)) {
          joy = (JOYFUNC)in_stick_keyboard;
          break;
      } else if(in_key_pressed(IN_KEY_SCANCODE_2)) {
          joy = (JOYFUNC)in_stick_kempston;
          break;
      } else if(in_key_pressed(IN_KEY_SCANCODE_3)) {
          joy = (JOYFUNC)in_stick_sinclair2;
          break;
      }
  }
  first_keypress = tick;
  srand(first_keypress);
  print_background_lvl1();

  intrinsic_di();
  ay_vt_init(music_module);
  intrinsic_ei();
}

/*
static void initialiseColourOther(unsigned int count, struct sp1_cs *c)
{
  (void)count;   // Suppress compiler warning about unused parameter
  c->attr_mask = SP1_AMASK_INK;
  c->attr      = INK_BLACK;
}*/



struct sp1_ss * add_sprite_protar1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 4, 0, 1);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 640, 1); // 64*10
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 1280, 1); // 128 * 10
  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 1);

  //sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

inline struct sp1_ss * add_sprite_swim() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_XOR1LB, SP1_TYPE_1BYTE, 4, 0, 1);
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, 192, 1);  // 32*6
  sp1_AddColSpr(sp, SP1_DRAW_XOR1,    SP1_TYPE_1BYTE, 384, 1); // 64 * 6
  sp1_AddColSpr(sp, SP1_DRAW_XOR1RB,  SP1_TYPE_1BYTE, 0, 1);

  //sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

inline struct sp1_ss * add_sprite_dogr1() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, 0, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 192, 0); // 192 = 48 * 4
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 384, 0); // 96 * 4
  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  //sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}

inline struct sp1_ss * add_sprite_bincat() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, 0, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 96, 0); // 48 * 2
  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 0);

  //sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}



inline struct sp1_ss * add_sprite_auxiliar() {
  struct sp1_ss * sp;
  sp = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, 0, 0);
  sp1_AddColSpr(sp, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, 288, 0);

  sp1_AddColSpr(sp, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 2);

  //sp1_IterateSprChar(sp, initialiseColour);

  return sp;
}


void add_sprites_for_all_levels() {
  misifu.sp = add_sprite_protar1();
  dogr1sp = add_sprite_dogr1();
  bincatsp = add_sprite_bincat();

  aux_object.sp = add_sprite_auxiliar();
  aux_object.x = 0;
  aux_object.y = 0;
  aux_object.offset = AUX_PHONE;
}


void reset_misifu_position() {
  misifu.in_bin = NONE;
  misifu.x = 0;
  misifu.y = FLOOR_Y - 2;
  misifu.initial_jump_y = 0;
  misifu.draw_additional = NONE;
  misifu.state = FALLING_FLOOR;
  aux_object.offset = AUX_BROOM;
  aux_object.x = 33;
  x_malo = 33;
  points = 0;
}

void print_room_walls(uint8_t initial_window, uint8_t paper_color, uint8_t ink_color) {
  uint8_t *pt = rooms;
  uint8_t bright_black_paper = 0x40 | paper_color;
  uint8_t *black_window = tiles_lvl1 + 168;


  for (idx = 0; idx < ROOMS_TILES_LEN; ++idx, pt += 8) {
      sp1_TileEntry(ROOMS_TILES_BASE + idx, pt);
  }
  sp1_TileEntry(UDG_WINDOWHOLE, black_window);


  for(idx = 0; idx != 3; ++idx) {
    // upper left
    sp1_PrintAt( 3 + idx, idx,  bright_black_paper, UDG_WALL3);
    // down left diagonal
    sp1_PrintAt( 20 - idx, idx, bright_black_paper, UDG_WALL4);
    // upper right
    sp1_PrintAt( 5 - idx, 29 + idx,  bright_black_paper, UDG_WALL4);
    // down right
    sp1_PrintAt( 18 + idx, 29 + idx,  bright_black_paper, UDG_WALL3);
  }

  // draw horizontal wall
  for (idx = 3; idx != 29; ++idx) {
    for(idx_j = 5; idx_j != 29; idx_j += 12) {
        sp1_PrintAtInv( idx_j, idx, bright_black_paper, UDG_WALL2);
    }
  }

  // draw vertical wall
  for (idx = 6; idx != 18; ++idx) {
    for(idx_j = 3; idx_j != 55; idx_j += 26) {
        sp1_PrintAtInv( idx, idx_j, bright_black_paper, UDG_WALL1);
    }
  }
  sp1_PrintAtInv( 17, 3, bright_black_paper, UDG_WALL5);

  bright_black_paper = ink_color | paper_color | BRIGHT;

  for (idx = initial_window; idx != initial_window + 8; ++idx) {
     sp1_PrintAt( 7, idx, INK_WHITE | paper_color | BRIGHT, UDG_Q_BARRA_CORTINA);
  }

  for (idx = 8; idx != 11; ++idx) {

    for (idx_j = 0; idx_j != 8; ++idx_j) {
       if(idx_j < 2 || idx_j > 5) {
        sp1_PrintAt( idx, initial_window + idx_j, bright_black_paper, UDG_CURTAIN);
       }
    }

    // x=8, 9 and y=22-25
    if (idx != 10) {
        for (idx_j = 2; idx_j != 6; ++idx_j) {
            sp1_PrintAtInv( idx, initial_window + idx_j,  INK_BLACK | PAPER_WHITE, UDG_WINDOWHOLE);
        }
    }
  }

}

void check_level7_keys() {
    if(misifu.state == FIGHTING) {
        return;
    }
    if (in_key_pressed(IN_KEY_SCANCODE_0)) {
        in_wait_nokey();
        paws = 1;
    }
    if (misifu.state == JUMPING_PUSHED || misifu.state == FALLING) {
        return;
    }

    if((in & IN_STICK_DOWN) && misifu.y < 22) {
        ++misifu.y;
        misifu.state = WALKING_DOWN;
    } else if ((in & IN_STICK_UP) && misifu.y > 17) {
        --misifu.y;
        misifu.state = WALKING_UP;
    }

    if((in & IN_STICK_UP) || (in & IN_STICK_DOWN)) {
        if(misifu.offset == LEFTC1 || misifu.offset == LEFTC2) {
            if((misifu.y & 1) == 0) {
                misifu.offset = LEFTC1;
            } else {
                misifu.offset = LEFTC2;
            }
        } else if (misifu.offset == RIGHTC1 || misifu.offset == RIGHTC2) {
            if((misifu.y & 1) == 0) {
                misifu.offset = RIGHTC1;
            } else {
                misifu.offset = RIGHTC2;
            }
        }
    }

    if ((in & IN_STICK_RIGHT) && misifu.x < level_x_max  && misifu.state != CAT_ON_HIGH) {
        if(misifu.draw_additional == WALKING_RIGHT) {
            ++misifu.x;
        }

        misifu.state = misifu.draw_additional = WALKING_RIGHT;

    } else if ((in & IN_STICK_LEFT) && misifu.x > level_x_min && misifu.state != CAT_ON_HIGH) {
        if(misifu.draw_additional == WALKING_LEFT) {
            --misifu.x;
        }
        misifu.state = misifu.draw_additional = WALKING_LEFT;
    }

}

void check_keys()
{
    // checks keys
    // allow jump in directions
    if((!(in & IN_STICK_UP) && !(in & IN_STICK_DOWN)) || level == 7) {
        misifu.last_key = NONE;
    }
    if ((misifu.last_key != IN_STICK_UP) && (in & IN_STICK_UP) && (misifu.y > 0) && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT || misifu.state == CAT_IN_ROPE || misifu.state ==CAT_ON_HIGH) ) {
        misifu.state = JUMPING;
        misifu.in_bin = NONE;
        misifu.initial_jump_y = misifu.y;
        misifu.last_key = IN_STICK_UP;

        if((in & IN_STICK_RIGHT) && misifu.x < level_x_max ) {
            misifu.draw_additional = JUMP_RIGHT;
        } else if((in & IN_STICK_LEFT) && misifu.x > level_x_min ) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_UP;
        }
    } else if ((in & IN_STICK_RIGHT)  && misifu.x < level_x_max && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        misifu.state = WALKING_RIGHT;
        ++misifu.x;
    } else if((in & IN_STICK_LEFT)  && misifu.x >= level_x_min && (misifu.state == NONE || misifu.state == WALKING_LEFT || misifu.state == WALKING_RIGHT|| misifu.state == CAT_ON_HIGH)) {
        misifu.state = WALKING_LEFT;
        --misifu.x;
    } else if ((misifu.last_key != IN_STICK_DOWN) && (in & IN_STICK_DOWN) && misifu.y < FLOOR_Y) {
        misifu.last_key = IN_STICK_DOWN;
        misifu.state = FALLING;
        misifu.in_bin = NONE;
        ++misifu.y;
    }

    if (in_key_pressed(IN_KEY_SCANCODE_0)) {
        in_wait_nokey();
        paws = 1;
    }

    if(in_key_pressed(IN_KEY_SCANCODE_r)) {
        lives = 0;
        all_lives_lost();
    }
    // see the final
    if (in_key_pressed(IN_KEY_SCANCODE_1)) {
        get_out_of_level_generic(LEVELFINISHED);
    }
    if (in_key_pressed(IN_KEY_SCANCODE_2)) {
        print_background_level3();
    }
    if (in_key_pressed(IN_KEY_SCANCODE_3)) {
        print_background_level4();
    }
    if (in_key_pressed(IN_KEY_SCANCODE_4)) {
        print_background_level5();
    }
    if (in_key_pressed(IN_KEY_SCANCODE_5)) {
        print_background_level6();
    }
    if (in_key_pressed(IN_KEY_SCANCODE_6)) {
        print_background_level7();
    }
    if (in_key_pressed(IN_KEY_SCANCODE_7)) {
        print_background_level_last();
    }
}

void check_swim() {
    if (in_key_pressed(IN_KEY_SCANCODE_0)) {
        in_wait_nokey();
        paws = 1;
    }
    // TODO quiza hacer halts en este nivel extras
    if((in & IN_STICK_LEFT) && misifu.x > 0 ) {
        --misifu.x;
        if (frame == 2) {
            misifu.offset = SWIM_LC1;
        } else {
            misifu.offset = SWIM_LC2;
        }

        if((in & IN_STICK_UP) && misifu.y > 1) {
            --misifu.y;
        } else if((in & IN_STICK_DOWN)) {
            ++misifu.y;
        }
    } else if((in & IN_STICK_RIGHT) && misifu.x < 31 ) {
        ++misifu.x;
        if (frame == 2) {
            misifu.offset = SWIM_RC1;
        } else {
            misifu.offset = SWIM_RC2;
        }
        if((in & IN_STICK_UP) && misifu.y > 1) {
            --misifu.y;
        } else if((in & IN_STICK_DOWN)) {
            ++misifu.y;
        }

    } else if((in & IN_STICK_DOWN) && misifu.y < 29 ) {
        ++misifu.y;
        misifu.offset = SWIM_DOWN1;

    } else if((in & IN_STICK_UP) && misifu.y > 0 ) {
        --misifu.y;
        misifu.offset = SWIM_UP1;

    }
}

void dog_checks() {
// time for doggy checks
   if(level != 7) {
      idx_j = FLOOR_Y;
   } else {
      idx_j = misifu.y;
   }

    if (misifu.state != FIGHTING && enemy_apears == YES) {
        if((frame & 1) == 0) {
            --x_malo;
        }

        if ((x_malo & 1) == 0) {
            dog_offset = DOG1;
        } else  {
            dog_offset = DOG2;
        }

        // detects collission malo->misifu
        if( abs(misifu.x - x_malo) <=1 && misifu.y > 19) {
            enemy_apears = NONE;
            misifu.state = FIGHTING;
            misifu.y = FLOOR_Y;
            anim_frames = 20;
            // hide cat
            //misifu.x = 33;
            x_malo = misifu.x;
            // do sound
            bit_beepfx_di_fastcall(BEEPFX_DROP_1);
            bit_beepfx_di_fastcall(BEEPFX_HIT_1);
        }
        if (x_malo == 0 && misifu.state != FIGHTING) {
            enemy_apears = NONE;
            x_malo = 33;
        }
        sp1_MoveSprAbs(dogr1sp, &full_screen, (int) (sprite_dog1 + dog_offset), idx_j, x_malo, 0, 0);

    }
    idx = 0;
    if (misifu.state == FIGHTING) {
        if (frame < FRAME_CHANGE) {
            dog_offset = DOGFIGHTING1;
        } else {
            dog_offset = DOGFIGHTING2;
        }

        --anim_frames;
        if (anim_frames == 0) {
            enemy_apears = NONE;
            x_malo = 33;
            get_out_of_level_generic(FIGHTING);
            //idx = 1;
        }
        sp1_MoveSprAbs(dogr1sp, &full_screen, (int) (sprite_dog1 + dog_offset), idx_j, x_malo, 0, 0);
    }
    // check if dog should appear
    if (level != 7 && enemy_apears != YES && random_value > 250) {
        enemy_apears = YES;
    }
    return;
}

static void stop_jump_if_needed(uint8_t max_jump) {
    if ((misifu.initial_jump_y - misifu.y) >= max_jump || misifu.x > 28) {
        misifu.state = FALLING;
        misifu.draw_additional = NONE;
    }
}

void check_fsm() {
// decide new FSM draw status
    if (misifu.state == NONE && frame == 3 && level != 7) {
        misifu.offset = (int)BORED;
    } else if (misifu.state == WALKING_RIGHT) {
        if ((misifu.x & 1) == 0) {
            misifu.offset = (int)RIGHTC1;
        } else  {
            misifu.offset = (int)RIGHTC2;
        }
        misifu.state = NONE;
    } else if (misifu.state == WALKING_LEFT) {
        if ((misifu.x & 1) == 0) {
            misifu.offset = (int)LEFTC1;
        } else {
            misifu.offset = (int)LEFTC2;
        }
        misifu.state = NONE;
    } else if (misifu.state == JUMPING_PUSHED){
        if(misifu.y > 2) {
            misifu.y = misifu.y - 2;
        } else {
            misifu.state = FALLING;
        }
        if (misifu.draw_additional == JUMP_LEFT) {
            if(misifu.x > 1) {
                misifu.x = misifu.x - 2;
            }
        } else {
            if(misifu.x < (level_x_max - 2)) {
                misifu.x = misifu.x + 2;
            }
        }
        stop_jump_if_needed(10);
    } else if (misifu.state == JUMPING) {
        --misifu.y;
        if(level == 10 && misifu.y < 3) {
            misifu.state = FALLING;
            misifu.y = 3;
        }

        if(misifu.draw_additional == JUMP_RIGHT && misifu.x < level_x_max) {

            misifu.offset = (int)JRIGHTC1;
            if((in & IN_STICK_RIGHT)) {
                ++misifu.x;
            }
        }  else if(misifu.draw_additional == JUMP_LEFT && misifu.x > level_x_min) {
            misifu.offset =(int) JLEFTC1;

            if((in & IN_STICK_LEFT)) {
                --misifu.x;
            }
        } else {
            misifu.offset = (int)JUMPINGC1;
        }

        if (level == 1) {
            if (misifu.y <= 1) {
                misifu.y = 2;
                misifu.offset = (int)HANGING;
                misifu.state = CAT_IN_ROPE;
                misifu.draw_additional = CAT_IN_ROPE3;
            }
        }

        stop_jump_if_needed(5);
    } else if (misifu.state == FALLING) {
        ++misifu.y;
        misifu.offset = FALL_OFFSET;

        if(misifu.y >= FLOOR_Y) {
            misifu.y = FLOOR_Y;
            misifu.state = NONE;
            misifu.offset = (int)BORED;
        }
    } else if (misifu.state == FALLING_FLOOR) {
        ++misifu.y;
        misifu.offset = FALL_OFFSET;
        misifu.draw_additional = NONE;
        if(misifu.y >= FLOOR_Y) {
            misifu.y = FLOOR_Y;
            misifu.state = NONE;
        }
    } else if(misifu.state == CAT_IN_ROPE) {
        misifu.offset = (int)HANGING;

    }
}

void paint_lamp(uint8_t col, uint8_t color) {
    if(level == 7) {
        frame = 18;
    } else {
        frame = 19;
    }

    sp1_PrintAtInv(frame, col, color, UDG_Q_MESABASE);
    for(idx = frame - 4; idx != frame; ++idx) {
       sp1_PrintAtInv(idx, col, color, UDG_MESAPATA);
    }

    for(idx = frame - 6; idx != frame - 4; ++idx) {
        for(idx_j = col - 1; idx_j != col + 2; ++idx_j) {
            sp1_PrintAtInv(idx, idx_j, color, UDG_LAMP1);
        }
    }
    sp1_PrintAtInv(frame - 4, col + 1, color, UDG_LAMP2);
}

void paint_table(uint8_t col, uint8_t color) {
    sp1_PrintAt(18, col, color, UDG_MESASIDE);
    sp1_PrintAt(18, col + 1, color, UDG_MESATOP);
    sp1_PrintAt(18, col + 2,  color, UDG_MESASIDE);

    sp1_PrintAt(19, col + 1,  color, UDG_MESAPATA);
    sp1_PrintAt(20, col + 1,  color, UDG_Q_MESABASE);
}

void paint_chair(uint8_t col, uint8_t color) {
    for(idx_j = 17; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j, col,  color, UDG_SILLAL); // RESPALDO Y PATA IZQ
    }
    sp1_PrintAtInv( 19, col,  color, UDG_SILLALM); // ASIENTO
    sp1_PrintAt( 19, col + 1,  color, UDG_SILLARM); // ASIENTO
    sp1_PrintAt( 20, col + 1,  color, UDG_SILLAR); // PATA DERECHA
}


void paint_portrait(uint8_t color) {
    x = UDG_CUADRO_SUPERIOR_IZQUIERDA;
    for(idx_j = 10; idx_j != 12; ++idx_j) {
        for(idx = 10; idx != 12; ++idx) {
            sp1_PrintAt(idx_j, idx, color, x);
            ++x;
        }
    }
}

void paint_chair2(uint8_t col, uint8_t color) {
    for(idx_j = 17; idx_j != 21; ++idx_j) {
        sp1_PrintAt( idx_j, col + 1,  color, UDG_SILLA2_PARTE01); // RESPALDO Y PATA DER
    }

    sp1_PrintAtInv( 19, col + 1,  color, UDG_SILLA2_PARTE02); // ASIENTO
    sp1_PrintAt( 19, col,  color, UDG_SILLA2_PARTE03); // ASIENTO
    sp1_PrintAt( 20, col,  color, UDG_SILLA2_PARTE04); // PATA FRONTAL
}

void detect_fall_in_chair(uint8_t x_chair, uint8_t bin) {
    if(misifu.state == FALLING && misifu.x == x_chair && misifu.y == 17) {
        misifu.state = CAT_ON_HIGH;
        misifu.in_bin = bin;
        misifu.offset = (int)BORED;
    }

    if(misifu.in_bin == bin && misifu.x != x_chair) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }
}

void get_out_of_level_generic(uint8_t fall) {
    sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_WHITE,
                  ' ' );
    // control wether if gets out of level by having eat all mouses
    sp1_Invalidate(&full_screen);
    sp1_TileEntry('H', heart2);

    if(fall == LEVELFINISHED) {
        last_success_level = 0;
        //sp1_DeleteSpr_fastcall(dogr1sp);
        ay_vt_init(sweet_module);
        x = 0;
        for(idx = 14; idx != 18; ++idx) {
            sp1_PrintAt(10, idx, INK_BLACK | PAPER_WHITE, final_msg[x]);
            ++x;
        }

        for (idx = 0; idx != 13; ++idx) {

            if((idx & 1) == 0) {
                misifu.offset = (int)RIGHTC1;
                idx_j = LEFTC1;
            } else {
                misifu.offset = (int)RIGHTC2;
                idx_j = LEFTC2;
            }
            sp1_MoveSprAbs(misifu.sp, &full_screen,(int) sprite_protar1 + misifu.offset, FLOOR_Y, 2 + idx, 0, 0);

            sp1_MoveSprAbs(fredsp, &full_screen,(int) sprite_protar1 + idx_j, FLOOR_Y, 30 - idx, 0, 0);
            sp1_UpdateNow();
            for(idx_j = 0; idx_j != 15; ++idx_j) {
                wait();
            }
        }
        sp1_DeleteSpr_fastcall(fredsp);
        fredsp = NULL;
        ay_vt_init(music_module);

    } else if(fall == WON_LEVEL) {
        last_success_level = level;
        idx_j = 250 / points;  // number of VUs

        if(idx_j > 20) {
            idx_j = 20;
        }

        for (idx = 0; idx != idx_j; ++idx) {
            for(x = 14; x != 20; x += 2) {
                sp1_PrintAtInv(22 - idx, x, INK_RED | PAPER_WHITE, 'H');
            }
            sp1_UpdateNow();
            wait();
        }
        bit_beepfx_di_fastcall(BEEPFX_SELECT_5);
    } else if(fall == FALLING) {
        bit_beepfx_di_fastcall(BEEPFX_UH_HUH);
    } else if (fall == ELECTRIFIED) {
        for (idx = 0; idx != 5; ++idx) {
            bit_beepfx_di_fastcall(BEEPFX_HIT_4);
            zx_border(INK_WHITE);
            wait();
            zx_border(INK_BLUE);
        }
    } else if(fall == OXYGEN) {
        bit_beepfx_di_fastcall(BEEPFX_GULP);
    } else {
        if(fall != FIGHTING) {
            bit_beepfx_di_fastcall(BEEPFX_DROP_1);
        }
        if(lives > 0) {
            --lives;
        } else {
            // reached zero on lives
            last_success_level = 0;
            bit_beepfx_di_fastcall(BEEPFX_BOOM_1);

            all_lives_lost();
        }
        repaint_lives = 1;
    }

    if(birdsp != NULL) {
        sp1_DeleteSpr_fastcall(birdsp);
        birdsp = NULL;
    }

    opened_window_frames = 2;
    print_background_lvl1();
}



void detect_cat_in_window(uint8_t offset) {
    if( misifu.y >= 8 && misifu.y <= 10) {
        if(misifu.x == (19 - offset) || misifu.x == (20 - offset) || misifu.x == (25 - offset) || misifu.x == (26 - offset)) {
            misifu.state = CAT_IN_ROPE;
        } else if(misifu.x >= (21 - offset) && misifu.x <= (24 - offset)) {
            //get_out_of_level_generic(FALLING);
            window_shown = 10;
        }
    }
}

inline void check_broom_collision() {

    if (misifu.state != FALLING_FLOOR && misifu.state!= JUMPING_PUSHED && abs(misifu.x - aux_object.x) < 2 && abs(misifu.y - aux_object.y) < 2) {
        misifu.state = JUMPING_PUSHED;
        misifu.initial_jump_y = misifu.y;
        // will jump right or left depending on where is hit
        if(misifu.x < aux_object.x) {
            misifu.draw_additional = JUMP_LEFT;
        } else {
            misifu.draw_additional = JUMP_RIGHT;
        }
    }
}


void move_broom() {
 if(misifu.state == FIGHTING) {
    return;
 }
 if (frame < FRAME_CHANGE) {
     aux_object.offset = AUX_BROOM;
 } else {
     aux_object.offset = AUX_BROOM2;
 }


 // BROOM MOVE
    if((random_value & 1) == 0) {
        if(random_value < 50) {
            ++aux_object.y;
        } else if (random_value < 100 && aux_object.y > 0) {
            --aux_object.y;
        } else if(random_value < 150) {
            ++aux_object.x;
        } else if(random_value < 200) {
            --aux_object.x;
        } else if(misifu.state != JUMPING_PUSHED) {
            if(misifu.x < aux_object.x) {
                --aux_object.x;
            } else if(misifu.x > aux_object.x) {
                ++aux_object.x;
            }

            if (misifu.y < aux_object.y) {
                --aux_object.y;
            } else if (misifu.y > aux_object.y) {
                ++aux_object.y;
            }
        }

        if(aux_object.x < 3) {
            aux_object.x = 3;
        } else if(aux_object.x > 29) {
            aux_object.x = 29;
        }

        if (aux_object.y < 1) {
            aux_object.y = 0;
        } else if(aux_object.y > 21) {
            aux_object.y = 21;
        }

        sp1_MoveSprAbs(aux_object.sp, &full_screen, (int) auxiliar1 + aux_object.offset, aux_object.y, aux_object.x, 0, 0);
    }

    check_broom_collision();
}



void detect_fall_in_table(uint8_t offset) {
    idx = 25 - offset;
    idx_j = 27 - offset;
    if(misifu.state == FALLING) {
        if(misifu.y == 16 && misifu.x >= idx && misifu.x <= idx_j) {
            misifu.state = CAT_ON_HIGH;
            misifu.offset = (int)BORED;
            misifu.in_bin = 2;
        }
    }

    if(misifu.in_bin == 2 && !(misifu.x >= idx && misifu.x <= idx_j)) {
        misifu.state = FALLING;
        misifu.in_bin = NONE;
    }

}



// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83

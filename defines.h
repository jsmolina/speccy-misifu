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
#define CAT_ON_HIGH 10
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

extern struct sp1_Rect;


extern struct prota misifu;
extern struct freesprite aux_object;
extern struct sp1_ss  *dogr1sp;
extern struct sp1_ss  *bincatsp;

extern struct row_clothes row1clothes[2];
extern struct row_clothes row2clothes[2];
extern unsigned char udg_win2[];

extern struct sp1_Rect full_screen;

extern uint8_t level_x_max[];
extern uint8_t level_x_min[];

// shared vars
extern uint8_t x, y;


// game required vars
extern uint8_t frame;
extern uint8_t x_malo;
extern uint8_t bincat_appears;
extern uint8_t enemy_apears;
extern uint8_t row1_moving;
extern uint8_t bincat_in_bin;
extern uint8_t dog_offset;
// keeps animation frames when something takes longer
extern uint8_t anim_frames;
extern uint8_t anim_frames_bincat;

extern uint8_t first_keypress;

extern uint8_t idx;
extern uint8_t idx_j;


extern uint8_t random_value;

extern uint8_t opened_window;
extern uint8_t opened_window_frames;
extern uint8_t level;

// level 3 hearts
extern const uint8_t heart1[];
extern const uint8_t heart2[];
extern const uint8_t cupid11[];
extern const uint8_t cupid12[];
extern const uint8_t cupid13[];
extern const uint8_t cupid21[];
extern const uint8_t cupid22[];
extern const uint8_t cupid23[];
extern const uint8_t cupid31[];
extern const uint8_t cupid32[];
extern const uint8_t cupid33[];

extern uint8_t floor_holes4[];
extern uint8_t floor_holes3[];
extern uint8_t floor_holes2[];
extern uint8_t floor_holes1[];
extern uint8_t floor_holes[];

// level 2 cheese
extern const uint8_t hole_empty[];
extern const uint8_t hole_mouse[];
extern const uint8_t cheese2[];
extern const uint8_t curtain[];

extern const uint8_t wall1[];
extern const uint8_t wall2[];
extern const uint8_t wall3[];
extern const uint8_t wall4[];

// level 1
extern struct udgstruct windows[14];
extern const uint8_t bin_places2[];


extern const uint8_t udg_valla1[];
extern const uint8_t udg_valla2[];
extern const uint8_t udg_valla3[];
extern const uint8_t udg_valla4[];

extern const uint8_t cubo_down1[];
extern const uint8_t cubo_down2[];
extern const uint8_t cubo_down3[];
extern const uint8_t cubo_middle1[];
extern const uint8_t cubo_middle2[];
extern const uint8_t cubo_middle3[];

extern const uint8_t cubotop1[];
extern const uint8_t cubotop2[];
extern const uint8_t cubotop3[];

extern const uint8_t udg_rope[];
extern const uint8_t  udg_win1[]; // with rope
extern const uint8_t  udg_win3[];

extern const uint8_t udg_c[];
extern const uint8_t udg_a[];
extern const uint8_t udg_t[];


// variable used for free objects (e.g. kitchen object thrown from window)
extern uint8_t vertical_direction;
extern uint8_t horizontal_direction;

extern void initialiseColour(unsigned int count, struct sp1_cs *c);

extern void initialiseDogColour(unsigned int count, struct sp1_cs *c);

extern void initialiseClothesColour(unsigned int count, struct sp1_cs *c);


extern struct sp1_ss * add_sprite_protar1();

extern struct sp1_ss * add_sprite_dogr1();

extern struct sp1_ss * add_sprite_bincat();

extern struct sp1_ss * add_sprite_clothes1();
extern struct sp1_ss * add_sprite_clothes2();

extern struct sp1_ss * add_sprite_auxiliar();

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

#ifndef _DEFINES_H
#define _DEFINES_H

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>

#define UNDEF 250
#define NONE 0
#define WON_LEVEL 10
#define YES 1
#define BIN_Y1 15
#define BIN_Y2 16
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define OXYGEN 99
#define FIGHTING 5
#define CAT_IN_ROPE 6
#define CAT_IN_ROPE1 7
#define CAT_IN_ROPE2 8
#define CAT_IN_ROPE3 9
#define CAT_ON_HIGH 10
#define JUMPING_PUSHED 11
#define SWIMMING 12
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
#define SPIDER 25 // 16 + 8 + 1

#define AUX_ZAP 33  // 24 + 8 + 1
#define AUX_ARROWRIGHT 65
#define AUX_ARROWLEFT  97
#define AUX_BROOM 129

#define SWIM_RC1 1
#define SWIM_RC2 33  // 24 + 8 + 1
#define SWIM_LC1 65
#define SWIM_LC2  97
#define SWIM_UP1 129
#define SWIM_DOWN1 161

#define MISIOFFSET 33
#define OUCHOFFSET 65
#define LOVEOFFSET 97

#define Y_AXIS 0
#define X_AXIS 1

#define FISHES_HORIZ_DIR 2
#define FISHES_VERT_DIR 3

#define LEVELFINISHED 100

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

extern uint8_t level_x_max;
extern uint8_t level_x_min;

// shared vars
extern uint8_t x, y;


// game required vars
// useful for  controlling amount of things to eat (mouses, fishes, ...)
extern char left;
extern char right;
extern uint8_t eaten_items;
extern uint8_t frame;
extern uint8_t x_malo;
extern uint8_t bincat_appears;
extern uint8_t enemy_apears;
extern uint8_t row1_moving;
extern uint8_t bincat_in_bin;
extern uint8_t dog_offset;
// keeps animation frames when something takes longer
extern uint8_t anim_frames;
extern uint8_t udgxs[];
extern uint8_t udgys[];

extern uint8_t first_keypress;

extern uint8_t idx;
extern uint8_t idx_j;


extern uint8_t random_value;

extern uint8_t opened_window;
extern uint8_t opened_window_frames;
extern uint8_t level;
extern uint8_t lives;
extern uint8_t last_success_level; // to see user progress
extern uint8_t repaint_lives;
extern uint16_t points;

extern uint8_t floor_holes[][24];

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


// variable used for free objects (e.g. kitchen object thrown from window)
extern uint8_t vertical_direction;
extern uint8_t horizontal_direction;

extern void add_sprites_for_all_levels();

struct row_clothes {
    struct sp1_ss* sp;
    uint8_t col;
    uint8_t offset;
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
    char has_item;
};

extern void all_lives_lost();

extern void loose_a_live();

extern void reset_misifu_position();

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83
// extern void page(uint8_t bank);

extern void check_keys();

extern void dog_checks();

extern void check_swim();

extern void check_fsm();

extern void print_room_walls(uint8_t initial_window, uint8_t paper_color, uint8_t ink_color);
extern void define_silla_udgs();

extern void paint_chair(uint8_t row, uint8_t col, uint8_t paper_color, uint8_t ink_color);

extern void paint_table(uint8_t row, uint8_t col, uint8_t paper_color, uint8_t ink_color);

extern void get_out_of_level_generic(uint8_t fall);

extern void detect_cat_in_window(uint8_t offset);

extern void move_broom();

extern void check_broom_collision();

extern struct sp1_ss * add_sprite_swim();

extern struct sp1_ss * add_sprite_protar1();

#endif

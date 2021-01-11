#ifndef _DEFINES_H
#define _DEFINES_H

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>

#define BACKGROUND_GREEN 0x60

#define Y_POS 0
#define X_POS 1
#define UNDEF 250
#define NONE 0
#define WON_LEVEL 10
#define DOG_AWAKEN 30
#define ELECTRIFIED 40
#define YES 1
#define CLEAN 1
#define BIN_Y1 15
#define BIN_Y2 16
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define FALLING_FLOOR 69
#define BITE 55
#define OXYGEN 99
#define FIGHTING 5
#define CAT_IN_ROPE 6
#define CAT_IN_ROPE1 7
#define CAT_IN_ROPE2 8
#define CAT_IN_ROPE3 9
#define CAT_IN_SHELVE 20
#define CAT_ON_HIGH 10
#define JUMPING_PUSHED 11
#define SWIMMING 12
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#define CAT_IN_BIN 3
#define CAT_IN_FENCE 4
#define HIGHER_BIN_X 2   // bins are from 1 - 5
#define HIGHER_BIN_X2 4
#define FLOOR_Y 21

#define AUX_BINCAT 0
#define SPIDER 48 // (16 * 2) + 16
#define BIRD_OFFSET 96
#define BIRD_OFFSET2 144

#define RIGHTC1 0
#define RIGHTC2 64
#define LEFTC1 128
#define LEFTC2 192
#define JLEFTC1 256
#define JRIGHTC1 320
#define JUMPINGC1 384
#define BORED 448
#define HANGING 512
#define FALL_OFFSET 576

#define AUX_PHONE 0
#define AUX_ZAP 48  // + 16x2 + 8x2
#define AUX_ARROWRIGHT 96
#define AUX_ARROWLEFT  144
#define AUX_BROOM 192
#define AUX_BROOM2 240

#define SWIM_RC1 0
#define SWIM_RC2 32  // 24 + 8
#define SWIM_LC1 64
#define SWIM_LC2  96
#define SWIM_UP1 128
#define SWIM_DOWN1 160

#define MISIOFFSET 33
#define OUCHOFFSET 65
#define LOVEOFFSET 97

#define Y_AXIS 0
#define X_AXIS 1

#define FISHES_HORIZ_DIR 2
#define FISHES_VERT_DIR 3

#define LEVELFINISHED 100

#define UP 64
#define DOWN 128
#define LEFT 1
#define RIGHT 2

#define FISH_LEFT 'B'
#define FISH_RIGHT 'A'

#define BIRD 244

#define FRAME_CHANGE 3
#define FRAME_MOST 4
#define DOG1 0
#define DOG2 48
#define DOGFIGHTING1 96
#define DOGFIGHTING2 144

#define SONG_RESTART 250

#define MAX_X 32

extern struct sp1_Rect;


extern struct prota misifu;
extern struct freesprite aux_object;
extern struct sp1_ss  *dogr1sp;
extern struct sp1_ss  *bincatsp;


extern const uint8_t queso_textura[];
extern const uint8_t queso_diagonal[];

extern struct sp1_Rect full_screen;

extern uint8_t level_x_max;
extern uint8_t level_x_min;

// shared vars
extern uint8_t x;

extern uint8_t paws;
// game required vars
// useful for  controlling amount of things to eat (mouses, fishes, ...)
extern const uint8_t heart2[];
extern char left;
extern char right;
extern uint8_t eaten_items;
extern uint8_t frame;
extern uint8_t frame_big;
extern uint8_t x_malo;
extern uint8_t bincat_appears;
extern uint8_t enemy_apears;
extern uint8_t row1_moving;
extern uint8_t bincat_in_bin;
extern uint8_t dog_offset;
// keeps animation frames when something takes longer
extern uint8_t anim_frames;
//extern uint8_t udgxs[];

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
extern uint8_t points;

extern uint8_t floor_holes[][24];

// level 2 cheese
extern const uint8_t hole_empty[];
extern const uint8_t hole_mouse[];
extern const uint8_t cheese2[];
extern const uint8_t curtain[];


extern uint8_t sprite_protar1[];
extern uint8_t sprite_protar2[];
extern uint8_t sprite_protar3[];

extern uint8_t sprite_dog1[];
extern uint8_t sprite_dog2[];
extern uint8_t sprite_dog3[];

extern uint8_t sprite_bincat1[];
extern uint8_t sprite_bincat2[];
extern uint8_t sprite_bincat3[];

extern uint8_t auxiliar1[];
extern uint8_t auxiliar2[];

extern uint8_t sprite_swim1[];
extern uint8_t sprite_swim2[];
extern uint8_t sprite_swim3[];
extern uint8_t sprite_swim4[];

// level 1
extern struct udgstruct windows[14];
extern const uint8_t bin_places2[];


// variable used for free objects (e.g. kitchen object thrown from window)
extern uint8_t horizontal_direction;

extern void add_sprites_for_all_levels();

struct prota {
    struct sp1_ss* sp;
    uint8_t x;
    uint8_t y;
    uint8_t initial_jump_y;
    uint8_t draw_additional;
    unsigned int  offset;
    uint8_t in_bin;
    uint8_t state;
    uint8_t last_key;
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

extern JOYFUNC joy;
extern udk_t joy_keys;
extern uint16_t in;

extern void all_lives_lost();


extern void reset_misifu_position();

// reference: https://github.com/z88dk/z88dk/blob/master/include/_DEVELOPMENT/sdcc/arch/zx/sp1.h#L83
// extern void page(uint8_t bank);

extern void check_keys();
extern void check_level7_keys();

extern void dog_checks();

extern void check_swim();

extern void check_fsm();

extern void print_room_walls(uint8_t initial_window, uint8_t paper_color, uint8_t ink_color);

extern void paint_chair(uint8_t row, uint8_t col, uint8_t paper_color, uint8_t ink_color);

extern void detect_fall_in_chair(uint8_t x_chair);

extern void paint_table(uint8_t row, uint8_t col, uint8_t paper_color, uint8_t ink_color);

extern void get_out_of_level_generic(uint8_t fall);

extern void detect_cat_in_window(uint8_t offset);

extern void move_broom();

extern struct sp1_ss * add_sprite_swim();

extern struct sp1_ss * add_sprite_protar1();

extern void check_chair_and_table();

extern void move_right_and_left();
extern void assign_window_pos(uint8_t y, uint8_t x);

#endif

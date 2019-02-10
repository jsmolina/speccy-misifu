#include <stdlib.h>
#include <sound.h>
#include <input.h>
#include "defines.h"
#include "level1.h"

const uint8_t udg_dog1[] = {0x0, 0xf, 0x1f, 0x3f, 0x7f, 0x8f, 0x3e, 0x60};
const uint8_t udg_dog1m[] = {0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0};
const uint8_t udg_dog2[] = {0x0, 0xb3, 0xde, 0xef, 0xef, 0xcf, 0xe6, 0x31};
const uint8_t udg_dogmilk[] = {0x3c, 0x66, 0xc3, 0x81, 0xc3, 0xff, 0x7e, 0x3c};

// https://user-images.githubusercontent.com/447481/51000354-2598e700-152d-11e9-86ac-7106cfed0137.png

void print_a_dog(uint8_t row, uint8_t col) {
    // sp1_PrintAt(uint16_t row,uint16_t col
    sp1_PrintAt(row, col, INK_WHITE | PAPER_MAGENTA, 'C');
    sp1_PrintAt(row, col + 1, INK_WHITE | PAPER_MAGENTA, 'D');
    sp1_PrintAt(row, col + 2, INK_WHITE | PAPER_MAGENTA, 'E');
    sp1_PrintAt(row, col + 4, INK_BLUE | PAPER_MAGENTA, 'O');
}

void assign_dogs(uint8_t y, uint8_t x) {
    assign_window_pos(y, x);
    print_a_dog(y, x);
}

void  print_background_level7() {
     sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                      PAPER_MAGENTA,
                      ' ' );
     level = 7;

     sp1_Invalidate(&full_screen);

     sp1_TileEntry('C', udg_dog1);
     sp1_TileEntry('D', udg_dog1m);
     sp1_TileEntry('E', udg_dog2);
     sp1_TileEntry('O', udg_dogmilk);

     level_x_max = 26;
     level_x_min = 2;
     eaten_items = 6;
     horizontal_direction = 3; // you can touch up to three dogs before getting out of level

     print_room_walls(20, PAPER_MAGENTA, INK_CYAN);
     idx = 0;
     assign_dogs(23, 5); //  x + 2 is the bowl position
     assign_dogs(23, 15);
     assign_dogs(21, 10);
     assign_dogs(21, 22);
     assign_dogs(18, 5);
     assign_dogs(18, 12);

     reset_misifu_position();
     misifu.draw_additional = WALKING_RIGHT;
}

static inline void drink_milk_or_got_awaken(uint8_t index) {
    if(misifu.x > (windows[index].x + 1)) {
        if(windows[index].has_item != 'Z' && (in & IN_STICK_FIRE)) {
            sp1_PrintAtInv(windows[index].y, windows[index].x + 4, INK_GREEN | PAPER_MAGENTA, 'O');
            windows[index].has_item = 'Z';
            --eaten_items;
            bit_beepfx_di_fastcall(BEEPFX_EAT);

            if(eaten_items == 0) {
                get_out_of_level_generic(WON_LEVEL);
            }
        }
    } else {
        --horizontal_direction;
        bit_beepfx_di_fastcall(BEEPFX_GULP);
        misifu.x = 0;
        misifu.y = 15;
        misifu.state = FALLING;

        if(horizontal_direction == 0) {
            get_out_of_level_generic(DOG_AWAKEN);
        }
    }
}


static uint8_t get_index_from_misifu_position() {
    if(misifu.y == 22) {
        if(misifu.x > 2 && misifu.x < 10) {
            return 0;
        } else if(misifu.x > 12 && misifu.x < 20) {
            return 1;
        }

    } else if(misifu.y == 20) {
        if(misifu.x > 7 && misifu.x < 15) {
            return 2;
        } else if(misifu.x > 20 && misifu.x < 27) {
            return 3;
        }
    } else if(misifu.y == 17) {
        if(misifu.x > 2 && misifu.x < 10) {
            return 4;
        } else if(misifu.x > 9 && misifu.x < 17) {
            return 5;
        }
    }

    return UNDEF;
}

static void check_eat_milk_or_dog() {
    // misifu.x - 1 is the real udg position
    idx = get_index_from_misifu_position();

    if(idx != UNDEF) {
        drink_milk_or_got_awaken(idx);
    }
}


void level7_loop() {
    if(misifu.y < 17 && misifu.state != CAT_IN_ROPE && misifu.state != JUMPING_PUSHED) {
        misifu.state = FALLING;
    }

    check_eat_milk_or_dog();
    move_broom();
    detect_cat_in_window(0);
}
#include <stdlib.h>
#include <sound.h>
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

void assign_dogs(uint8_t index, uint8_t y, uint8_t x) {
    windows[index].y = y;
    windows[index].x = x;
    windows[index].has_item = 'O';
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

     print_room_walls(20, PAPER_MAGENTA, INK_CYAN);
     assign_dogs(0, 23, 5);
     assign_dogs(1, 23, 15);
     assign_dogs(2, 21, 10);
     assign_dogs(3, 21, 22);
     assign_dogs(4, 18, 5);
     assign_dogs(5, 18, 12);

     reset_misifu_position();
     misifu.draw_additional = WALKING_RIGHT;
}

static inline void drink_milk(uint8_t index) {
    if(windows[index].has_item != 'Z') {
        //sp1_PrintAt(windows[idx].y, windows[idx].x + 4, INK_BLACK | PAPER_MAGENTA, 'O');
        windows[index].has_item = 'Z';
        --eaten_items;

        if(eaten_items == 0) {
            get_out_of_level_generic(WON_LEVEL);
        }
    }
}

static inline void got_awaken() {
    get_out_of_level_generic(DOG_AWAKEN);
}

static uint8_t get_index_from_misifu_position() {
    if(misifu.y == 22) {
        if(misifu.x == 7) {
            return 0;
        } else if(misifu.x == 17) {
            return 1;
        }

    } else if(misifu.y == 20) {
        if(misifu.x == 12) {
            return 2;
        } else if(misifu.x == 24) {
            return 3;
        }
    } else if(misifu.y == 17) {
        if(misifu.x == 7) {
            return 4;
        } else if(misifu.x == 14) {
            return 5;
        }
    }

    return NONE;
}

static void check_eat_milk_or_dog() {
    // misifu.x - 1 is the real udg position
    idx = get_index_from_misifu_position();
}


void level7_loop() {
    check_eat_milk_or_dog();
}
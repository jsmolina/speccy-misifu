#include <stdlib.h>
#include <sound.h>
#include <input.h>
#include <intrinsic.h>
#include "defines.h"
#include "level1.h"

#define LEVEL7_TILES_LEN  10
#define LEVEL7_TILES_BASE  65

#define MILK_ON_RIGHT 1
#define MILK_ON_LEFT 2
#define NO_MILK 2
#define HAS_MILK 1

#define SLEEPING 1
#define AWAKEN 2

#define UDG_CUENCO_VACIO 65
#define UDG_CUENCO_LLENO 66
#define UDG_CACHORRO_DERECHA_COLA 67
#define UDG_CACHORRO_DERECHA_CUERPO 68
#define UDG_CACHORRO_DERECHA_CABEZA 69
#define UDG_CACHORRO_DERECHA_CABEZA_OJOS 70
#define UDG_CACHORRO_IZQUIERDA_CABEZA 71
#define UDG_CACHORRO_IZQUIERDA_CUERPO 72
#define UDG_CACHORRO_IZQUIERDA_COLA 73
#define UDG_CACHORRO_IZQUIERDA_CABEZA_OJOS 74


#define WHITE_MAGENTA_BRIGHT INK_WHITE | PAPER_MAGENTA | BRIGHT
#define TOTAL_PERROS 8

const uint8_t perros_coords [] = {0x42, 0x15, 0x55, 0x32, 0x04, 0x43, 0x53, 0x23};
uint8_t last_awaken;

uint8_t level7[] = {
    0x00, 0x7e, 0xc3, 0x81, 0xc3, 0xff, 0xff, 0x7e, // y:0, x:0 (65)
    0x00, 0x7e, 0xc3, 0xbd, 0xc3, 0xff, 0xff, 0x7e, // y:0, x:1 (66)
    0x03, 0x0f, 0x1f, 0x1f, 0x3c, 0x5f, 0x4f, 0x23, // y:0, x:2 (67)
    0xfd, 0xfe, 0xfd, 0xfd, 0xed, 0x6e, 0x37, 0x83, // y:0, x:3 (68)
    0xdc, 0xf8, 0xfc, 0xfc, 0xfc, 0xf8, 0x74, 0x8c, // y:0, x:4 (69)
    0xdc, 0xf8, 0xfc, 0xfc, 0x24, 0xf8, 0x74, 0x8c, // y:0, x:5 (70)
    0x3b, 0x1f, 0x3f, 0x3f, 0x3f, 0x1f, 0x2e, 0x31, // y:0, x:6 (71)
    0xbf, 0x7f, 0xbf, 0xbf, 0xb7, 0x76, 0xec, 0xc1, // y:0, x:7 (72)
    0xc0, 0xf0, 0xf8, 0xf8, 0x3c, 0xfa, 0xf2, 0xc4, // y:0, x:8 (73)
    0x3b, 0x1f, 0x3f, 0x3f, 0x24, 0x1f, 0x2e, 0x31, // y:0, x:9 (74)
};

// https://user-images.githubusercontent.com/447481/51000354-2598e700-152d-11e9-86ac-7106cfed0137.png
/*
void print_a_dog(uint8_t row, uint8_t col) {
    // sp1_PrintAt(uint16_t row,uint16_t col
    sp1_PrintAt(row, col, WHITE_MAGENTA_BRIGHT, 'C');
    sp1_PrintAt(row, col + 1, WHITE_MAGENTA_BRIGHT, 'D');
    sp1_PrintAt(row, col + 2, WHITE_MAGENTA_BRIGHT, 'E');
    sp1_PrintAt(row, col + 4, INK_BLUE | PAPER_MAGENTA | BRIGHT, 'O');
}

void assign_dogs(uint8_t y, uint8_t x) {
    assign_window_pos(y, x);
    print_a_dog(y, x);
}*/

void  print_background_level7() {
     sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                      PAPER_BLUE| BRIGHT | INK_CYAN,
                      ' ' );
     level = 7;

     sp1_Invalidate(&full_screen);

     uint8_t *pt = level7;
      print_room_walls(20, PAPER_BLUE, INK_CYAN);

     // So now you can use:
     for (idx = 0; idx < LEVEL7_TILES_LEN; idx++, pt += 8) {
         sp1_TileEntry(LEVEL7_TILES_BASE + idx, pt);
     }
     paint_lamp(5, INK_CYAN | PAPER_BLUE | BRIGHT);
     paint_portrait(INK_CYAN | PAPER_BLUE| BRIGHT);

     idx = 0;
     for(x = 0; x != TOTAL_PERROS; ++x) {
        idx += perros_coords[x] & 0x0F;
        idx_j = ((perros_coords[x] & 0xF0) >> 4) + 18;
        // 3 , 5, 7 are painted backwards

        if(x == 3 || x == 5 || x == 7) {
            frame = UDG_CACHORRO_IZQUIERDA_CABEZA;
            floor_holes[0][x] = MILK_ON_LEFT;
            horizontal_direction = idx;
            eaten_items = 1;
        } else {
            frame = UDG_CACHORRO_DERECHA_COLA;
            floor_holes[0][x] = MILK_ON_RIGHT;
            horizontal_direction = idx + 3;
            eaten_items = 0;
        }
        floor_holes[1][x] = HAS_MILK;
        floor_holes[2][x] = SLEEPING;
        // dog
        for(bincat_appears = eaten_items; bincat_appears != eaten_items + 3; ++bincat_appears) {
            sp1_PrintAt(
                idx_j,
                idx + bincat_appears,
                INK_CYAN | PAPER_BLUE | BRIGHT,
                frame
            );
            frame += 1;
        }
        // milk
        sp1_PrintAt(
            idx_j,
            horizontal_direction,
            INK_WHITE | PAPER_BLUE | BRIGHT,
            UDG_CUENCO_LLENO
        );
     }

     level_x_max = 28;
     level_x_min = 3;
     //misifu.state = WALKING_RIGHT;

     eaten_items = TOTAL_PERROS;

     last_awaken = UNDEF;
     reset_misifu_position();
     misifu.offset = RIGHTC1;
     misifu.state = WALKING_RIGHT;
     misifu.x = level_x_min;
     misifu.y = 17;

     enemy_apears = NONE;
}


inline void drink_milk() {
    bit_beepfx_di_fastcall(BEEPFX_SCORE);

    if(floor_holes[1][x] == NO_MILK) {
        // already eaten!
        return;
    }
    --eaten_items;
    total_points += 10;
    // milk: row1_moving is the offset where milk is positioned if it is on right
    sp1_PrintAt(
        idx_j,
        idx + row1_moving,
        INK_WHITE | PAPER_BLUE| BRIGHT,
        UDG_CUENCO_VACIO
    );
    floor_holes[1][x] = NO_MILK; // 1 + 2 = 3
}


void level7_loop() {
    if(misifu.y < 17 && misifu.state != CAT_IN_ROPE && misifu.state != JUMPING_PUSHED) {
        misifu.state = FALLING;
    }
    if(misifu.y >= 17 && misifu.state == FALLING) {
        misifu.state = NONE;
        misifu.offset = (int)BORED;
        misifu.y = 17;
    }

    move_broom();

    for(idx = 0; idx != 4; ++idx) {
        intrinsic_halt();
    }

    idx = 0;
    for(x = 0; x != TOTAL_PERROS; ++x) {
        idx += perros_coords[x] & 0x0F;
        idx_j = ((perros_coords[x] & 0xF0) >> 4) + 18;
        horizontal_direction = misifu.x + 1;
        // example, misifu is at 6, 6 +1 = 7
        // dog starts on 7, so 7, 8, 9, 10 are right positions
        // 7 >= 7 && 7 <= 10

        // colision with dog
        if(misifu.state != FIGHTING && (misifu.y + 1) == idx_j && horizontal_direction >= (idx - 1)
           && horizontal_direction <= (idx + 4)) {
            //if(in & IN_STICK_FIRE)
            //(in & IN_STICK_FIRE)
            row1_moving = 0;
            if(floor_holes[0][x] == MILK_ON_RIGHT) {
                row1_moving = idx + 4; // milk is offset 4 to the right
            } else {
                row1_moving = idx - 1; // milk is offset -1 to the left
            }

            if(horizontal_direction == row1_moving) {
                if(in & IN_STICK_FIRE) {

                    if(floor_holes[0][x] == MILK_ON_RIGHT) {
                        row1_moving = 3;
                        if(misifu.draw_additional != WALKING_LEFT) {
                            return;
                        }
                    } else {
                        if(misifu.draw_additional != WALKING_RIGHT) {
                            return;
                        }
                        row1_moving = 0;
                    }

                    drink_milk();

                    if(eaten_items == 0) {
                        get_out_of_level_generic(WON_LEVEL);
                    }
                    return;
                }
            } else if(floor_holes[2][x] == SLEEPING) {
                // +1 si esta a la izquierda
                // +2 si esta a la derecha
                row1_moving = 1;
                floor_holes[2][x] = UDG_CACHORRO_IZQUIERDA_CABEZA_OJOS;
                if(floor_holes[0][x] == MILK_ON_RIGHT) {
                    row1_moving = 2; // milk is offset 3 to the right
                    floor_holes[2][x] = UDG_CACHORRO_DERECHA_CABEZA_OJOS;
                }

                sp1_PrintAt(
                    idx_j,
                    idx + row1_moving,
                    INK_CYAN | PAPER_BLUE| BRIGHT,
                    floor_holes[2][x]
                );
                last_awaken = x;
                floor_holes[2][x] = AWAKEN;
            } else if(floor_holes[2][x] == AWAKEN && last_awaken != x) {
                x_malo = misifu.x;
                misifu.state = FIGHTING;
                bit_beepfx_di_fastcall(BEEPFX_GULP);
                anim_frames = 20;
            }
        } else if(last_awaken == x) {
            last_awaken = UNDEF;
        }
    }
    dog_checks();
    detect_cat_in_window(0);
}
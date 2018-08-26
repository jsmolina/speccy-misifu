// juego.c
// Esqueleto de juegos de Radastan para ZX Spectrum
// version 0.1 beta
#define BIN_Y1 15
#define BIN_Y2 16
#define NO_DRAW 0
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define FIGHTING 5
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#define FLOOR_Y 21
#include <config.h>
#include <spriteszx.h>
#include <lib/motorzx.h>
#include <lib/sonidoszx.h>

#pragma output STACKPTR=65000

unsigned char pantalla [768];

unsigned char in_left_bins(unsigned char x) {
    return(x >= 0 && x < 13);
}

unsigned char in_right_bins(unsigned char x) {
    return(x >= 15 && x < 28);
}

unsigned char in_bin1 (unsigned char x) {
    return (x >= 1 && x < 3);
}

unsigned char in_bin2 (unsigned char x) {
    return (x >= 7 && x < 9);
}

unsigned char in_bin3 (unsigned char x) {
    return (x >= 19 && x < 21);
}

unsigned char in_bin4 (unsigned char x) {
    return (x >= 24 && x < 27);
}

void paint_bin1() {
    put_sprite_x32(bin1, 2, 17);
    put_sprite_x32(bin2, 2, 20);
}

void paint_bin2() {
    put_sprite_x32(bin1, 7, 18);
    put_sprite_x32(bin2, 7, 20);
}

void paint_bin3() {
    put_sprite_x32(bin1, 19, 17);
    put_sprite_x32(bin2, 19, 20);
}

void paint_bin4() {
    put_sprite_x32(bin1, 24, 18);
    put_sprite_x32(bin2, 24, 20);
}

void main (void)
{
    unsigned char x, y, draw, frame, frame_malo, initial_jump_y, jump_direction;
    unsigned char x_malo;
    unsigned char malo_appears = 0;

    cls(7); // Borramos la pantalla
	x=0;
    y=FLOOR_Y;
    x_malo = 22;
    frame_malo = 0;
    initial_jump_y = 0;
    draw=0;
    frame=0;
    jump_direction = 0;
    put_sprite_32x16(sprite_prota1, x, y);
    // paint bins
    paint_bin1();
    paint_bin2();
    paint_bin3();
    paint_bin4();

    put_sprite_x32(bin2, 24, 20);

	while (1)
    {
        // check keyboard inputs (todo move to function)

        if ((port_in(64510)&1)==0 && y>0 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT) ) // Q
        {
            draw = JUMPING;
            initial_jump_y = y;

            if((port_in(57342)&1)==0 && x<28) {
                jump_direction = JUMP_RIGHT;
            } else if((port_in(57342)&2)==0 && x>0) {
                jump_direction = JUMP_LEFT;
            } else {
                jump_direction = JUMP_UP;
            }
        }

        if ((port_in(57342)&1)==0 && x<28 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT) ) // P
        {
            put_sprite_32x16 (sprite_negro,x,y);
            draw = WALKING_RIGHT;
            ++x;
        }

        if ((port_in(57342)&2)==0 && x>0 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT)) // O
        {
            put_sprite_32x16 (sprite_negro,x,y);
            draw = WALKING_LEFT;
            --x;
        }

        if ((port_in(65022)&1)==0 && y<22) // A
        {
            //put_sprite_32x16 (sprite_negro,x,y);
            //draw = WALKING;
            //++y;
            malo_appears = 1;
        }


        // check if cat should fall out of bin
        if (y <= BIN_Y2 && (draw == WALKING_RIGHT || draw == WALKING_LEFT )) {
            if(in_bin1(x) || in_bin2(x) || in_bin3(x)  || in_bin4(x)) {

            } else {
                draw = FALLING;
            }
        }

        if (draw == WALKING_RIGHT) {
            if (frame==0) {
                put_sprite_32x16(sprite_prota1, x, y);
                frame=1;
            } else {
                put_sprite_32x16(sprite_prota2, x, y);
                frame=0;
            }
            draw = NO_DRAW;
        }

        if (draw == WALKING_LEFT) {
            if (frame==0) {
                put_sprite_32x16(sprite_prota4, x, y);
                frame=1;
            } else {
                put_sprite_32x16(sprite_prota5, x, y);
                frame=0;
            }
            draw = NO_DRAW;
        }

        if (draw == JUMPING) {
            put_sprite_32x16 (sprite_negro,x,y);
            --y;

            if(jump_direction == JUMP_RIGHT && x < 28) {
                ++x;
                put_sprite_32x16(sprite_protajumpright, x, y);
            } else if(jump_direction == JUMP_LEFT && x > 0) {
                --x;
                put_sprite_32x16(sprite_protajumpleft, x, y);
            } else {
                put_sprite_32x16(sprite_protajump, x, y);
            }

            if (initial_jump_y - y >= 8) {
                draw = FALLING;
            }
        }

        if (draw == FALLING) {
            put_sprite_32x16 (sprite_negro,x,y);
            ++y;

            put_sprite_32x16(sprite_protajump, x, y);
            if(y == FLOOR_Y) {
                // todo tomar suelo del mapeado
                draw = NO_DRAW;
            } else if (in_bin1(x) && y == BIN_Y1) {
                draw = NO_DRAW;
            } else if (in_bin2(x) && y == BIN_Y2) {
                draw = NO_DRAW;
            } else if (in_bin3(x) && y == BIN_Y1) {
                draw = NO_DRAW;
            } else if (in_bin4(x) && y == BIN_Y2) {
                draw = NO_DRAW;
            }
        }

        if (draw == FIGHTING) {
            // pierde una vida y dura X frames
            put_sprite_32x16 (sprite_negro,x,y);
            if (frame==0) {
                put_sprite_32x16(sprite_fight1, x, y);
                frame = 1;
            } else {
                put_sprite_32x16(sprite_fight2, x, y);
                frame = 0;
            }

            --frame_malo;
            if (frame_malo == 0) {
                draw = NO_DRAW;
            }
        }

        if (draw != FIGHTING && malo_appears == 1) {
            // pintar malo todo en random
            put_sprite_32x16 (sprite_negro, x_malo, FLOOR_Y);
            --x_malo;
            if (x_malo <= 0) {
                // arrived to the left
                put_sprite_32x16 (sprite_negro, x_malo, FLOOR_Y);
                malo_appears = 0;
                x_malo = 22;
                paint_bin1();
            } else {
                if (frame_malo == 0){
                    put_sprite_32x16 (sprite_malo1, x_malo, FLOOR_Y);
                    frame_malo = 1;
                } else {
                    put_sprite_32x16 (sprite_malo2, x_malo, FLOOR_Y);
                    frame_malo = 0;
                }
            }

            // detects collission malo->misifu
            if( abs(x - x_malo) < 3 && y > 18) {
                malo_appears = 0;
                draw = FIGHTING;
                put_sprite_32x16 (sprite_negro, x_malo, FLOOR_Y);
                frame_malo = 10;
                put_sprite_32x16 (sprite_negro, x, y);
                y = FLOOR_Y;
                x_malo = 22;
            }
        }

        // bins redraw routine
        if (in_left_bins(x) || in_left_bins(x_malo)) {
            paint_bin1();
            paint_bin2();
        }
        if (in_right_bins(x) || in_right_bins(x_malo)) {
           paint_bin3();
           paint_bin4();
        }


        wait_int(); wait_int(); wait_int(); wait_int();
    }

}

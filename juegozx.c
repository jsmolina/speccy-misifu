// juego.c
// Esqueleto de juegos de Radastan para ZX Spectrum
// version 0.1 beta
#define NO_DRAW 0
#define WALKING_LEFT 1
#define WALKING_RIGHT 2
#define JUMPING 3
#define FALLING 4
#define FIGHTING 5
#define JUMP_UP  0
#define JUMP_RIGHT 1
#define JUMP_LEFT 2
#include <config.h>
#include <spriteszx.h>
#include <lib/motorzx.h>
#include <lib/sonidoszx.h>

#pragma output STACKPTR=65000

unsigned char pantalla [768];

void main (void)
{
    unsigned char x, y, draw, frame, frame_malo, initial_jump_y, jump_direction;
    unsigned char x_malo;
    unsigned char malo_appears = 0;

    cls(7); // Borramos la pantalla
    malo_appears = rand();
	x=0;
    y=22;
    x_malo = 22;
    frame_malo = 0;
    initial_jump_y = 0;
    draw=0;
    frame=0;
    jump_direction = 0;
    put_sprite_32x16(sprite_prota1, x, y);

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

        if ((port_in(65022)&1)==0 && y<22) // A
        {
            //put_sprite_32x16 (sprite_negro,x,y);
            //draw = WALKING;
            //++y;
        }

        if ((port_in(57342)&1)==0 && x<28 && (draw == NO_DRAW || draw == WALKING_LEFT || draw == WALKING_RIGHT) ) // P
        {
            put_sprite_32x16 (sprite_negro,x,y);
            draw = WALKING_RIGHT;
            ++x;
        }

        if ((port_in(57342)&2)==0 && x>0 && draw != JUMPING && draw != FALLING) // O
        {
            put_sprite_32x16 (sprite_negro,x,y);
            draw = WALKING_LEFT;
            --x;
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

            if(jump_direction == JUMP_RIGHT) {
                ++x;
                put_sprite_32x16(sprite_protajumpright, x, y);
            } else if(jump_direction == JUMP_LEFT) {
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
            if(y == 22) {
                // todo tomar suelo del mapeado
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

        if (draw != FIGHTING) {
            // pintar malo todo en random
            put_sprite_32x16 (sprite_negro, x_malo, 22);
            --x_malo;
            if (frame_malo == 0){
                put_sprite_32x16 (sprite_malo1, x_malo, 22);
                frame_malo = 1;
            } else {
                put_sprite_32x16 (sprite_malo2, x_malo, 22);
                frame_malo = 0;
            }

            if( abs(x - x_malo) < 3 && y > 18) {
                draw = FIGHTING;
                put_sprite_32x16 (sprite_negro, x_malo, 22);
                frame_malo = 10;
                put_sprite_32x16 (sprite_negro, x, y);
                y = 22;
                x_malo = 22;
            } else if (x_malo <= 0) {
                put_sprite_32x16 (sprite_negro, x_malo, 22);
                x_malo = 22;
            }
        }


        wait_int(); wait_int(); wait_int(); wait_int();
    }

}

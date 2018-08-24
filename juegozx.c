// juego.c
// Esqueleto de juegos de Radastan para ZX Spectrum
// version 0.1 beta

#include <config.h>
#include <spriteszx.h>
#include <lib/motorzx.h>
#include <lib/sonidoszx.h>

#pragma output STACKPTR=65000

unsigned char pantalla [768];

void main (void)
{
    unsigned char x, y, draw, frame;
    cls(7); // Borramos la pantalla

	x=10;
    y=5;
    draw=0;
    frame=0;
    put_sprite_32x16(sprite_prota1, x, y);

	while (1)
    {
        if ((port_in(64510)&1)==0 && y>0) // Q
        {
            put_partial1v_sprite_x16 (sprite_negro,x,y+1);
            draw=1;
            --y;
        }

        if ((port_in(65022)&1)==0 && y<22) // A
        {
            put_partial1v_sprite_x16 (sprite_negro,x,y);
            draw=1;
            ++y;
        }

        if ((port_in(57342)&1)==0 && x<30) // P
        {
            put_partial1h_sprite_x16 (sprite_negro,x,y);
            draw=1;
            ++x;
        }

        if ((port_in(57342)&2)==0 && x>0) // O
        {
            put_sprite_32x16 (sprite_negro,x,y);
            draw=1;
            --x;
        }

        if (draw == 1) {
            if (frame==0) {
                put_sprite_32x16(sprite_prota1, x, y);
                frame=1;
            } else {
                put_sprite_32x16(sprite_prota2, x, y);
                frame=0;
            }
            draw = 0;
        }


        wait_int(); wait_int(); wait_int(); wait_int();
    }

}

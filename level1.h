#ifndef _LEVEL1
#define _LEVEL1

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include "defines.h"



extern uint8_t is_in_bin(uint8_t x_pos);


extern void  print_cubo(uint8_t x);


extern void paint_window(uint8_t num, uint16_t colour);

extern void  print_background_lvl1();



extern void move_clothes();

extern void anim_windows();



extern void check_bincat();

extern void detect_fall_in_bin();

//extern void add_row_clothes();
void detect_fall_in_window();

#endif

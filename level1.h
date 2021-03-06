#ifndef _LEVEL1
#define _LEVEL1

#include <z80.h>
#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include "defines.h"

extern uint8_t is_in_bin(uint8_t x_pos);
extern void  print_background_lvl1();

//extern void add_row_clothes();

extern inline void level1_loop();

#endif

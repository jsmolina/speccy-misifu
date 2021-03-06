#ifndef _LEVEL2
#define _LEVEL2
// AKA RATS ROOM

#include "defines.h"

/**
Returns 1 if x,y are in window position
**/
extern uint8_t thrown_from_window(uint8_t x, uint8_t y);
// Candidate to be shared


extern void define_cheese_holes_pos();


extern inline void  print_background_level2();

extern void detect_fall_in_hole_or_curtain();

extern inline void level2_loop();


#endif

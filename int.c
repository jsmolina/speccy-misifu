#include <stdlib.h>
#include <intrinsic.h>
#include "defines.h"
#include "int.h"

// timer

unsigned char tick;
unsigned char timer;

void
wait(void)
{
   while (abs(tick - timer) < WFRAMES)
      intrinsic_halt();

   timer = tick;
}

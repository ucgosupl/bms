#include "timestamp.h"

uint8_t seed = 0;

void timestamp_get(struct datetime *dt)
{
   dt->year = 2025;
   dt->month = 02;
   dt->day = 20;

   dt->h = seed++;
   dt->m = seed++;
   dt->s = seed++;
}

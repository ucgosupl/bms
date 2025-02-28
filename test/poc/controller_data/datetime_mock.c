#include "interface/datetime/datetime.h"

static uint8_t seed = 0;

void datetime_get(struct datetime *dt)
{
   dt->year = 2025;
   dt->month = 02;
   dt->day = 20;

   dt->h = seed++;
   dt->m = seed++;
   dt->s = seed++;
}
